
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"
#include "../validation/r3-validation-utils.hpp"

using namespace r3::validation;

namespace r3 {

	namespace tiled {

		namespace JsonTilesetLoader {

			bool typeValueValid(const Json::Value& jsonValue) {
				bool result = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::TYPE);
				if (result) {
					std::string typeValue = jsonValue[JsonPropertyName::TYPE].asString();
					result = (typeValue.compare(JsonPropertyValue::FileTypeValue::TILESET) == 0);
				}
				return result;
			}

			bool columnsValueValid(const Json::Value& jsonValue) {
				bool result =
					JsonValidationUtils::requiredInt(jsonValue, JsonPropertyName::Tileset::COLUMNS) &&
					JsonValidationUtils::intInRange(jsonValue, JsonPropertyName::Tileset::COLUMNS, IntRange::createMin(0));
				return result;
			}

			TilesetType resolveTilesetType(const Json::Value& jsonValue) {
				TilesetType result = TilesetType::UNKNOWN;

				bool isSingleImageFlag = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::Tileset::IMAGE_PATH);
				bool isMultiImageFlag = JsonValidationUtils::requiredArray(jsonValue, JsonPropertyName::Tileset::TILE_LIST);

				if (
					isSingleImageFlag &&
					!isMultiImageFlag
				) {
					result = TilesetType::IMAGE;
				}

				if (
					!isSingleImageFlag &&
					isMultiImageFlag &&
					(jsonValue[JsonPropertyName::Tileset::TILE_LIST].size() > 0)
				) {
					result = TilesetType::TILE_LIST;
				}

				return result;
			}

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.versionValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::VERSION);
				result.typeValid = typeValueValid(jsonValue);
				result.nameValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::NAME);
				result.columnsValid = columnsValueValid(jsonValue);
				result.tileCountValid = JsonTiledValidationUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_COUNT);
				result.tileWidthValid = JsonTiledValidationUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_WIDTH);
				result.tileHeightValid = JsonTiledValidationUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_HEIGHT);

				TilesetType tilesetType = resolveTilesetType(jsonValue);
				result.tilesetTypeValid = (tilesetType != TilesetType::UNKNOWN);

				switch (tilesetType) {

				case TilesetType::IMAGE:
					result.imageValidationResult.imageWidthValid = JsonTiledValidationUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_WIDTH);
					result.imageValidationResult.imageHeightValid = JsonTiledValidationUtils::dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_HEIGHT);
					break;

				case TilesetType::TILE_LIST:
					Json::Value tileListValue = jsonValue[JsonPropertyName::Tileset::TILE_LIST];
					for (Json::ArrayIndex index = 0; index < tileListValue.size(); index++) {
						result.tileValidationResultList.push_back(JsonTilesetTileLoader::validate(tileListValue[index]));
					}
					break;
				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
						result.propertyValidationResultList.push_back(JsonCustomPropertyLoader::validate(propertyListValue[index]));
					}
				}

				return result;
			}

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult) {
				std::vector<std::string> result;

				if (!validationResult.versionValid) {
					result.push_back("The \"version\" is invalid.  It must be a valid JSON file format version number.");
				}

				if (!validationResult.typeValid) {
					result.push_back("The \"type\" is invalid.  It must be \"tileset\".");
				}

				if (!validationResult.nameValid) {
					result.push_back("The \"name\" is invalid.  It must be a string.");
				}

				if (!validationResult.columnsValid ) {
					result.push_back("The \"columns\" is invalid.  It must be an integer of 0 or greater.");
				}

				if (!validationResult.tileCountValid) {
					result.push_back("The \"tilecount\" is invalid.  It must be an integer of 1 or greater.");
				}

				if (!validationResult.tileWidthValid) {
					result.push_back("The \"tilewidth\" is invalid.  It must be an integer of 1 or greater.");
				}

				if (!validationResult.tileHeightValid) {
					result.push_back("The \"tileheight\" is invalid.  It must be an integer of 1 or greater.");
				}

				if (!validationResult.marginValid) {
					result.push_back("The \"margin\" is invalid.  It must be an integer of 0 or greater.");
				}

				if (!validationResult.spacingValid) {
					result.push_back("The \"spacing\" is invalid.  It must be an integer of 0 or greater.");
				}

				if (!validationResult.tilesetTypeValid) {
					result.push_back("The tileset must contain either an \"image\" string referencing an image file (Based on Tileset Image), or a \"tiles\" array referencing multiple image files (Collection of Images).");
				}

				std::vector<std::string> imageValidationResult = JsonTilesetImageLoader::localizeValidationResult(validationResult.imageValidationResult);
				result.insert(std::end(result), std::begin(imageValidationResult), std::end(imageValidationResult));

				for (size_t index = 0; index < validationResult.tileValidationResultList.size(); index++) {
					auto& currTileValidationResult = validationResult.tileValidationResultList[index];
					std::vector<std::string> currErrorList = JsonTilesetTileLoader::localizeValidationResult(currTileValidationResult);

					if (!currErrorList.empty()) {
						result.push_back(JsonTilesetTileLoader::localizeTileListError(index + 1));
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

			TilesetDefn convertToDefn(const Json::Value& jsonValue) {
				TilesetDefn result;

				result.version = jsonValue[JsonPropertyName::VERSION].asFloat();
				result.type = resolveTilesetType(jsonValue);
				result.name = jsonValue[JsonPropertyName::NAME].asString();
				result.columns = jsonValue[JsonPropertyName::Tileset::COLUMNS].asInt();
				result.tileCount = jsonValue[JsonPropertyName::Tileset::TILE_COUNT].asInt();
				result.tileWidth = jsonValue[JsonPropertyName::Tileset::TILE_WIDTH].asInt();
				result.tileHeight = jsonValue[JsonPropertyName::Tileset::TILE_HEIGHT].asInt();
				result.margin = jsonValue[JsonPropertyName::Tileset::MARGIN].asInt();
				result.spacing = jsonValue[JsonPropertyName::Tileset::SPACING].asInt();

				switch (result.type) {

				case TilesetType::IMAGE:
					result.imageDefn = JsonTilesetImageLoader::convertToDefn(jsonValue);
					break;

				case TilesetType::TILE_LIST:
					if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::Tileset::TILE_LIST)) {
						Json::Value tileListValue = jsonValue[JsonPropertyName::Tileset::TILE_LIST];
						for (Json::ArrayIndex index = 0; index < tileListValue.size(); index++) {
							result.tileDefnList.push_back(JsonTilesetTileLoader::convertToDefn(tileListValue[index]));
						}
					}
					break;

				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
						result.propertyDefnList.push_back(JsonCustomPropertyLoader::convertToDefn(propertyListValue[index]));
					}
				}

				return result;
			}

			LoadTilesetResult loadFromJsonFile(const char* filePath) {
				LoadTilesetResult result;

				r3::JsonLoaderUtils::LoadJsonDataResult loadJsonDataResult = r3::JsonLoaderUtils::loadFromJsonFile(filePath);
				if (!loadJsonDataResult.parseErrorString.empty()) {
					result.errorList.push_back(loadJsonDataResult.parseErrorString);
				} else {
					ValidationResult validationResult = validate(loadJsonDataResult.jsonValue);
					if (!validationResult.isValid()) {
						result.errorList = localizeValidationResult(validationResult);
					} else {
						result.tilesetDefn = convertToDefn(loadJsonDataResult.jsonValue);
					}
				}

				return result;
			}

		}

	}

}
