
#include "r3-tiled-JsonMapLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLoaderTests {

			Json::Value createValidMapTilesetJsonValue() {
				Json::Value result;
				result[JsonPropertyName::Map::FIRST_GID] = 1;
				result[JsonPropertyName::Map::SOURCE_PATH] = "tilesets/characters.json";
				return result;
			}

			Json::Value createValidMapLayerObjectJsonValue() {
				Json::Value result;
				result[JsonPropertyName::ID] = 1;
				result[JsonPropertyName::X] = 35;
				result[JsonPropertyName::Y] = 47;
				result[JsonPropertyName::Map::ROTATION] = 90;
				result[JsonPropertyName::WIDTH] = 100;
				result[JsonPropertyName::HEIGHT] = 100;
				result[JsonPropertyName::NAME] = "An Object";
				result[JsonPropertyName::TYPE] = "Blob";
				return result;
			}

			Json::Value createValidObjectMapLayerJsonValue() {
				Json::Value objectListJsonValue = Json::arrayValue;
				objectListJsonValue.append(createValidMapLayerObjectJsonValue());

				Json::Value result;
				result[JsonPropertyName::ID] = 1;
				result[JsonPropertyName::NAME] = "Spawns";
				result[JsonPropertyName::WIDTH] = 5;
				result[JsonPropertyName::HEIGHT] = 2;
				result[JsonPropertyName::TYPE] = JsonPropertyValue::MapLayerTypeValue::OBJECT;
				result[JsonPropertyName::Map::OBJECT_LIST] = objectListJsonValue;
				return result;
			}

			Json::Value createValidMapJsonValue() {
				Json::Value tilesetListJsonValue = Json::arrayValue;
				tilesetListJsonValue.append(createValidMapTilesetJsonValue());

				Json::Value layerListJsonValue = Json::arrayValue;
				layerListJsonValue.append(createValidObjectMapLayerJsonValue());

				Json::Value result;
				result[JsonPropertyName::VERSION] = 1.4;
				result[JsonPropertyName::Map::ORIENTATION] = JsonPropertyValue::MapOrientationValue::ORTHOGONAL;
				result[JsonPropertyName::Map::INFINITE] = false;
				result[JsonPropertyName::WIDTH] = 5;
				result[JsonPropertyName::HEIGHT] = 2;
				result[JsonPropertyName::Tileset::TILE_WIDTH] = 128;
				result[JsonPropertyName::Tileset::TILE_HEIGHT] = 128;
				result[JsonPropertyName::Map::TILESET_LIST] = tilesetListJsonValue;
				result[JsonPropertyName::Map::LAYER_LIST] = layerListJsonValue;
				return result;
			}

			bool testValidate_Valid() {
				Json::Value jsonValue = createValidMapJsonValue();

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_MissingVersion() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue.removeMember(JsonPropertyName::VERSION);

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.versionValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Version(const Json::Value& versionJsonValue, bool expectedVersionValid) {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::VERSION] = versionJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = (validationResult.versionValid == expectedVersionValid);
				return result;
			}

			bool testValidate_MissingOrientation() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue.removeMember(JsonPropertyName::Map::ORIENTATION);

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.orientationValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Orientation(const Json::Value& orientationJsonValue, bool expectedOrientationValid) {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::Map::ORIENTATION] = orientationJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = (validationResult.orientationValid == expectedOrientationValid);
				return result;
			}

			bool testValidate_MissingInfinite() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue.removeMember(JsonPropertyName::Map::INFINITE);

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.infiniteValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Infinite(const Json::Value& infiniteJsonValue, bool expectedInfiniteValid) {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::Map::INFINITE] = infiniteJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = (validationResult.infiniteValid == expectedInfiniteValid);
				return result;
			}

			bool testValidate_MissingWidth() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue.removeMember(JsonPropertyName::WIDTH);

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.widthValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Width(const Json::Value& widthJsonValue, bool expectedWidthValid) {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::WIDTH] = widthJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = (validationResult.widthValid == expectedWidthValid);
				return result;
			}

			bool testValidate_MissingHeight() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue.removeMember(JsonPropertyName::HEIGHT);

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.heightValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Height(const Json::Value& heightJsonValue, bool expectedHeightValid) {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::HEIGHT] = heightJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = (validationResult.heightValid == expectedHeightValid);
				return result;
			}

			bool testValidate_MissingTileWidth() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::TILE_WIDTH);

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.tileWidthValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_TileWidth(const Json::Value& tileWidthJsonValue, bool expectedTileWidthValid) {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::Tileset::TILE_WIDTH] = tileWidthJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = (validationResult.tileWidthValid == expectedTileWidthValid);
				return result;
			}

			bool testValidate_MissingTileHeight() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue.removeMember(JsonPropertyName::Tileset::TILE_HEIGHT);

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.tileHeightValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_TileHeight(const Json::Value& tileHeightJsonValue, bool expectedTileHeightValid) {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::Tileset::TILE_HEIGHT] = tileHeightJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result = (validationResult.tileHeightValid == expectedTileHeightValid);
				return result;
			}

			bool testValidate_InvalidTilesetList() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::Map::TILESET_LIST][0][JsonPropertyName::Map::FIRST_GID] = "no";

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.tilesetValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidLayerList() {
				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::Map::LAYER_LIST][0][JsonPropertyName::ID] = "way";

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.layerValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidPropertyList() {
				Json::Value propertyJsonValue;
				propertyJsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
				propertyJsonValue[JsonPropertyName::VALUE] = "a value";

				Json::Value propertyListJsonValue = Json::arrayValue;
				propertyListJsonValue.append(propertyJsonValue);

				Json::Value jsonValue = createValidMapJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				JsonMapLoader::ValidationResult validationResult = JsonMapLoader::validate(jsonValue);

				bool result =
					!validationResult.propertyValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

		}

	}

}
