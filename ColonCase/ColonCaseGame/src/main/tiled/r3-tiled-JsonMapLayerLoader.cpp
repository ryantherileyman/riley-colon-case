
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerLoader {

			MapLayerType convertToMapLayerType(const Json::Value& jsonValue) {
				MapLayerType result = MapLayerType::UNKNOWN;

				std::string jsonValueStr = jsonValue.asString();
				if (jsonValueStr.compare(JsonPropertyValue::MapLayerTypeValue::TILE) == 0) {
					result = MapLayerType::TILE;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::MapLayerTypeValue::OBJECT) == 0) {
					result = MapLayerType::OBJECT;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::MapLayerTypeValue::GROUP) == 0) {
					result = MapLayerType::GROUP;
				}

				return result;
			}

			bool mapLayerTypeValid(const Json::Value& jsonValue) {
				bool result =
					JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::TYPE) &&
					(convertToMapLayerType(jsonValue[JsonPropertyName::TYPE]) != MapLayerType::UNKNOWN);
				return result;
			}

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					result.idValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::ID);

					result.typeValid = mapLayerTypeValid(jsonValue);
					if (result.typeValid) {
						result.layerType = convertToMapLayerType(jsonValue[JsonPropertyName::TYPE]);
					}

					result.nameValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::NAME);
				}

				// TODO

				return result;
			}

			std::string localizeObjectListError(int index) {
				std::string result;
				return result; // TODO
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				// TODO

				return result;
			}

			MapLayerDefn convertToDefn(const Json::Value& jsonValue) {
				MapLayerDefn result;

				// TODO

				return result;
			}

		}

	}

}
