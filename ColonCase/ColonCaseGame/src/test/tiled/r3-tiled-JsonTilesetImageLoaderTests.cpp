
#include "r3-tiled-JsonTilesetLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonTilesetImageLoaderTests {

			Json::Value createValidTilesetImageJsonValue() {
				Json::Value result;
				result[JsonPropertyName::Tileset::IMAGE_PATH] = "../path/tileset.png";
				result[JsonPropertyName::Tileset::IMAGE_WIDTH] = 256;
				result[JsonPropertyName::Tileset::IMAGE_HEIGHT] = 128;
				return result;
			}

			bool testValidate_Valid() {
				Json::Value jsonValue = createValidTilesetImageJsonValue();

				JsonTilesetImageLoader::ValidationResult validationResult = JsonTilesetImageLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_MissingImagePath() {
				Json::Value jsonValue = createValidTilesetImageJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::IMAGE_PATH);

				JsonTilesetImageLoader::ValidationResult validationResult = JsonTilesetImageLoader::validate(jsonValue);

				bool result =
					!validationResult.imagePathValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidImagePath() {
				Json::Value jsonValue = createValidTilesetImageJsonValue();
				jsonValue[JsonPropertyName::Tileset::IMAGE_PATH] = 5;

				JsonTilesetImageLoader::ValidationResult validationResult = JsonTilesetImageLoader::validate(jsonValue);

				bool result =
					!validationResult.imagePathValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingImageWidth() {
				Json::Value jsonValue = createValidTilesetImageJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::IMAGE_WIDTH);

				JsonTilesetImageLoader::ValidationResult validationResult = JsonTilesetImageLoader::validate(jsonValue);

				bool result =
					!validationResult.imageWidthValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_ImageWidth(const Json::Value& imageWidthValue, bool expectedImageWidthValid) {
				Json::Value jsonValue = createValidTilesetImageJsonValue();
				jsonValue[JsonPropertyName::Tileset::IMAGE_WIDTH] = imageWidthValue;

				JsonTilesetImageLoader::ValidationResult validationResult = JsonTilesetImageLoader::validate(jsonValue);

				bool result = (validationResult.imageWidthValid == expectedImageWidthValid);
				return result;
			}

			bool testValidate_MissingImageHeight() {
				Json::Value jsonValue = createValidTilesetImageJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::IMAGE_HEIGHT);

				JsonTilesetImageLoader::ValidationResult validationResult = JsonTilesetImageLoader::validate(jsonValue);

				bool result =
					!validationResult.imageHeightValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_ImageHeight(const Json::Value& imageHeightValue, bool expectedImageHeightValid) {
				Json::Value jsonValue = createValidTilesetImageJsonValue();
				jsonValue[JsonPropertyName::Tileset::IMAGE_HEIGHT] = imageHeightValue;

				JsonTilesetImageLoader::ValidationResult validationResult = JsonTilesetImageLoader::validate(jsonValue);

				bool result = (validationResult.imageHeightValid == expectedImageHeightValid);
				return result;
			}

			bool testConvertToDefn() {
				Json::Value jsonValue = createValidTilesetImageJsonValue();

				TilesetImageDefn defn = JsonTilesetImageLoader::convertToDefn(jsonValue);

				bool result =
					(defn.imagePath.compare("../path/tileset.png") == 0) &&
					(defn.imageWidth == 256) &&
					(defn.imageHeight == 128);
				return result;
			}

		}

	}

}
