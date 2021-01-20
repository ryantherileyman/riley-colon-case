
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerObjectLoader {

			MapLayerObjectType resolveObjectType(const Json::Value& jsonValue) {
				MapLayerObjectType result = MapLayerObjectType::RECTANGLE;

				int objectTypeBits = 0;

				if (jsonValue.isMember(JsonPropertyName::Map::POINT_FLAG)) {
					objectTypeBits += 1;
				}

				if (jsonValue.isMember(JsonPropertyName::Map::ELLIPSE_FLAG)) {
					objectTypeBits += 2;
				}
				
				if (jsonValue.isMember(JsonPropertyName::Map::POLYLINE)) {
					objectTypeBits += 4;
				}

				if (jsonValue.isMember(JsonPropertyName::Map::POLYGON)) {
					objectTypeBits += 8;
				}

				if (jsonValue.isMember(JsonPropertyName::Map::TILE_GID)) {
					objectTypeBits += 16;
				}

				if (objectTypeBits == 1) {
					result = MapLayerObjectType::POINT;
				}
				else if (objectTypeBits == 2) {
					result = MapLayerObjectType::ELLIPSE;
				}
				else if (objectTypeBits == 4) {
					result = MapLayerObjectType::POLYLINE;
				}
				else if (objectTypeBits == 8) {
					result = MapLayerObjectType::POLYGON;
				}
				else if (objectTypeBits == 16) {
					result = MapLayerObjectType::TILE;
				}

				return result;
			}

			void validatePointList(std::vector<JsonMapLayerObjectPointLoader::ValidationResult>& pointValidationResultList, const Json::Value& pointListJsonValue) {
				for (Json::ArrayIndex index = 0; index < pointListJsonValue.size(); index++) {
					pointValidationResultList.push_back(JsonMapLayerObjectPointLoader::validate(pointListJsonValue[index]));
				}
			}

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					MapLayerObjectType objectType = resolveObjectType(jsonValue);

					result.idValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::ID);
					result.xValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::X);
					result.yValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::Y);
					result.rotationDegreesValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::Map::ROTATION);

					result.widthValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::WIDTH);
					result.heightValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::HEIGHT);
					if (MapLayerObjectTypeUtils::expectsDimensions(objectType)) {
						result.widthValid = result.widthValid && (jsonValue[JsonPropertyName::WIDTH].asDouble() > 0.0);
						result.heightValid = result.heightValid && (jsonValue[JsonPropertyName::HEIGHT].asDouble() > 0.0);
					}

					if (objectType == MapLayerObjectType::POINT) {
						result.objectTypeValid =
							JsonValidationUtils::requiredBool(jsonValue, JsonPropertyName::Map::POINT_FLAG) &&
							jsonValue[JsonPropertyName::Map::POINT_FLAG].asBool();
					}
					else if (objectType == MapLayerObjectType::ELLIPSE) {
						result.objectTypeValid =
							JsonValidationUtils::requiredBool(jsonValue, JsonPropertyName::Map::ELLIPSE_FLAG) &&
							jsonValue[JsonPropertyName::Map::ELLIPSE_FLAG].asBool();
					}
					else if (objectType == MapLayerObjectType::POLYLINE) {
						result.objectTypeValid = JsonValidationUtils::requiredArray(jsonValue, JsonPropertyName::Map::POLYLINE);
						validatePointList(result.pointValidationResultList, jsonValue[JsonPropertyName::Map::POLYLINE]);
					}
					else if (objectType == MapLayerObjectType::POLYGON) {
						result.objectTypeValid = JsonValidationUtils::requiredArray(jsonValue, JsonPropertyName::Map::POLYGON);
						validatePointList(result.pointValidationResultList, jsonValue[JsonPropertyName::Map::POLYGON]);
					}
					else if (objectType == MapLayerObjectType::TILE) {
						result.objectTypeValid = JsonValidationUtils::requiredInt(jsonValue, JsonPropertyName::Map::TILE_GID);
						result.tileGidValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::Map::TILE_GID);
					}
					else if (objectType == MapLayerObjectType::UNKNOWN) {
						result.objectTypeValid = false;
					}

					result.nameValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::NAME);
					result.typeValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::TYPE);

					if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
						Json::Value propertyListJsonValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
						for (Json::ArrayIndex index = 0; index < propertyListJsonValue.size(); index++) {
							result.propertyValidationResultList.push_back(JsonCustomPropertyLoader::validate(propertyListJsonValue[index]));
						}
					}
				}

				return result;
			}

			std::string localizeObjectListError(int index) {
				char resultStr[128];
				sprintf_s(resultStr, "Entry %d within the \"objects\" array is invalid.  Individual error messages follow...", index);

				std::string result(resultStr);
				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				// TODO

				return result;
			}

			MapLayerObjectDefn convertToDefn(const Json::Value& jsonValue) {
				MapLayerObjectDefn result;

				// TODO

				return result;
			}

		}

	}

}
