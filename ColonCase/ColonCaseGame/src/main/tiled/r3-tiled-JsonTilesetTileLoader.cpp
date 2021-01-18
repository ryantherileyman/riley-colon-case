
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonTilesetTileLoader {

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					result.idValid = JsonValidationUtils::requiredInt(jsonValue, JsonPropertyName::ID);
					result.imageValidationResult = JsonTilesetImageLoader::validate(jsonValue);

					if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
						Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
						for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
							result.propertyValidationResultList.push_back(JsonCustomPropertyLoader::validate(propertyListValue[index]));
						}
					}
				}

				return result;
			}

			std::string localizeTileListError(int index) {
				char resultStr[128];
				sprintf_s(resultStr, "Entry %d within the \"tiles\" array is invalid.  Individual error messages follow...", index);

				std::string result(resultStr);
				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				if (!validationResult.idValid) {
					result.push_back("The \"id\" is invalid.  It must be an integer of 0 or higher.");
				}

				std::vector<std::string> imageValidationResult = JsonTilesetImageLoader::localizeValidationResult(validationResult.imageValidationResult);
				result.insert(std::end(result), std::begin(imageValidationResult), std::end(imageValidationResult));

				for (size_t index = 0; index < validationResult.propertyValidationResultList.size(); index++) {
					auto& currPropertyValidationResult = validationResult.propertyValidationResultList[index];
					std::vector<std::string> currErrorList = JsonCustomPropertyLoader::localizeValidationResult(currPropertyValidationResult);

					if (!currErrorList.empty()) {
						result.push_back(JsonCustomPropertyLoader::localizePropertyListError(index + 1));
						result.insert(std::end(result), std::begin(currErrorList), std::end(currErrorList));
					}
				}

				return result;
			}

			TilesetTileDefn convertToDefn(const Json::Value& jsonValue) {
				TilesetTileDefn result;

				result.id = jsonValue[JsonPropertyName::ID].asInt();
				result.imageDefn = JsonTilesetImageLoader::convertToDefn(jsonValue);

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
						result.propertyDefnList.push_back(JsonCustomPropertyLoader::convertToDefn(propertyListValue[index]));
					}
				}

				return result;
			}

		}

	}

}
