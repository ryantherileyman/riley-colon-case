
#include <cmath>
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

			bool testLocalizeValidationResult_Valid() {
				JsonMapLoader::ValidationResult validationResult;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result = errorList.empty();
				return result;
			}

			bool testLocalizeValidationResult_VersionInvalid() {
				JsonMapLoader::ValidationResult validationResult;
				validationResult.versionValid = false;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"version\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_OrientationInvalid() {
				JsonMapLoader::ValidationResult validationResult;
				validationResult.orientationValid = false;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"orientation\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_InfiniteInvalid() {
				JsonMapLoader::ValidationResult validationResult;
				validationResult.infiniteValid = false;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"infinite\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_WidthInvalid() {
				JsonMapLoader::ValidationResult validationResult;
				validationResult.widthValid = false;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"width\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_HeightInvalid() {
				JsonMapLoader::ValidationResult validationResult;
				validationResult.heightValid = false;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"height\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_TileWidthInvalid() {
				JsonMapLoader::ValidationResult validationResult;
				validationResult.tileWidthValid = false;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"tilewidth\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_TileHeightInvalid() {
				JsonMapLoader::ValidationResult validationResult;
				validationResult.tileHeightValid = false;

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"tileheight\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_TilesetListInvalid() {
				JsonMapTilesetLoader::ValidationResult tilesetValidationResult;
				tilesetValidationResult.firstGidValid = false;

				JsonMapLoader::ValidationResult validationResult;
				validationResult.tilesetValidationResultList.push_back(tilesetValidationResult);

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 2) &&
					(errorList.at(0).find("Entry 1 within the \"tilesets\" array is invalid") != std::string::npos) &&
					(errorList.at(1).find("The \"firstgid\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_LayerListInvalid() {
				JsonMapLayerLoader::ValidationResult layerValidationResult;
				layerValidationResult.idValid = false;

				JsonMapLoader::ValidationResult validationResult;
				validationResult.layerValidationResultList.push_back(layerValidationResult);

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 2) &&
					(errorList.at(0).find("Entry 1 within the \"layers\" array is invalid") != std::string::npos) &&
					(errorList.at(1).find("The \"id\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_PropertyListInvalid() {
				JsonCustomPropertyLoader::ValidationResult propertyValidationResult;
				propertyValidationResult.nameValid = false;

				JsonMapLoader::ValidationResult validationResult;
				validationResult.propertyValidationResultList.push_back(propertyValidationResult);

				std::vector<std::string> errorList = JsonMapLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 2) &&
					(errorList.at(0).find("Entry 1 within the \"properties\" array is invalid") != std::string::npos) &&
					(errorList.at(1).find("The \"name\" is invalid") != std::string::npos);
				return result;
			}

			bool testConvertToDefn() {
				Json::Value jsonValue = createValidMapJsonValue();

				MapDefn defn = JsonMapLoader::convertToDefn(jsonValue);

				bool result =
					(lround(defn.version * 10) == 14l) &&
					(defn.orientation == MapOrientationType::ORTHOGONAL) &&
					(defn.infinite == false) &&
					(defn.width == 5) &&
					(defn.height == 2) &&
					(defn.tileWidth == 128) &&
					(defn.tileHeight == 128) &&
					(defn.tilesetDefnList.at(0).sourcePath.compare("tilesets/characters.json") == 0) &&
					(defn.layerDefnList.at(0).name.compare("Spawns") == 0);
				return result;
			}

			bool testLoadFromJsonFile_InvalidJson() {
				JsonMapLoader::LoadMapResult loadMapResult = JsonMapLoader::loadFromFile("resources/invalid_json.json");

				bool result =
					(loadMapResult.errorList.size() == 1) &&
					(loadMapResult.errorList.at(0).find("Missing '}' or object member name") != std::string::npos);
				return result;
			}

			bool testLoadFromJsonFile_InvalidMap() {
				JsonMapLoader::LoadMapResult loadMapResult = JsonMapLoader::loadFromFile("resources/invalid_map.json");

				bool result =
					(loadMapResult.errorList.size() == 1) &&
					(loadMapResult.errorList.at(0).find("The \"orientation\" is invalid") != std::string::npos);
				return result;
			}

			bool testLoadFromJsonFile_ValidMap() {
				JsonMapLoader::LoadMapResult loadMapResult = JsonMapLoader::loadFromFile("resources/valid_map.json");

				bool result =
					(loadMapResult.errorList.empty()) &&
					(loadMapResult.mapDefn.orientation == MapOrientationType::ORTHOGONAL);
				return result;
			}

		}

	}

}
