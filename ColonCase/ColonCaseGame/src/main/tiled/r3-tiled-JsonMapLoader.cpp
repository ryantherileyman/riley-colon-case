
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

				if (!validationResult.versionValid) {
					result.push_back("The \"version\" is invalid.  It must be a valid JSON file format version number.");
				}

				if (!validationResult.orientationValid) {
					result.push_back("The \"orientation\" is invalid.  It must be one of \"orthogonal\", \"isometric\", \"staggered\", or \"hexagonal\".");
				}

				if (!validationResult.infiniteValid) {
					result.push_back("The \"infinite\" is invalid.  It must be true or false.");
				}

				if (!validationResult.widthValid) {
					result.push_back("The \"width\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.heightValid) {
					result.push_back("The \"height\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.tileWidthValid) {
					result.push_back("The \"tilewidth\" is invalid.  It must be an integer greater than 0.");
				}

				if (!validationResult.tileHeightValid) {
					result.push_back("The \"tileheight\" is invalid.  It must be an integer greater than 0.");
				}

				for (size_t index = 0; index < validationResult.tilesetValidationResultList.size(); index++) {
					const auto& currTilesetValidationResult = validationResult.tilesetValidationResultList[index];
					std::vector<std::string> currErrorList = JsonMapTilesetLoader::localizeValidationResult(currTilesetValidationResult);

					if (!currErrorList.empty()) {
						result.push_back(JsonMapTilesetLoader::localizeTilesetListError(index + 1));
						result.insert(std::end(result), std::begin(currErrorList), std::end(currErrorList));
					}
				}

				for (size_t index = 0; index < validationResult.layerValidationResultList.size(); index++) {
					const auto& currLayerValidationResult = validationResult.layerValidationResultList[index];
					std::vector<std::string> currErrorList = JsonMapLayerLoader::localizeValidationResult(currLayerValidationResult);

					if (!currErrorList.empty()) {
						result.push_back(JsonMapLayerLoader::localizeObjectListError(index + 1));
						result.insert(std::end(result), std::begin(currErrorList), std::end(currErrorList));
					}
				}

				for (size_t index = 0; index < validationResult.propertyValidationResultList.size(); index++) {
					const auto& currPropertyValidationResult = validationResult.propertyValidationResultList[index];
					std::vector<std::string> currErrorList = JsonCustomPropertyLoader::localizeValidationResult(currPropertyValidationResult);

					if (!currErrorList.empty()) {
						result.push_back(JsonCustomPropertyLoader::localizePropertyListError(index + 1));
						result.insert(std::end(result), std::begin(currErrorList), std::end(currErrorList));
					}
				}

				return result;
			}

			MapDefn convertToDefn(const Json::Value& jsonValue) {
				MapDefn result;

				result.version = jsonValue[JsonPropertyName::VERSION].asDouble();
				result.orientation = convertToMapOrientationType(jsonValue[JsonPropertyName::Map::ORIENTATION]);
				result.infinite = jsonValue[JsonPropertyName::Map::INFINITE].asBool();
				result.width = jsonValue[JsonPropertyName::WIDTH].asInt();
				result.height = jsonValue[JsonPropertyName::HEIGHT].asInt();
				result.tileWidth = jsonValue[JsonPropertyName::Tileset::TILE_WIDTH].asInt();
				result.tileHeight = jsonValue[JsonPropertyName::Tileset::TILE_HEIGHT].asInt();

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::Map::TILESET_LIST)) {
					Json::Value tilesetListJsonValue = jsonValue[JsonPropertyName::Map::TILESET_LIST];
					for (Json::ArrayIndex index = 0; index < tilesetListJsonValue.size(); index++) {
						result.tilesetDefnList.push_back(JsonMapTilesetLoader::convertToDefn(tilesetListJsonValue[index]));
					}
				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::Map::LAYER_LIST)) {
					Json::Value layerListJsonValue = jsonValue[JsonPropertyName::Map::LAYER_LIST];
					for (Json::ArrayIndex index = 0; index < layerListJsonValue.size(); index++) {
						result.layerDefnList.push_back(JsonMapLayerLoader::convertToDefn(layerListJsonValue[index]));
					}
				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListJsonValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListJsonValue.size(); index++) {
						result.propertyDefnList.push_back(JsonCustomPropertyLoader::convertToDefn(propertyListJsonValue[index]));
					}
				}

				return result;
			}

		}

	}

}
