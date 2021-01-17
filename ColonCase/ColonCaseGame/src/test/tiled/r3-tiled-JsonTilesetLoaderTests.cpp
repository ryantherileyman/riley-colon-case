
#include <cmath>
#include "r3-tiled-JsonTilesetLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonTilesetLoaderTests {

			Json::Value createValidCustomPropertyJsonValue() {
				Json::Value result;
				result[JsonPropertyName::NAME] = "someProperty";
				result[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
				result[JsonPropertyName::VALUE] = "a value";
				return result;
			}

			Json::Value createValidTilesetImageJsonValue() {
				Json::Value result;
				result[JsonPropertyName::Tileset::IMAGE_PATH] = "../path/tileset.png";
				result[JsonPropertyName::Tileset::IMAGE_WIDTH] = 256;
				result[JsonPropertyName::Tileset::IMAGE_HEIGHT] = 128;
				return result;
			}


			Json::Value createValidTilesetTileJsonValue() {
				Json::Value result;
				result[JsonPropertyName::ID] = 5;
				result[JsonPropertyName::Tileset::IMAGE_PATH] = "../path/tileset.png";
				result[JsonPropertyName::Tileset::IMAGE_WIDTH] = 256;
				result[JsonPropertyName::Tileset::IMAGE_HEIGHT] = 128;
				return result;
			}

			Json::Value createValidTilesetJsonValue() {
				Json::Value result;
				result[JsonPropertyName::VERSION] = 1.4;
				result[JsonPropertyName::TYPE] = JsonPropertyValue::FileTypeValue::TILESET;
				result[JsonPropertyName::NAME] = "Ground";
				result[JsonPropertyName::Tileset::COLUMNS] = 0;
				result[JsonPropertyName::Tileset::TILE_COUNT] = 1;
				result[JsonPropertyName::Tileset::TILE_WIDTH] = 128;
				result[JsonPropertyName::Tileset::TILE_HEIGHT] = 64;
				result[JsonPropertyName::Tileset::MARGIN] = 2;
				result[JsonPropertyName::Tileset::SPACING] = 1;

				return result;
			}

			Json::Value createValidMultiImageTilesetJsonValue() {
				Json::Value tileValue1 = createValidTilesetTileJsonValue();

				Json::Value tileListValue;
				tileListValue[0] = tileValue1;

				Json::Value result = createValidTilesetJsonValue();
				result[JsonPropertyName::Tileset::TILE_LIST] = tileListValue;

				return result;
			}

			Json::Value createValidSingleImageTilesetJsonValue() {
				Json::Value result = createValidTilesetJsonValue();
				result[JsonPropertyName::Tileset::IMAGE_PATH] = "../resources/texture.png";
				result[JsonPropertyName::Tileset::IMAGE_WIDTH] = 512;
				result[JsonPropertyName::Tileset::IMAGE_HEIGHT] = 512;

				return result;
			}

			bool testValidate_Valid() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_MissingVersion() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue.removeMember(JsonPropertyName::VERSION);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.versionValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidVersion() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::VERSION] = "should be float";

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.versionValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingType() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue.removeMember(JsonPropertyName::TYPE);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.typeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidType() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::FileTypeValue::MAP;

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.typeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingColumns() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::COLUMNS);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.columnsValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Columns(const Json::Value& columnsValue, bool expectedColumnsValid) {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::Tileset::COLUMNS] = columnsValue;

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result = (validationResult.columnsValid == expectedColumnsValid);
				return result;
			}

			bool testValidate_MissingTileCount() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::TILE_COUNT);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.tileCountValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_TileCount(const Json::Value& tileCountValue, bool expectedTileCountValid) {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::Tileset::TILE_COUNT] = tileCountValue;

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result = (validationResult.tileCountValid == expectedTileCountValid);
				return result;
			}

			bool testValidate_MissingTileWidth() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::TILE_WIDTH);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.tileWidthValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_TileWidth(const Json::Value& tileWidthValue, bool expectedTileWidthValid) {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::Tileset::TILE_WIDTH] = tileWidthValue;

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result = (validationResult.tileWidthValid == expectedTileWidthValid);
				return result;
			}

			bool testValidate_MissingTileHeight() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::TILE_HEIGHT);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.tileHeightValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_TileHeight(const Json::Value& tileHeightValue, bool expectedTileHeightValid) {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::Tileset::TILE_HEIGHT] = tileHeightValue;

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result = (validationResult.tileHeightValid == expectedTileHeightValid);
				return result;
			}

			bool testValidate_MissingTilesetType() {
				Json::Value jsonValue = createValidTilesetJsonValue();

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.tilesetTypeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_EmptyMultiImageTileList() {
				Json::Value jsonValue = createValidTilesetJsonValue();
				jsonValue[JsonPropertyName::Tileset::TILE_LIST] = Json::arrayValue;

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.tilesetTypeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidSingleImage() {
				Json::Value jsonValue = createValidSingleImageTilesetJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::IMAGE_WIDTH);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.imageValidationResult.isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidMultiImage() {
				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::Tileset::TILE_LIST][0].removeMember(JsonPropertyName::Tileset::IMAGE_HEIGHT);

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.tileValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidPropertyList() {
				Json::Value propertyJsonValue = createValidCustomPropertyJsonValue();
				propertyJsonValue.removeMember(JsonPropertyName::NAME);

				Json::Value propertyListJsonValue;
				propertyListJsonValue[0] = propertyJsonValue;

				Json::Value jsonValue = createValidSingleImageTilesetJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				JsonTilesetLoader::ValidationResult validationResult = JsonTilesetLoader::validate(jsonValue);

				bool result =
					!validationResult.propertyValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testConvertToDefn_SingleImage() {
				Json::Value jsonValue = createValidSingleImageTilesetJsonValue();

				TilesetDefn defn = JsonTilesetLoader::convertToDefn(jsonValue);

				bool result =
					(lround(defn.version * 10) == 14) &&
					(defn.type == TilesetType::IMAGE) &&
					(defn.name.compare("Ground") == 0) &&
					(defn.columns == 0) &&
					(defn.tileCount == 1) &&
					(defn.tileWidth == 128) &&
					(defn.tileHeight == 64) &&
					(defn.margin == 2) &&
					(defn.spacing == 1) &&
					(defn.imageDefn.imagePath.compare("../resources/texture.png") == 0) &&
					(defn.imageDefn.imageWidth == 512) &&
					(defn.imageDefn.imageHeight == 512) &&
					(defn.tileDefnList.empty()) &&
					(defn.propertyDefnList.empty());
				return result;
			}

			bool testConvertToDefn_MultiImage() {
				Json::Value propertyListJsonValue;
				propertyListJsonValue[0] = createValidCustomPropertyJsonValue();

				Json::Value jsonValue = createValidMultiImageTilesetJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				TilesetDefn defn = JsonTilesetLoader::convertToDefn(jsonValue);

				bool result =
					(lround(defn.version * 10) == 14l) &&
					(defn.type == TilesetType::TILE_LIST) &&
					(defn.name.compare("Ground") == 0) &&
					(defn.columns == 0) &&
					(defn.tileCount == 1) &&
					(defn.tileWidth == 128) &&
					(defn.tileHeight == 64) &&
					(defn.margin == 2) &&
					(defn.spacing == 1) &&
					(defn.imageDefn.imagePath.length() == 0) &&
					(defn.tileDefnList.at(0).id == 5) &&
					(defn.propertyDefnList.at(0).name.compare("someProperty") == 0);
				return result;
			}

		}

	}

}
