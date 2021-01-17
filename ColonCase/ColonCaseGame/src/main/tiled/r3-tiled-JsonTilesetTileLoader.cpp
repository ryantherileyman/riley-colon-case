
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
