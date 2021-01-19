
#include <assert.h>
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerObjectPointLoader {

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					result.xValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::X);
					result.yValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::Y);
				}

				return result;
			}

			std::string localizePointListError(int index, const char* listPropertyName) {
				assert(strlen(listPropertyName) <= 50);

				char resultStr[128];
				sprintf_s(resultStr, "Entry %d within the \"%s\" array is invalid.  Individual error messages follow...", index, listPropertyName);

				std::string result(resultStr);
				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				if (!validationResult.xValid) {
					result.push_back("The \"x\" value is invalid.  It must be a decimal value.");
				}

				if (!validationResult.yValid) {
					result.push_back("The \"y\" value is invalid.  It must be a decimal value.");
				}

				return result;
			}

			MapLayerObjectPointDefn convertToDefn(const Json::Value& jsonValue) {
				MapLayerObjectPointDefn result;

				result.x = jsonValue[JsonPropertyName::X].asDouble();
				result.y = jsonValue[JsonPropertyName::Y].asDouble();

				return result;
			}

		}

	}

}
