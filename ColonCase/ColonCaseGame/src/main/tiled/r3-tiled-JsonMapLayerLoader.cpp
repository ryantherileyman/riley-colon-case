
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

			bool dataValid(const Json::Value& jsonValue, int expectedDataSize) {
				bool result = JsonValidationUtils::requiredArray(jsonValue, JsonPropertyName::Map::DATA);

				if (result && (expectedDataSize > 0)) {
					result = result && (jsonValue[JsonPropertyName::Map::DATA].size() == expectedDataSize);
				}

				if (result) {
					Json::Value dataJsonValue = jsonValue[JsonPropertyName::Map::DATA];
					for (Json::ArrayIndex index = 0; index < dataJsonValue.size(); index++) {
						result = result &&
							dataJsonValue[index].isInt() &&
							(dataJsonValue[index].asInt() >= 0);
					}
				}

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
					result.widthValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::WIDTH);
					result.heightValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::HEIGHT);

					if (result.layerType == MapLayerType::TILE) {
						int expectedDataSize = 0;
						if (result.widthValid && result.heightValid) {
							expectedDataSize = jsonValue[JsonPropertyName::WIDTH].asInt() * jsonValue[JsonPropertyName::HEIGHT].asInt();
						}

						result.dataValid = dataValid(jsonValue, expectedDataSize);
					}
					else if (result.layerType == MapLayerType::OBJECT) {
						const Json::Value& objectListJsonValue = jsonValue[JsonPropertyName::Map::OBJECT_LIST];
						for (Json::ArrayIndex index = 0; index < objectListJsonValue.size(); index++) {
							result.objectValidationResultList.push_back(JsonMapLayerObjectLoader::validate(objectListJsonValue[index]));
						}
					}
					else if (result.layerType == MapLayerType::GROUP) {
						const Json::Value& layerListJsonValue = jsonValue[JsonPropertyName::Map::LAYER_LIST];
						for (Json::ArrayIndex index = 0; index < layerListJsonValue.size(); index++) {
							result.layerValidationResultList.push_back(JsonMapLayerLoader::validate(layerListJsonValue[index]));
						}
					}

					const Json::Value& propertyListJsonValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListJsonValue.size(); index++) {
						result.propertyValidationResultList.push_back(JsonCustomPropertyLoader::validate(propertyListJsonValue[index]));
					}
				}

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
