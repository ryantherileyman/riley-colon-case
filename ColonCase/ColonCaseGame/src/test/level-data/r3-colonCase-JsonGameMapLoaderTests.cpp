
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
