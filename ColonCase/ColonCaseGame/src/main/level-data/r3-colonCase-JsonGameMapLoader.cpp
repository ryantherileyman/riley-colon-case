
#include <stdexcept>
#include <unordered_map>
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

			class GameTileImageDefnListBuilder {

			private:
				const tiled::MapTilesetDefn* mapTilesetDefn;
				const tiled::TilesetDefn* tilesetDefn;
				std::vector<GameTileImageDefn> result;

			public:
				GameTileImageDefnListBuilder(const tiled::MapTilesetDefn* mapTilesetDefn, const tiled::TilesetDefn* tilesetDefn) {
					this->mapTilesetDefn = mapTilesetDefn;
					this->tilesetDefn = tilesetDefn;
				}

				std::vector<GameTileImageDefn> build() {
					if (this->tilesetDefn->type == tiled::TilesetType::IMAGE) {
						this->buildAllFromImage();
					}
					else if (this->tilesetDefn->type == tiled::TilesetType::TILE_LIST) {
						this->buildAllFromTileList();
					}

					return result;
				}

				void buildAllFromImage() {
					int currTileId = 0;
					int currRow = 0;
					int textureRectTop = this->tilesetDefn->margin;
					while (currTileId < this->tilesetDefn->tileCount) {
						int textureRectLeft = this->tilesetDefn->margin;
						for (int currColumn = 0; currColumn < this->tilesetDefn->columns; currColumn++) {
							GameTileImageDefn currTileImageDefn;
							currTileImageDefn.tileId = this->mapTilesetDefn->firstGid + currTileId;
							currTileImageDefn.filename = this->tilesetDefn->imageDefn.imagePath;
							currTileImageDefn.imageSize.x = this->tilesetDefn->imageDefn.imageWidth;
							currTileImageDefn.imageSize.y = this->tilesetDefn->imageDefn.imageHeight;
							currTileImageDefn.textureRect.left = textureRectLeft;
							currTileImageDefn.textureRect.top = textureRectTop;
							currTileImageDefn.textureRect.width = this->tilesetDefn->tileWidth;
							currTileImageDefn.textureRect.height = this->tilesetDefn->tileHeight;

							this->result.push_back(currTileImageDefn);

							currTileId++;
							textureRectLeft += this->tilesetDefn->tileWidth + this->tilesetDefn->spacing;
						}

						currRow++;
						textureRectTop += this->tilesetDefn->tileHeight + this->tilesetDefn->spacing;
					}
				}

				void buildAllFromTileList() {
					for (const auto& currTileDefn : this->tilesetDefn->tileDefnList) {
						GameTileImageDefn currTileImageDefn;
						currTileImageDefn.tileId = this->mapTilesetDefn->firstGid + currTileDefn.id;
						currTileImageDefn.filename = currTileDefn.imageDefn.imagePath;
						currTileImageDefn.imageSize.x = currTileDefn.imageDefn.imageWidth;
						currTileImageDefn.imageSize.y = currTileDefn.imageDefn.imageHeight;
						currTileImageDefn.textureRect.left = 0;
						currTileImageDefn.textureRect.top = 0;
						currTileImageDefn.textureRect.width = currTileDefn.imageDefn.imageWidth;
						currTileImageDefn.textureRect.height = currTileDefn.imageDefn.imageHeight;

						this->result.push_back(currTileImageDefn);
					}
				}

			};

			std::vector<GameTileImageDefn> convertToTileImageDefnList(const tiled::MapTilesetDefn& mapTilesetDefn, const tiled::TilesetDefn& tilesetDefn) {
				GameTileImageDefnListBuilder builder(&mapTilesetDefn, &tilesetDefn);
				std::vector<GameTileImageDefn> result = builder.build();
				return result;
			}

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
					result.tileIdList.insert(std::end(result.tileIdList), std::begin(source.data), std::end(source.data));
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

			class GameMapDefnLoader {

			private:
				const char* campaignFolder;
				const char* mapFilePath;
				tiled::JsonMapLoader::LoadMapResult loadMapResult;
				std::unordered_map<std::string, tiled::TilesetDefn> tilesetDefnMap;
				LoadGameMapResult result;

			public:
				GameMapDefnLoader(const char* campaignFolder, const char* mapFilePath) {
					this->campaignFolder = campaignFolder;
					this->mapFilePath = mapFilePath;
				}

				LoadGameMapResult load() {
					if (GameLoaderUtils::isValidPath(this->campaignFolder, this->mapFilePath)) {
						this->loadMap();

						if (this->result.errorList.empty()) {
							this->buildGameMapDefn();
						}
					}
					else {
						this->result.errorList.push_back(GameLoaderUtils::localizeInvalidPathError(this->campaignFolder, this->mapFilePath));
					}

					return result;
				}
				
			private:

				void loadMap() {
					std::string fullFilePath = GameLoaderUtils::buildFullPath(this->campaignFolder, this->mapFilePath);
					this->loadMapResult = tiled::JsonMapLoader::loadFromFile(fullFilePath.c_str());

					if (this->loadMapResult.errorList.empty()) {
						for (const auto& currMapTilesetDefn : this->loadMapResult.mapDefn.tilesetDefnList) {
							this->loadTilesetIfValid(currMapTilesetDefn);
						}
					}
					else {
						this->result.errorList.insert(std::end(this->result.errorList), std::begin(this->loadMapResult.errorList), std::end(this->loadMapResult.errorList));
					}
				}

				void loadTilesetIfValid(const tiled::MapTilesetDefn& sourceMapTilesetDefn) {
					std::string tilesetRelativePath = GameLoaderUtils::resolveRelativeFilePath(this->mapFilePath, sourceMapTilesetDefn.sourcePath.c_str());

					if (GameLoaderUtils::isValidPath(this->campaignFolder, tilesetRelativePath.c_str())) {
						this->loadTileset(sourceMapTilesetDefn);
					}
					else {
						this->result.errorList.push_back(GameLoaderUtils::localizeInvalidPathError(this->campaignFolder, tilesetRelativePath.c_str()));
					}
				}

				void loadTileset(const tiled::MapTilesetDefn& sourceMapTilesetDefn) {
					std::string tilesetRelativePath = GameLoaderUtils::resolveRelativeFilePath(this->mapFilePath, sourceMapTilesetDefn.sourcePath.c_str());
					std::string tilesetFullPath = GameLoaderUtils::buildFullPath(this->campaignFolder, tilesetRelativePath.c_str());

					tiled::JsonTilesetLoader::LoadTilesetResult loadTilesetResult = tiled::JsonTilesetLoader::loadFromJsonFile(tilesetFullPath.c_str());

					if (loadTilesetResult.errorList.empty()) {
						this->tilesetDefnMap[sourceMapTilesetDefn.sourcePath] = loadTilesetResult.tilesetDefn;
					}
					else {
						this->result.errorList.insert(std::end(this->result.errorList), std::begin(loadTilesetResult.errorList), std::end(loadTilesetResult.errorList));
					}
				}

				void buildGameMapDefn() {
					this->result.mapDefn.size.x = this->loadMapResult.mapDefn.width;
					this->result.mapDefn.size.y = this->loadMapResult.mapDefn.height;

					this->result.mapDefn.tileSize.x = this->loadMapResult.mapDefn.tileWidth;
					this->result.mapDefn.tileSize.y = this->loadMapResult.mapDefn.tileHeight;

					if (!this->loadMapResult.mapDefn.backgroundColor.empty()) {
						this->result.mapDefn.backgroundColor = GameLoaderUtils::convertToSfmlColor(this->loadMapResult.mapDefn.backgroundColor);
					}

					for (const auto& currMapTilesetDefn : this->loadMapResult.mapDefn.tilesetDefnList) {
						const auto& currTilesetDefn = this->tilesetDefnMap[currMapTilesetDefn.sourcePath];

						std::string tilesetRelativePath = GameLoaderUtils::resolveRelativeFilePath(this->mapFilePath, currMapTilesetDefn.sourcePath.c_str());

						std::vector<GameTileImageDefn> tileImageDefnList = convertToTileImageDefnList(currMapTilesetDefn, currTilesetDefn);
						for (const auto& currTileImageDefn : tileImageDefnList) {
							this->result.mapDefn.tileImageDefnMap[currTileImageDefn.tileId] = currTileImageDefn;

							// Convert the image path to be relative to the campaign folder
							std::string imageRelativePath = GameLoaderUtils::resolveRelativeFilePath(tilesetRelativePath.c_str(), currTileImageDefn.filename.c_str());
							this->result.mapDefn.tileImageDefnMap[currTileImageDefn.tileId].filename = imageRelativePath;
						}
					}

					for (const auto& currLayerDefn : this->loadMapResult.mapDefn.layerDefnList) {
						this->attachGameMapLayerDefnList(currLayerDefn);
					}
				}

				void attachGameMapLayerDefnList(const tiled::MapLayerDefn& sourceLayerDefn) {
					if (
						(sourceLayerDefn.type == tiled::MapLayerType::TILE) ||
						(sourceLayerDefn.type == tiled::MapLayerType::OBJECT)
					) {
						this->result.mapDefn.layerDefnList.push_back(convertToLayerDefn(sourceLayerDefn));
					}
					else if (sourceLayerDefn.type == tiled::MapLayerType::GROUP) {
						for (const auto& currChildLayerDefn : sourceLayerDefn.layerDefnList) {
							this->attachGameMapLayerDefnList(currChildLayerDefn);
						}
					}
				}

			};

			LoadGameMapResult loadFromFile(const char* campaignFolder, const char* filePath) {
				GameMapDefnLoader loader(campaignFolder, filePath);
				LoadGameMapResult result = loader.load();
				return result;
			}

		}

	}

}
