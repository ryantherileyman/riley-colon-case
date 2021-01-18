
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

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				if (!validationResult.imagePathValid) {
					result.push_back("The \"image\" is invalid.  It must be a path to a valid image file.");
				}

				if (!validationResult.imageWidthValid) {
					result.push_back("The \"imagewidth\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.imageHeightValid) {
					result.push_back("The \"imageheight\" is invalid.  It must be an integer greater than 0.");
				}

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
