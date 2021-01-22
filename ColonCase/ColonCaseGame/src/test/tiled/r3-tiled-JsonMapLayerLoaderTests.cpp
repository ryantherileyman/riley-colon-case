
#include "r3-tiled-JsonMapLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerLoaderTests {

			Json::Value createValidCustomPropertyJsonValue() {
				Json::Value result;
				result[JsonPropertyName::NAME] = "someProperty";
				result[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
				result[JsonPropertyName::VALUE] = "a value";
				return result;
			}

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
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue.removeMember(JsonPropertyName::WIDTH);

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.widthValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Width(const Json::Value& widthValue, bool expectedWidthValid) {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::WIDTH] = widthValue;

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result = (validationResult.widthValid == expectedWidthValid);
				return result;
			}

			bool testValidate_MissingHeight() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue.removeMember(JsonPropertyName::HEIGHT);

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.heightValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Height(const Json::Value& heightValue, bool expectedHeightValid) {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::HEIGHT] = heightValue;

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result = (validationResult.heightValid == expectedHeightValid);
				return result;
			}

			bool testValidate_MissingData() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue.removeMember(JsonPropertyName::Map::DATA);

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.dataValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidData_NotArray(const Json::Value& dataValue) {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::Map::DATA] = dataValue;

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.dataValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidData_Size() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::Map::DATA].append(15);

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.dataValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidData_CellType() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::Map::DATA][9] = "not an int";

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.dataValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidObjectList() {
				Json::Value jsonValue = createValidObjectMapLayerJsonValue();
				jsonValue[JsonPropertyName::Map::OBJECT_LIST][0][JsonPropertyName::Map::ROTATION] = "turn me away";

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.objectValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidLayerList() {
				Json::Value jsonValue = createValidGroupMapLayerJsonValue();
				jsonValue[JsonPropertyName::Map::LAYER_LIST][0][JsonPropertyName::ID] = "no!";

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.layerValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidPropertyList() {
				Json::Value propertyJsonValue = createCommonMapLayerJsonValue();
				propertyJsonValue.removeMember(JsonPropertyName::NAME);

				Json::Value propertyListJsonValue = Json::arrayValue;
				propertyListJsonValue.append(propertyJsonValue);

				Json::Value jsonValue = createValidTileMapLayerJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				JsonMapLayerLoader::ValidationResult validationResult = JsonMapLayerLoader::validate(jsonValue);

				bool result =
					!validationResult.propertyValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testLocalizeObjectListError() {
				std::string error = JsonMapLayerLoader::localizeObjectListError(3);

				bool result = (error.find("Entry 3 within the \"layers\" array is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_Valid() {
				JsonMapLayerLoader::ValidationResult validationResult;

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result = errorList.empty();
				return result;
			}

			bool testLocalizeValidationResult_IdInvalid() {
				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.idValid = false;

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"id\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_TypeInvalid() {
				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.typeValid = false;

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"type\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_NameInvalid() {
				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.nameValid = false;

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"name\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_WidthInvalid() {
				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.widthValid = false;

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"width\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_HeightInvalid() {
				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.heightValid = false;

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"height\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_DataInvalid() {
				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.dataValid = false;

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_ObjectListInvalid() {
				JsonMapLayerObjectLoader::ValidationResult objectValidationResult;
				objectValidationResult.idValid = false;

				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.layerType = MapLayerType::OBJECT;
				validationResult.objectValidationResultList.push_back(objectValidationResult);

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 2) &&
					(errorList.at(0).find("Entry 1 within the \"objects\" array is invalid") != std::string::npos) &&
					(errorList.at(1).find("The \"id\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_LayerListInvalid() {
				JsonMapLayerLoader::ValidationResult layerValidationResult;
				layerValidationResult.typeValid = false;

				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.layerType = MapLayerType::GROUP;
				validationResult.layerValidationResultList.push_back(layerValidationResult);

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 2) &&
					(errorList.at(0).find("Entry 1 within the \"layers\" array is invalid") != std::string::npos) &&
					(errorList.at(1).find("The \"type\" is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_PropertyListInvalid() {
				JsonCustomPropertyLoader::ValidationResult propertyValidationResult;
				propertyValidationResult.nameValid = false;

				JsonMapLayerLoader::ValidationResult validationResult;
				validationResult.layerType = MapLayerType::TILE;
				validationResult.propertyValidationResultList.push_back(propertyValidationResult);

				std::vector<std::string> errorList = JsonMapLayerLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 2) &&
					(errorList.at(0).find("Entry 1 within the \"properties\" array is invalid") != std::string::npos) &&
					(errorList.at(1).find("The \"name\" is invalid") != std::string::npos);
				return result;
			}

			bool testConvertToDefn_Common(const Json::Value& jsonValue, const MapLayerDefn& defn) {
				bool result =
					(defn.id == 3) &&
					(defn.name.compare("My Layer") == 0) &&
					(defn.width == 5) &&
					(defn.height == 2);
				return result;
			}

			bool testConvertToDefn_Tile() {
				Json::Value jsonValue = createValidTileMapLayerJsonValue();

				MapLayerDefn defn = JsonMapLayerLoader::convertToDefn(jsonValue);

				bool result =
					testConvertToDefn_Common(jsonValue, defn) &&
					(defn.type == MapLayerType::TILE) &&
					(defn.data.size() == 10);
				return result;
			}

			bool testConvertToDefn_Object() {
				Json::Value jsonValue = createValidObjectMapLayerJsonValue();

				MapLayerDefn defn = JsonMapLayerLoader::convertToDefn(jsonValue);

				bool result =
					testConvertToDefn_Common(jsonValue, defn) &&
					(defn.type == MapLayerType::OBJECT) &&
					(defn.objectDefnList.size() == 1);
				return result;
			}

			bool testConvertToDefn_Group() {
				Json::Value jsonValue = createValidGroupMapLayerJsonValue();

				MapLayerDefn defn = JsonMapLayerLoader::convertToDefn(jsonValue);

				bool result =
					testConvertToDefn_Common(jsonValue, defn) &&
					(defn.type == MapLayerType::GROUP) &&
					(defn.layerDefnList.size() == 2);
				return result;
			}

		}

	}

}
