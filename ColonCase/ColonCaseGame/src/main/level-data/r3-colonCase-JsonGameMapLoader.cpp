
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

		}

	}

}
