
#include "r3-tiled-JsonMapLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerLoaderTests {

			Json::Value createCommonMapLayerJsonValue() {
				Json::Value result;
				result[JsonPropertyName::ID] = 3;
				result[JsonPropertyName::NAME] = "My Layer";
				result[JsonPropertyName::WIDTH] = 5;
				result[JsonPropertyName::HEIGHT] = 2;
				return result;
			}

			Json::Value createValidTileMapLayerJsonValue() {
				Json::Value dataJsonValue = Json::arrayValue;

				dataJsonValue[0] = 6;
				dataJsonValue[1] = 5;
				dataJsonValue[2] = 5;
				dataJsonValue[3] = 5;
				dataJsonValue[4] = 6;

				dataJsonValue[5] = 6;
				dataJsonValue[6] = 4;
				dataJsonValue[7] = 4;
				dataJsonValue[8] = 4;
				dataJsonValue[9] = 6;

				Json::Value result = createCommonMapLayerJsonValue();
				result[JsonPropertyName::TYPE] = JsonPropertyValue::MapLayerTypeValue::TILE;
				result[JsonPropertyName::Map::DATA] = dataJsonValue;
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

				Json::Value result = createCommonMapLayerJsonValue();
				result[JsonPropertyName::TYPE] = JsonPropertyValue::MapLayerTypeValue::OBJECT;
				result[JsonPropertyName::Map::OBJECT_LIST] = objectListJsonValue;
				return result;
			}

			Json::Value createValidGroupMapLayerJsonValue() {
				Json::Value layerListJsonValue = Json::arrayValue;
				layerListJsonValue.append(createValidTileMapLayerJsonValue());
				layerListJsonValue.append(createValidObjectMapLayerJsonValue());

				Json::Value result = createCommonMapLayerJsonValue();
				result[JsonPropertyName::TYPE] = JsonPropertyValue::MapLayerTypeValue::GROUP;
				result[JsonPropertyName::Map::LAYER_LIST] = layerListJsonValue;
				return result;
			}

			bool testValidate_Valid_Tile() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					(validationResult.layerType == MapLayerType::TILE) &&
					validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_Object() {
				Json::Value jsonValue = createValidObjectMapLayerJsonValue();

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					(validationResult.layerType == MapLayerType::OBJECT) &&
					validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_Group() {
				Json::Value jsonValue = createValidGroupMapLayerJsonValue();

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					(validationResult.layerType == MapLayerType::GROUP) &&
					validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidRoot() {
				Json::Value jsonValue = "where's mah object bro";

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.rootValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingId() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue.removeMember(JsonPropertyName::ID);

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.idValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Id(const Json::Value& idValue, bool expectedIdValid) {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::ID] = idValue;

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result = (validationResult.idValid == expectedIdValid);
				return result;
			}

			bool testValidate_MissingType() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue.removeMember(JsonPropertyName::TYPE);

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.typeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Type(const Json::Value& typeValue, bool expectedTypeValid) {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::TYPE] = typeValue;

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result = (validationResult.typeValid == expectedTypeValid);
				return result;
			}

			bool testValidate_MissingName() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue.removeMember(JsonPropertyName::NAME);

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.nameValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Name(const Json::Value& nameValue, bool expectedNameValid) {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::NAME] = nameValue;

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result = (validationResult.nameValid == expectedNameValid);
				return result;
			}

			bool testValidate_MissingWidth() {
				return false; // TODO
			}

			bool testValidate_Width(const Json::Value& widthValue, bool expectedWidthValid) {
				return false; // TODO
			}

			bool testValidate_MissingHeight() {
				return false; // TODO
			}

			bool testValidate_Height(const Json::Value& heightValue, bool expectedHeightValid) {
				return false; // TODO
			}

			bool testValidate_MissingData() {
				return false; // TODO
			}

			bool testValidate_InvalidData_NotArray(const Json::Value& jsonValue) {
				return false; // TODO
			}

			bool testValidate_InvalidData_Size() {
				return false; // TODO
			}

			bool testValidate_InvalidData_CellType() {
				return false; // TODO
			}

			bool testValidate_InvalidObjectList() {
				return false; // TODO
			}

			bool testValidate_InvalidLayerList() {
				return false; // TODO
			}

			bool testValidate_InvalidPropertyList() {
				return false; // TODO
			}

		}

	}

}
