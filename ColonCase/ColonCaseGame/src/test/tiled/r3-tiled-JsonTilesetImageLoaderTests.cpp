
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

			bool testLocalizeValidationResult_Valid() {
				JsonTilesetImageLoader::ValidationResult validationResult;

				std::vector<std::string> errorList = JsonTilesetImageLoader::localizeValidationResult(validationResult);

				bool result = errorList.empty();
				return result;
			}

			bool testLocalizeValidationResult_ImagePathInvalid() {
				JsonTilesetImageLoader::ValidationResult validationResult;
				validationResult.imagePathValid = false;

				std::vector<std::string> errorList = JsonTilesetImageLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"image\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_ImageWidthInvalid() {
				JsonTilesetImageLoader::ValidationResult validationResult;
				validationResult.imageWidthValid = false;

				std::vector<std::string> errorList = JsonTilesetImageLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"imagewidth\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_ImageHeightInvalid() {
				JsonTilesetImageLoader::ValidationResult validationResult;
				validationResult.imageHeightValid = false;

				std::vector<std::string> errorList = JsonTilesetImageLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"imageheight\" is invalid") != std::string::npos);
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
