
#include <math.h>
#include <stdexcept>
#include "r3-colonCase-JsonGameMapLoaderTests.hpp"
#include "../../main/level-data/r3-colonCase-JsonGameLoader.hpp"

namespace r3 {

	namespace colonCase {

		namespace JsonGameMapLoaderTests {

			tiled::CustomPropertyDefn createBoolPropertyDefn(const char* name, bool value) {
				tiled::CustomPropertyDefn result;
				result.name = name;
				result.type = tiled::CustomPropertyType::BOOLEAN;
				result.boolValue = value;
				return result;
			}

			tiled::MapTilesetDefn createMapTilesetDefn(int firstGid, const std::string& sourcePath) {
				tiled::MapTilesetDefn result;
				result.firstGid = firstGid;
				result.sourcePath = sourcePath;
				return result;
			}

			tiled::TilesetDefn createImageTilesetDefn() {
				tiled::TilesetDefn result;
				result.version = 1.4;
				result.type = tiled::TilesetType::IMAGE;
				result.columns = 3;
				result.tileCount = 6;
				result.tileWidth = 32;
				result.tileHeight = 16;
				result.margin = 2;
				result.spacing = 1;
				result.imageDefn.imagePath = "../textures/texture-atlas.png";
				result.imageDefn.imageWidth = 105;
				result.imageDefn.imageHeight = 39;
				return result;
			}

			tiled::TilesetDefn createTileListTilesetDefn() {
				tiled::TilesetTileDefn tile1Defn;
				tile1Defn.id = 0;
				tile1Defn.imageDefn.imagePath = "../textures/floor1.png";
				tile1Defn.imageDefn.imageWidth = 64;
				tile1Defn.imageDefn.imageHeight = 32;

				tiled::TilesetTileDefn tile2Defn;
				tile2Defn.id = 1;
				tile2Defn.imageDefn.imagePath = "../textures/floor2.png";
				tile2Defn.imageDefn.imageWidth = 64;
				tile2Defn.imageDefn.imageHeight = 32;

				tiled::TilesetDefn result;
				result.version = 1.4;
				result.type = tiled::TilesetType::TILE_LIST;
				result.columns = 0;
				result.tileCount = 2;
				result.tileWidth = 64;
				result.tileHeight = 32;
				result.margin = 0;
				result.spacing = 0;
				result.tileDefnList.push_back(tile1Defn);
				result.tileDefnList.push_back(tile2Defn);
				return result;
			}

			tiled::MapLayerObjectDefn createMapLayerObjectDefn() {
				tiled::MapLayerObjectDefn result;
				result.id = 2;
				result.position.x = 90.0;
				result.position.y = 95.0;
				result.width = 64.0;
				result.height = 32.0;
				result.objectType = tiled::MapLayerObjectType::TILE;
				result.tileGid = 4;
				return result;
			}

			tiled::MapLayerDefn createCommonMapLayerDefn() {
				tiled::MapLayerDefn result;
				result.id = 3;
				result.width = 3;
				result.height = 3;
				return result;
			}

			tiled::MapLayerDefn createTileMapLayerDefn() {
				tiled::MapLayerDefn result = createCommonMapLayerDefn();
				result.type = tiled::MapLayerType::TILE;
				result.data = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
				return result;
			}

			tiled::MapLayerDefn createObjectMapLayerDefn() {
				tiled::MapLayerObjectDefn objectDefn = createMapLayerObjectDefn();

				tiled::MapLayerDefn result = createCommonMapLayerDefn();
				result.type = tiled::MapLayerType::OBJECT;
				result.objectDefnList.push_back(objectDefn);
				return result;
			}

			bool testConvertToTileImageDefnList_Image() {
				tiled::MapTilesetDefn mapTilesetDefn = createMapTilesetDefn(1, "imagetileset.json");

				tiled::TilesetDefn tilesetDefn = createImageTilesetDefn();

				std::vector<GameTileImageDefn> tileImageDefnList = JsonGameMapLoader::convertToTileImageDefnList(mapTilesetDefn, tilesetDefn);

				bool allTileImageMatch = true;
				for (const auto& currTileImageDefn : tileImageDefnList) {
					allTileImageMatch = allTileImageMatch &&
						(currTileImageDefn.filename.compare("../textures/texture-atlas.png") == 0) &&
						(currTileImageDefn.imageSize.x == 105) &&
						(currTileImageDefn.imageSize.y == 39) &&
						(currTileImageDefn.textureRect.width == 32) &&
						(currTileImageDefn.textureRect.height == 16);
				}

				bool result =
					(tileImageDefnList.size() == 6) &&
					allTileImageMatch &&
					(tileImageDefnList[0].tileId == 1) &&
					(tileImageDefnList[0].textureRect.left == 3) &&
					(tileImageDefnList[0].textureRect.top == 3) &&
					(tileImageDefnList[5].tileId == 6) &&
					(tileImageDefnList[5].textureRect.left == 69) &&
					(tileImageDefnList[5].textureRect.top == 20);
				return result;
			}

