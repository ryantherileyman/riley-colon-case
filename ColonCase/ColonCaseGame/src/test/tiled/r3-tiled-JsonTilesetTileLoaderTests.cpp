
#include "r3-tiled-JsonTilesetLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonTilesetTileLoaderTests {

			Json::Value createValidCustomPropertyJsonValue() {
				Json::Value result;
				result[JsonPropertyName::NAME] = "someProperty";
				result[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
				result[JsonPropertyName::VALUE] = "a value";
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

			bool testValidate_Valid_NoPropertyList() {
				Json::Value jsonValue = createValidTilesetTileJsonValue();

				JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_WithPropertyList() {
				Json::Value propertyListJsonValue;
				propertyListJsonValue[0] = createValidCustomPropertyJsonValue();

				Json::Value jsonValue = createValidTilesetTileJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidRoot() {
				Json::Value jsonValue = "should be an object";

				JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

				bool result =
					!validationResult.rootValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingId() {
				Json::Value jsonValue = createValidTilesetTileJsonValue();
				jsonValue.removeMember(JsonPropertyName::ID);

				JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

				bool result =
					!validationResult.idValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidId() {
				Json::Value jsonValue = createValidTilesetTileJsonValue();
				jsonValue[JsonPropertyName::ID] = "no strings allowed";

				JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

				bool result =
					!validationResult.idValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidImage() {
				Json::Value jsonValue = createValidTilesetTileJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::IMAGE_PATH);

				JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

				bool result =
					!validationResult.imageValidationResult.isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidPropertyList() {
				Json::Value propertyJsonValue = createValidCustomPropertyJsonValue();
				propertyJsonValue.removeMember(JsonPropertyName::NAME);

				Json::Value propertyListJsonValue;
				propertyListJsonValue[0] = propertyJsonValue;

				Json::Value jsonValue = createValidTilesetTileJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				JsonTilesetTileLoader::ValidationResult validationResult = JsonTilesetTileLoader::validate(jsonValue);

				bool result =
					!validationResult.propertyValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testConvertToDefn_EmptyPropertyList() {
				Json::Value jsonValue = createValidTilesetTileJsonValue();

				TilesetTileDefn defn = JsonTilesetTileLoader::convertToDefn(jsonValue);

				bool result =
					(defn.id == 5) &&
					(defn.imageDefn.imagePath.compare("../path/tileset.png") == 0) &&
					(defn.imageDefn.imageWidth == 256) &&
					(defn.imageDefn.imageHeight == 128) &&
					(defn.propertyDefnList.empty());
				return result;
			}

			bool testConvertToDefn_WithPropertyList() {
				Json::Value propertyListJsonValue;
				propertyListJsonValue[0] = createValidCustomPropertyJsonValue();

				Json::Value jsonValue = createValidTilesetTileJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				TilesetTileDefn defn = JsonTilesetTileLoader::convertToDefn(jsonValue);

				bool result =
					(defn.id == 5) &&
					(defn.imageDefn.imagePath.compare("../path/tileset.png") == 0) &&
					(defn.imageDefn.imageWidth == 256) &&
					(defn.imageDefn.imageHeight == 128) &&
					(defn.propertyDefnList.at(0).name.compare("someProperty") == 0);
				return result;
			}

		}

	}

}
