
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapTilesetLoader {

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					result.firstGidValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::Map::FIRST_GID);
					result.sourcePathValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::Map::SOURCE_PATH);
				}

				return result;
			}

			std::string localizeTilesetListError(int index) {
				char resultStr[128];
				sprintf_s(resultStr, "Entry %d within the \"tilesets\" array is invalid.  Individual error messages follow...", index);

				std::string result(resultStr);
				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				if (!validationResult.firstGidValid) {
					result.push_back("The \"firstgid\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.sourcePathValid) {
					result.push_back("The \"source\" is invalid.  It must be a path to a valid tileset json file.");
				}

				return result;
			}

			MapTilesetDefn convertToDefn(const Json::Value& jsonValue) {
				MapTilesetDefn result;

				result.firstGid = jsonValue[JsonPropertyName::Map::FIRST_GID].asInt();
				result.sourcePath = jsonValue[JsonPropertyName::Map::SOURCE_PATH].asString();

				return result;
			}

		}

	}

}
