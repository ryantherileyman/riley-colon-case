
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLoader {

			MapOrientationType convertToMapOrientationType(const Json::Value& jsonValue) {
				MapOrientationType result = MapOrientationType::UNKNOWN;

				std::string jsonValueStr = jsonValue.asString();
				if (jsonValueStr.compare(JsonPropertyValue::MapOrientationValue::ORTHOGONAL) == 0) {
					result = MapOrientationType::ORTHOGONAL;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::MapOrientationValue::ISOMETRIC) == 0) {
					result = MapOrientationType::ISOMETRIC;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::MapOrientationValue::STAGGERED) == 0) {
					result = MapOrientationType::STAGGERED;
				}
				else if (jsonValueStr.compare(JsonPropertyValue::MapOrientationValue::HEXAGONAL) == 0) {
					result = MapOrientationType::HEXAGONAL;
				}

				return result;
			}

			bool mapOrientationTypeValid(const Json::Value& jsonValue) {
				bool result =
					JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::Map::ORIENTATION) &&
					(convertToMapOrientationType(jsonValue[JsonPropertyName::Map::ORIENTATION]) != MapOrientationType::UNKNOWN);
				return result;
			}

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.versionValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::VERSION);
				result.orientationValid = mapOrientationTypeValid(jsonValue);
				result.infiniteValid = JsonValidationUtils::requiredBool(jsonValue, JsonPropertyName::Map::INFINITE);
				result.widthValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::WIDTH);
				result.heightValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::HEIGHT);
				result.tileWidthValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_WIDTH);
				result.tileHeightValid = JsonLoaderUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_HEIGHT);

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::Map::TILESET_LIST)) {
					Json::Value tilesetListJsonValue = jsonValue[JsonPropertyName::Map::TILESET_LIST];
					for (Json::ArrayIndex index = 0; index < tilesetListJsonValue.size(); index++) {
						result.tilesetValidationResultList.push_back(JsonMapTilesetLoader::validate(tilesetListJsonValue[index]));
					}
				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::Map::LAYER_LIST)) {
					Json::Value layerListJsonValue = jsonValue[JsonPropertyName::Map::LAYER_LIST];
					for (Json::ArrayIndex index = 0; index < layerListJsonValue.size(); index++) {
						result.layerValidationResultList.push_back(JsonMapLayerLoader::validate(layerListJsonValue[index]));
					}
				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListJsonValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListJsonValue.size(); index++) {
						result.propertyValidationResultList.push_back(JsonCustomPropertyLoader::validate(propertyListJsonValue[index]));
					}
				}

				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				// TODO

				return result;
			}

			MapDefn convertToDefn(const Json::Value& jsonValue) {
				MapDefn result;

				// TODO

				return result;
			}

		}

	}

}
