
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
				char resultStr[128];
				sprintf_s(resultStr, "Entry %d within the \"layers\" array is invalid.  Individual error messages follow...", index);

				std::string result(resultStr);
				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				if (!validationResult.idValid) {
					result.push_back("The \"id\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.typeValid) {
					result.push_back("The \"type\" is invalid.  It must be one of \"tilelayer\", \"objectgrou\", or \"group\".");
				}

				if (!validationResult.nameValid) {
					result.push_back("The \"name\" is invalid.  It must be a string.");
				}

				if (!validationResult.widthValid) {
					result.push_back("The \"width\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.heightValid) {
					result.push_back("The \"height\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.dataValid) {
					result.push_back("The \"data\" is invalid.  It must be an array of integers.");
				}

				for (size_t index = 0; index < validationResult.objectValidationResultList.size(); index++) {
					auto& currObjectValidationResult = validationResult.objectValidationResultList[index];
					std::vector<std::string> currErrorList = JsonMapLayerObjectLoader::localizeValidationResult(currObjectValidationResult);

					if (!currErrorList.empty()) {
						result.push_back(JsonMapLayerObjectLoader::localizeObjectListError(index + 1));
						result.insert(std::end(result), std::begin(currErrorList), std::end(currErrorList));
					}
				}

				for (size_t index = 0; index < validationResult.layerValidationResultList.size(); index++) {
					auto& currLayerValidationResult = validationResult.layerValidationResultList[index];
					std::vector<std::string> currErrorList = JsonMapLayerLoader::localizeValidationResult(currLayerValidationResult);

					if (!currErrorList.empty()) {
						result.push_back(JsonMapLayerLoader::localizeObjectListError(index + 1));
						result.insert(std::end(result), std::begin(currErrorList), std::end(currErrorList));
					}
				}

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

			MapLayerDefn convertToDefn(const Json::Value& jsonValue) {
				MapLayerDefn result;

				result.id = jsonValue[JsonPropertyName::ID].asInt();
				result.type = convertToMapLayerType(jsonValue[JsonPropertyName::TYPE]);
				result.name = jsonValue[JsonPropertyName::NAME].asString();
				result.width = jsonValue[JsonPropertyName::WIDTH].asInt();
				result.height = jsonValue[JsonPropertyName::HEIGHT].asInt();

				if (result.type == MapLayerType::TILE) {
					const Json::Value& dataListJsonValue = jsonValue[JsonPropertyName::Map::DATA];
					for (Json::ArrayIndex index = 0; index < dataListJsonValue.size(); index++) {
						result.data.push_back(dataListJsonValue[index].asInt());
					}
				}
				else if (result.type == MapLayerType::OBJECT) {
					const Json::Value& objectListJsonValue = jsonValue[JsonPropertyName::Map::OBJECT_LIST];
					for (Json::ArrayIndex index = 0; index < objectListJsonValue.size(); index++) {
						result.objectDefnList.push_back(JsonMapLayerObjectLoader::convertToDefn(objectListJsonValue[index]));
					}
				}
				else if (result.type == MapLayerType::GROUP) {
					const Json::Value& groupListJsonValue = jsonValue[JsonPropertyName::Map::LAYER_LIST];
					for (Json::ArrayIndex index = 0; index < groupListJsonValue.size(); index++) {
						result.layerDefnList.push_back(JsonMapLayerLoader::convertToDefn(groupListJsonValue[index]));
					}
				}

				const Json::Value& propertyListJsonValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
				for (Json::ArrayIndex index = 0; index < propertyListJsonValue.size(); index++) {
					result.propertyDefnList.push_back(JsonCustomPropertyLoader::convertToDefn(propertyListJsonValue[index]));
				}

				return result;
			}

		}

	}

}
