
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonTilesetImageLoader {

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.imagePathValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::Tileset::IMAGE_PATH);
				result.imageWidthValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_WIDTH);
				result.imageHeightValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_HEIGHT);

				return result;
			}

			TilesetImageDefn convertToDefn(const Json::Value& jsonValue) {
				TilesetImageDefn result;

				result.imagePath = jsonValue[JsonPropertyName::Tileset::IMAGE_PATH].asString();
				result.imageWidth = jsonValue[JsonPropertyName::Tileset::IMAGE_WIDTH].asInt();
				result.imageHeight = jsonValue[JsonPropertyName::Tileset::IMAGE_HEIGHT].asInt();

				return result;
			}

		}

	}

}
