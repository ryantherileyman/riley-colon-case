
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include "r3-colonCase-JsonGameLoader.hpp"
#include "../tiled/r3-tiled-defn.hpp"
#include "../tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace colonCase {

		namespace LayerPropertyName {

			const char* RENDER_FLAG = "renderFlag";
			const char* COLLISION_FLAG = "collisionFlag";

		}

		namespace JsonGameMapLoader {

			GameMapSpriteDefn convertToSpriteDefn(const tiled::MapLayerObjectDefn& source) {
				if (source.objectType != tiled::MapLayerObjectType::TILE) {
					throw std::invalid_argument("Object must be a tile");
				}

				GameMapSpriteDefn result;
				result.tileId = source.tileGid;
				result.position.x = (float)source.position.x;
				result.position.y = (float)source.position.y;
				result.size.x = (float)source.width;
				result.size.y = (float)source.height;
				return result;
			}

			GameMapLayerType resolveGameMapLayerType(const tiled::MapLayerDefn& source) {
				GameMapLayerType result = GameMapLayerType::UNKNOWN;

				if (source.type == tiled::MapLayerType::TILE) {
					result = GameMapLayerType::TILE;
				}
				else if (source.type == tiled::MapLayerType::OBJECT) {
					result = GameMapLayerType::SPRITE;
				}

				return result;
			}

			GameMapLayerDefn convertToLayerDefn(const tiled::MapLayerDefn& source) {
				GameMapLayerDefn result;

				result.layerType = resolveGameMapLayerType(source);

				if (tiled::CustomPropertyDefnUtils::containsOfType(source.propertyDefnList, LayerPropertyName::RENDER_FLAG, tiled::CustomPropertyType::BOOLEAN)) {
					result.renderFlag = tiled::CustomPropertyDefnUtils::getBoolValue(source.propertyDefnList, LayerPropertyName::RENDER_FLAG);
				}

				if (tiled::CustomPropertyDefnUtils::containsOfType(source.propertyDefnList, LayerPropertyName::COLLISION_FLAG, tiled::CustomPropertyType::BOOLEAN)) {
					result.collisionFlag = tiled::CustomPropertyDefnUtils::getBoolValue(source.propertyDefnList, LayerPropertyName::COLLISION_FLAG);
				}

				if (result.layerType == GameMapLayerType::TILE) {
					std::copy(std::begin(source.data), std::end(source.data), std::back_inserter(result.tileIdList));
				}

				if (result.layerType == GameMapLayerType::SPRITE) {
					for (const auto& currObjectDefn : source.objectDefnList) {
						if (currObjectDefn.objectType == tiled::MapLayerObjectType::TILE) {
							GameMapSpriteDefn currSpriteDefn = convertToSpriteDefn(currObjectDefn);
							result.spriteDefnList.push_back(currSpriteDefn);
						}
					}
				}

				return result;
			}

			class TiledMapLoader {

			private:
				const char* campaignFolder;
				const char* mapFilePath;
				LoadTiledMapResult result;

			public:
				TiledMapLoader(const char* campaignFolder, const char* filePath) {
					this->campaignFolder = campaignFolder;
					this->mapFilePath = filePath;
				}

				LoadTiledMapResult load() {
					if (GameLoaderUtils::isValidPath(this->campaignFolder, this->mapFilePath)) {
						this->loadMap();
					}
					else {
						this->result.errorList.push_back(GameLoaderUtils::localizeInvalidPathError(this->campaignFolder, this->mapFilePath));
					}

					return result;
				}

			private:

				void loadMap() {
					std::string fullFilePath = GameLoaderUtils::buildFullPath(this->campaignFolder, this->mapFilePath);
					tiled::JsonMapLoader::LoadMapResult loadMapResult = tiled::JsonMapLoader::loadFromFile(fullFilePath.c_str());

					if (loadMapResult.errorList.empty()) {
						this->result.mapDefn = loadMapResult.mapDefn;

						this->loadTilesetList(loadMapResult.mapDefn.tilesetDefnList);
					}
					else {
						this->result.errorList.insert(std::end(this->result.errorList), std::begin(loadMapResult.errorList), std::end(loadMapResult.errorList));
					}
				}

				void loadTilesetList(const std::vector<tiled::MapTilesetDefn>& mapTilesetDefnList) {
					for (const auto& currTilesetDefn : mapTilesetDefnList) {
						this->loadTilesetIfValid(currTilesetDefn);
					}
				}

				void loadTilesetIfValid(const tiled::MapTilesetDefn& mapTilesetDefn) {
					std::string tilesetRelativePath = GameLoaderUtils::resolveRelativeFilePath(this->mapFilePath, mapTilesetDefn.sourcePath.c_str());
					if (GameLoaderUtils::isValidPath(this->campaignFolder, tilesetRelativePath.c_str())) {
						this->loadTileset(mapTilesetDefn, tilesetRelativePath);
					}
					else {
						this->result.errorList.push_back(GameLoaderUtils::localizeInvalidPathError(this->campaignFolder, tilesetRelativePath.c_str()));
					}
				}

				void loadTileset(const tiled::MapTilesetDefn& mapTilesetDefn, const std::string& tilesetRelativePath) {
					std::string tilesetFullPath = GameLoaderUtils::buildFullPath(campaignFolder, tilesetRelativePath.c_str());

					tiled::JsonTilesetLoader::LoadTilesetResult loadTilesetResult = tiled::JsonTilesetLoader::loadFromJsonFile(tilesetFullPath.c_str());

					if (loadTilesetResult.errorList.empty()) {
						this->result.tilesetDefnMap[mapTilesetDefn.sourcePath] = loadTilesetResult.tilesetDefn;

						auto& tilesetDefn = this->result.tilesetDefnMap[mapTilesetDefn.sourcePath];
						for (auto& currTileDefn : tilesetDefn.tileDefnList) {
							currTileDefn.id += mapTilesetDefn.firstGid;
						}
					}
					else {
						this->result.errorList.insert(std::end(this->result.errorList), std::begin(loadTilesetResult.errorList), std::end(loadTilesetResult.errorList));
					}
				}

			};

			LoadTiledMapResult loadFromFile(const char* campaignFolder, const char* filePath) {
				TiledMapLoader loader(campaignFolder, filePath);
				LoadTiledMapResult result = loader.load();
				return result;
			}

			std::unordered_map<int, GameTileImageDefn> buildGameTileImageDefnMap(const tiled::MapDefn& source) {
				std::unordered_map<int, GameTileImageDefn> result;

				for (auto& currTilesetDefn : source.tilesetDefnList) {
					
				}

				return result;
			}

			GameMapDefn convertTiledMapDefn(const tiled::MapDefn& source) {
				GameMapDefn result;

				result.size.x = source.width;
				result.size.y = source.height;



				return result;
			}

		}

	}

}
