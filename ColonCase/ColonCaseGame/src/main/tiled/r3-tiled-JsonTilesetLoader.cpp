
#include "r3-tiled-JsonLoader.hpp"
#include "../json/r3-jsoncpp-utils.hpp"
#include "../validation/r3-validation-utils.hpp"

using namespace r3::validation;

namespace r3 {

	namespace tiled {

		namespace JsonTilesetLoader {

			bool dimensionValueValid(const Json::Value& jsonValue, const char* propertyName) {
				bool result =
					JsonValidationUtils::requiredInt(jsonValue, propertyName) &&
					JsonValidationUtils::intInRange(jsonValue, propertyName, IntRange::createMin(1));
				return result;
			}

			LoadTilesetImageValidationResult validateTilesetImage(const Json::Value& jsonValue) {
				LoadTilesetImageValidationResult result;

				result.imagePathValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::Tileset::IMAGE_PATH);
				result.imageWidthValid = dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_WIDTH);
				result.imageHeightValid = dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_HEIGHT);

				return result;
			}

			LoadTilesetTileValidationResult validateTilesetTile(const Json::Value& jsonValue) {
				LoadTilesetTileValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					result.idValid = JsonValidationUtils::requiredInt(jsonValue, JsonPropertyName::ID);
					result.imageValidationResult = validateTilesetImage(jsonValue);

					if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
						Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
						for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
							result.propertyValidationResultList.push_back(JsonCustomPropertyLoader::validateCustomProperty(propertyListValue[index]));
						}
					}
				}

				return result;
			}

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

			LoadTilesetValidationResult validateTileset(const Json::Value& jsonValue) {
				LoadTilesetValidationResult result;

				result.versionValid = JsonValidationUtils::requiredFloat(jsonValue, JsonPropertyName::VERSION);
				result.typeValid = typeValueValid(jsonValue);
				result.nameValid = JsonValidationUtils::requiredString(jsonValue, JsonPropertyName::NAME);
				result.columnsValid = columnsValueValid(jsonValue);
				result.tileCountValid = dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_COUNT);
				result.tileWidthValid = dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_WIDTH);
				result.tileHeightValid = dimensionValueValid(jsonValue, JsonPropertyName::Tileset::TILE_HEIGHT);

				TilesetType tilesetType = resolveTilesetType(jsonValue);
				result.tilesetTypeValid = (tilesetType != TilesetType::UNKNOWN);

				switch (tilesetType) {

				case TilesetType::IMAGE:
					result.imageValidationResult.imageWidthValid = dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_WIDTH);
					result.imageValidationResult.imageHeightValid = dimensionValueValid(jsonValue, JsonPropertyName::Tileset::IMAGE_HEIGHT);
					break;

				case TilesetType::TILE_LIST:
					Json::Value tileListValue = jsonValue[JsonPropertyName::Tileset::TILE_LIST];
					for (Json::ArrayIndex index = 0; index < tileListValue.size(); index++) {
						result.tileValidationResultList.push_back(validateTilesetTile(tileListValue[index]));
					}
					break;
				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
						result.propertyValidationResultList.push_back(JsonCustomPropertyLoader::validateCustomProperty(propertyListValue[index]));
					}
				}

				return result;
			}

			TilesetImageDefn convertToTilesetImageDefn(const Json::Value& jsonValue) {
				TilesetImageDefn result;

				result.imagePath = jsonValue[JsonPropertyName::Tileset::IMAGE_PATH].asString();
				result.imageWidth = jsonValue[JsonPropertyName::Tileset::IMAGE_WIDTH].asInt();
				result.imageHeight = jsonValue[JsonPropertyName::Tileset::IMAGE_HEIGHT].asInt();

				return result;
			}

			TilesetTileDefn convertToTilesetTileDefn(const Json::Value& jsonValue) {
				TilesetTileDefn result;

				result.id = jsonValue[JsonPropertyName::ID].asInt();
				result.imageDefn = convertToTilesetImageDefn(jsonValue);

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
						result.propertyDefnList.push_back(JsonCustomPropertyLoader::convertToCustomPropertyDefn(propertyListValue[index]));
					}
				}

				return result;
			}

			TilesetDefn convertToTilesetDefn(const Json::Value& jsonValue) {
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
					result.imageDefn = convertToTilesetImageDefn(jsonValue);
					break;

				case TilesetType::TILE_LIST:
					if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::Tileset::TILE_LIST)) {
						Json::Value tileListValue = jsonValue[JsonPropertyName::Tileset::TILE_LIST];
						for (Json::ArrayIndex index = 0; index < tileListValue.size(); index++) {
							result.tileDefnList.push_back(convertToTilesetTileDefn(tileListValue[index]));
						}
					}
					break;

				}

				if (JsonValidationUtils::optionalArray(jsonValue, JsonPropertyName::PROPERTY_LIST)) {
					Json::Value propertyListValue = jsonValue[JsonPropertyName::PROPERTY_LIST];
					for (Json::ArrayIndex index = 0; index < propertyListValue.size(); index++) {
						result.propertyDefnList.push_back(JsonCustomPropertyLoader::convertToCustomPropertyDefn(propertyListValue[index]));
					}
				}

				return result;
			}

		}

	}

}
