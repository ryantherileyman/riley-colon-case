
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
					result.objectType = resolveObjectType(jsonValue);

					result.idValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::ID);
					result.xValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::X);
					result.yValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::Y);
					result.rotationDegreesValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::Map::ROTATION);

					result.widthValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::WIDTH);
					result.heightValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::HEIGHT);
					if (MapLayerObjectTypeUtils::expectsDimensions(result.objectType)) {
						result.widthValid = result.widthValid && (jsonValue[JsonPropertyName::WIDTH].asDouble() > 0.0);
						result.heightValid = result.heightValid && (jsonValue[JsonPropertyName::HEIGHT].asDouble() > 0.0);
					}

					if (result.objectType == MapLayerObjectType::POINT) {
						result.objectTypeValid =
							JsonValidationUtils::requiredBool(jsonValue, JsonPropertyName::Map::POINT_FLAG) &&
							jsonValue[JsonPropertyName::Map::POINT_FLAG].asBool();
					}
					else if (result.objectType == MapLayerObjectType::ELLIPSE) {
						result.objectTypeValid =
							JsonValidationUtils::requiredBool(jsonValue, JsonPropertyName::Map::ELLIPSE_FLAG) &&
							jsonValue[JsonPropertyName::Map::ELLIPSE_FLAG].asBool();
					}
					else if (result.objectType == MapLayerObjectType::POLYLINE) {
						result.objectTypeValid = JsonValidationUtils::requiredArray(jsonValue, JsonPropertyName::Map::POLYLINE);
						validatePointList(result.pointValidationResultList, jsonValue[JsonPropertyName::Map::POLYLINE]);
					}
					else if (result.objectType == MapLayerObjectType::POLYGON) {
						result.objectTypeValid = JsonValidationUtils::requiredArray(jsonValue, JsonPropertyName::Map::POLYGON);
						validatePointList(result.pointValidationResultList, jsonValue[JsonPropertyName::Map::POLYGON]);
					}
					else if (result.objectType == MapLayerObjectType::TILE) {
						result.objectTypeValid = JsonValidationUtils::requiredInt(jsonValue, JsonPropertyName::Map::TILE_GID);
						result.tileGidValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::Map::TILE_GID);
					}
					else if (result.objectType == MapLayerObjectType::UNKNOWN) {
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

				if (!validationResult.idValid) {
					result.push_back("The \"id\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.xValid) {
					result.push_back("The \"x\" value is invalid.  It must be a decimal value.");
				}

				if (!validationResult.yValid) {
					result.push_back("The \"y\" value is invalid.  It must be a decimal value.");
				}

				if (!validationResult.rotationDegreesValid) {
					result.push_back("The \"rotation\" value is invalid.  It must be a decimal value.");
				}

				if (!validationResult.widthValid) {
					result.push_back("The \"width\" is invalid.  It must be a decimal value.");
				}

				if (!validationResult.heightValid) {
					result.push_back("The \"height\" is invalid.  It must be a decimal value.");
				}

				if (!validationResult.objectTypeValid) {
					result.push_back("The type of object could not be determined.  A point must set \"point\" to \"true\".  An ellipse must set \"ellipse\" to \"true\".  A set of connected points must set \"polyline\" to an array of points.  A polygon must set \"polygon\" to an array of points.  A tile must set \"gid\" to an integer matching the id of a tile in a tileset.");
				}

				if (!validationResult.tileGidValid) {
					result.push_back("The \"gid\" value is invalid.  It must be an integer matching the id of a tile in a tileset.");
				}

				for (size_t index = 0; index < validationResult.pointValidationResultList.size(); index++) {
					auto& currPointValidationResult = validationResult.pointValidationResultList[index];
					std::vector<std::string> currErrorList = JsonMapLayerObjectPointLoader::localizeValidationResult(currPointValidationResult);

					if (!currErrorList.empty()) {
						if (validationResult.objectType == MapLayerObjectType::POLYLINE) {
							result.push_back(JsonMapLayerObjectPointLoader::localizePointListError(index + 1, JsonPropertyName::Map::POLYLINE));
						}
						else if ( validationResult.objectType == MapLayerObjectType::POLYGON ) {
							result.push_back(JsonMapLayerObjectPointLoader::localizePointListError(index + 1, JsonPropertyName::Map::POLYGON));
						}

						result.insert(std::end(result), std::begin(currErrorList), std::end(currErrorList));
					}
				}

				if (!validationResult.nameValid) {
					result.push_back("The \"name\" is invalid.  It must be a string.  Set to an empty string for no name.");
				}

				if (!validationResult.typeValid) {
					result.push_back("The \"type\" is invalid.  It must be a string.  Set to an empty string for no type.");
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

			MapLayerObjectDefn convertToDefn(const Json::Value& jsonValue) {
				MapLayerObjectDefn result;

				result.id = jsonValue[JsonPropertyName::ID].asInt();
				result.position.x = jsonValue[JsonPropertyName::X].asDouble();
				result.position.y = jsonValue[JsonPropertyName::Y].asDouble();
				result.rotationDegrees = jsonValue[JsonPropertyName::Map::ROTATION].asDouble();
				result.width = jsonValue[JsonPropertyName::WIDTH].asDouble();
				result.height = jsonValue[JsonPropertyName::HEIGHT].asDouble();
				result.objectType = resolveObjectType(jsonValue);

				if (result.objectType == MapLayerObjectType::POLYLINE) {
					Json::Value pointListJsonValue = jsonValue[JsonPropertyName::Map::POLYLINE];
					for (Json::ArrayIndex index = 0; index < pointListJsonValue.size(); index++) {
						result.pointDefnList.push_back(JsonMapLayerObjectPointLoader::convertToDefn(pointListJsonValue[index]));
					}
				}
				else if (result.objectType == MapLayerObjectType::POLYGON) {
					Json::Value pointListJsonValue = jsonValue[JsonPropertyName::Map::POLYGON];
					for (Json::ArrayIndex index = 0; index < pointListJsonValue.size(); index++) {
						result.pointDefnList.push_back(JsonMapLayerObjectPointLoader::convertToDefn(pointListJsonValue[index]));
					}
				}
				else if ( result.objectType == MapLayerObjectType::TILE ) {
					result.tileGid = jsonValue[JsonPropertyName::Map::TILE_GID].asInt();
				}

				result.name = jsonValue[JsonPropertyName::NAME].asString();
				result.type = jsonValue[JsonPropertyName::TYPE].asString();

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