			bool testConvertToTileImageDefnList_TileList() {
				tiled::MapTilesetDefn mapTilesetDefn = createMapTilesetDefn(7, "tilelist.json");

				tiled::TilesetDefn tilesetDefn = createTileListTilesetDefn();

				std::vector<GameTileImageDefn> tileImageDefnList = JsonGameMapLoader::convertToTileImageDefnList(mapTilesetDefn, tilesetDefn);

				bool allTileImageMatch = true;
				for (const auto& currTileImageDefn : tileImageDefnList) {
					allTileImageMatch = allTileImageMatch &&
						(currTileImageDefn.imageSize.x == 64) &&
						(currTileImageDefn.imageSize.y == 32) &&
						(currTileImageDefn.textureRect.width == 64) &&
						(currTileImageDefn.textureRect.height == 32);
				}

				bool result =
					(tileImageDefnList.size() == 2) &&
					allTileImageMatch &&
					(tileImageDefnList[0].filename.compare("../textures/floor1.png") == 0) &&
					(tileImageDefnList[1].filename.compare("../textures/floor2.png") == 0);
				return result;
			}

			bool testConvertToSpriteDefn_Success() {
				tiled::MapLayerObjectDefn sourceObjectDefn = createMapLayerObjectDefn();

				GameMapSpriteDefn spriteDefn = JsonGameMapLoader::convertToSpriteDefn(sourceObjectDefn);

				bool result =
					(spriteDefn.tileId == 4) &&
					(lround(spriteDefn.position.x) == 90) &&
					(lround(spriteDefn.position.y) == 95) &&
					(lround(spriteDefn.size.x) == 64) &&
					(lround(spriteDefn.size.y) == 32);
				return result;
			}

			bool testConvertToSpriteDefn_InvalidType() {
				tiled::MapLayerObjectDefn sourceObjectDefn = createMapLayerObjectDefn();
				sourceObjectDefn.objectType = tiled::MapLayerObjectType::RECTANGLE;

				try {
					JsonGameMapLoader::convertToSpriteDefn(sourceObjectDefn);
					return false;
				}
				catch (std::invalid_argument&) {
					return true;
				}
			}

			bool testConvertToLayerDefn_Tiles() {
				tiled::MapLayerDefn sourceLayerDefn = createTileMapLayerDefn();

				GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

				bool result =
					(layerDefn.layerType == GameMapLayerType::TILE) &&
					(!layerDefn.renderFlag) &&
					(!layerDefn.collisionFlag) &&
					(layerDefn.tileIdList.size() == 9) &&
					(layerDefn.tileIdList[4] == 1) &&
					(layerDefn.spriteDefnList.empty());
				return result;
			}

			bool testConvertToLayerDefn_Sprites() {
				tiled::MapLayerDefn sourceLayerDefn = createObjectMapLayerDefn();

				GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

				bool result =
					(layerDefn.layerType == GameMapLayerType::SPRITE) &&
					(!layerDefn.renderFlag) &&
					(!layerDefn.collisionFlag) &&
					(layerDefn.tileIdList.empty()) &&
					(layerDefn.spriteDefnList.size() == 1);
				return result;
			}

			bool testConvertToLayerDefn_RenderFlag() {
				tiled::MapLayerDefn sourceLayerDefn = createTileMapLayerDefn();
				sourceLayerDefn.propertyDefnList.push_back(createBoolPropertyDefn(LayerPropertyName::RENDER_FLAG, true));

				GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

				bool result =
					(layerDefn.layerType == GameMapLayerType::TILE) &&
					(layerDefn.renderFlag) &&
					(!layerDefn.collisionFlag) &&
					(layerDefn.tileIdList.size() == 9) &&
					(layerDefn.tileIdList[4] == 1) &&
					(layerDefn.spriteDefnList.empty());
				return result;
			}

			bool testConvertToLayerDefn_CollisionFlag() {
				tiled::MapLayerDefn sourceLayerDefn = createTileMapLayerDefn();
				sourceLayerDefn.propertyDefnList.push_back(createBoolPropertyDefn(LayerPropertyName::COLLISION_FLAG, true));

				GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

				bool result =
					(layerDefn.layerType == GameMapLayerType::TILE) &&
					(!layerDefn.renderFlag) &&
					(layerDefn.collisionFlag) &&
					(layerDefn.tileIdList.size() == 9) &&
					(layerDefn.tileIdList[4] == 1) &&
					(layerDefn.spriteDefnList.empty());
				return result;
			}

		}

	}

}
