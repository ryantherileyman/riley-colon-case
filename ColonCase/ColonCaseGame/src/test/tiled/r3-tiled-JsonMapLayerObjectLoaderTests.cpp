
#include "r3-tiled-JsonMapLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerObjectLoaderTests {

			Json::Value createValidCustomPropertyJsonValue() {
				Json::Value result;
				result[JsonPropertyName::NAME] = "someProperty";
				result[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
				result[JsonPropertyName::VALUE] = "a value";
				return result;
			}

			Json::Value createValidMapLayerObjectPointJsonValue(double x, double y) {
				Json::Value result;
				result[JsonPropertyName::X] = x;
				result[JsonPropertyName::Y] = y;
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

			Json::Value createValidMapLayerPointJsonValue() {
				Json::Value result = createValidMapLayerObjectJsonValue();
				result[JsonPropertyName::WIDTH] = 0;
				result[JsonPropertyName::HEIGHT] = 0;
				result[JsonPropertyName::Map::POINT_FLAG] = true;
				return result;
			}

			Json::Value createValidMapLayerEllipseJsonValue() {
				Json::Value result = createValidMapLayerObjectJsonValue();
				result[JsonPropertyName::Map::ELLIPSE_FLAG] = true;
				return result;
			}

			Json::Value createValidPointListJsonValue() {
				Json::Value result = Json::arrayValue;
				result.append(createValidMapLayerObjectPointJsonValue(5, 0));
				result.append(createValidMapLayerObjectPointJsonValue(10, 10));
				result.append(createValidMapLayerObjectPointJsonValue(10, -10));
				return result;
			}

			Json::Value createValidMapLayerPolylineJsonValue() {
				Json::Value pointListJsonValue = createValidPointListJsonValue();

				Json::Value result = createValidMapLayerObjectJsonValue();
				result[JsonPropertyName::WIDTH] = 0;
				result[JsonPropertyName::HEIGHT] = 0;
				result[JsonPropertyName::Map::POLYLINE] = pointListJsonValue;
				return result;
			}

			Json::Value createValidMapLayerPolygonJsonValue() {
				Json::Value pointListJsonValue = createValidPointListJsonValue();

				Json::Value result = createValidMapLayerObjectJsonValue();
				result[JsonPropertyName::WIDTH] = 0;
				result[JsonPropertyName::HEIGHT] = 0;
				result[JsonPropertyName::Map::POLYGON] = pointListJsonValue;
				return result;
			}

			Json::Value createValidMapLayerTileJsonValue() {
				Json::Value result = createValidMapLayerObjectJsonValue();
				result[JsonPropertyName::Map::TILE_GID] = 5;
				return result;
			}

			bool testValidate_Valid_Rectangle() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_Point() {
				Json::Value jsonValue = createValidMapLayerPointJsonValue();

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_Ellipse() {
				Json::Value jsonValue = createValidMapLayerEllipseJsonValue();

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_Polyline() {
				Json::Value jsonValue = createValidMapLayerPolylineJsonValue();

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_Polygon() {
				Json::Value jsonValue = createValidMapLayerPolygonJsonValue();

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_Valid_Tile() {
				Json::Value jsonValue = createValidMapLayerTileJsonValue();

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidRoot() {
				Json::Value jsonValue = "should be an object";

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.rootValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingId() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::ID);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.idValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Id(const Json::Value& id, bool expectedIdValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue[JsonPropertyName::ID] = id;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.idValid == expectedIdValid);
				return result;
			}

			bool testValidate_MissingX() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::X);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.xValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_X(const Json::Value& xValue, bool expectedXValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue[JsonPropertyName::X] = xValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.xValid == expectedXValid);
				return result;
			}

			bool testValidate_MissingY() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::Y);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.yValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Y(const Json::Value& yValue, bool expectedYValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue[JsonPropertyName::Y] = yValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.yValid == expectedYValid);
				return result;
			}

			bool testValidate_MissingRotation() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::Map::ROTATION);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.rotationDegreesValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Rotation(const Json::Value& rotationValue, bool expectedRotationDegreesValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue[JsonPropertyName::Map::ROTATION] = rotationValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.rotationDegreesValid == expectedRotationDegreesValid);
				return result;
			}

			bool testValidate_MissingWidth() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::WIDTH);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.widthValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Width(bool pointFlag, const Json::Value& widthValue, bool expectedWidthValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				if (pointFlag) {
					jsonValue[JsonPropertyName::Map::POINT_FLAG] = true;
				}
				jsonValue[JsonPropertyName::WIDTH] = widthValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.widthValid == expectedWidthValid);
				return result;
			}

			bool testValidate_MissingHeight() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::HEIGHT);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.heightValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Height(bool pointFlag, const Json::Value& heightValue, bool expectedHeightValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				if (pointFlag) {
					jsonValue[JsonPropertyName::Map::POINT_FLAG] = true;
				}
				jsonValue[JsonPropertyName::HEIGHT] = heightValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.heightValid == expectedHeightValid);
				return result;
			}

			bool testValidate_InvalidObjectType_Point() {
				Json::Value jsonValue = createValidMapLayerPointJsonValue();
				jsonValue[JsonPropertyName::Map::POINT_FLAG] = false;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.objectTypeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidObjectType_Ellipse() {
				Json::Value jsonValue = createValidMapLayerEllipseJsonValue();
				jsonValue[JsonPropertyName::Map::ELLIPSE_FLAG] = false;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.objectTypeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidObjectType_Polyline() {
				Json::Value jsonValue = createValidMapLayerPolylineJsonValue();
				jsonValue[JsonPropertyName::Map::POLYLINE] = "should be an object";

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.objectTypeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidObjectType_Polygon() {
				Json::Value jsonValue = createValidMapLayerPolygonJsonValue();
				jsonValue[JsonPropertyName::Map::POLYGON] = "I object!";

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.objectTypeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidObjectType_Tile() {
				Json::Value jsonValue = createValidMapLayerTileJsonValue();
				jsonValue[JsonPropertyName::Map::TILE_GID] = "no guid";

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.objectTypeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_TileGid(const Json::Value& tileGidValue, bool expectedTileGidValid) {
				Json::Value jsonValue = createValidMapLayerTileJsonValue();
				jsonValue[JsonPropertyName::Map::TILE_GID] = tileGidValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.tileGidValid == expectedTileGidValid);
				return result;
			}

			bool testValidate_InvalidPolylinePointList() {
				Json::Value jsonValue = createValidMapLayerPolylineJsonValue();
				jsonValue[JsonPropertyName::Map::POLYLINE][0][JsonPropertyName::X] = "whoa";

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.pointValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidPolygonPointList() {
				Json::Value jsonValue = createValidMapLayerPolygonJsonValue();
				jsonValue[JsonPropertyName::Map::POLYGON][1][JsonPropertyName::Y] = "hmm";

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.pointValidationResultList.at(1).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingName() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::NAME);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.nameValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Name(const Json::Value& nameValue, bool expectedNameValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue[JsonPropertyName::NAME] = nameValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.nameValid == expectedNameValid);
				return result;
			}

			bool testValidate_MissingType() {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue.removeMember(JsonPropertyName::TYPE);

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.typeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Type(const Json::Value& typeValue, bool expectedTypeValid) {
				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue[JsonPropertyName::TYPE] = typeValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result = (validationResult.typeValid == expectedTypeValid);
				return result;
			}

			bool testValidate_InvalidPropertyList() {
				Json::Value propertyJsonValue = createValidCustomPropertyJsonValue();
				propertyJsonValue.removeMember(JsonPropertyName::NAME);

				Json::Value propertyListJsonValue = Json::arrayValue;
				propertyListJsonValue.append(propertyJsonValue);

				Json::Value jsonValue = createValidMapLayerObjectJsonValue();
				jsonValue[JsonPropertyName::PROPERTY_LIST] = propertyListJsonValue;

				JsonMapLayerObjectLoader::ValidationResult validationResult = JsonMapLayerObjectLoader::validate(jsonValue);

				bool result =
					!validationResult.propertyValidationResultList.at(0).isValid() &&
					!validationResult.isValid();
				return result;
			}

			bool testLocalizeObjectListError() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_Valid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_IdInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_XInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_YInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_RotationInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_WidthInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_HeightInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_ObjectTypeInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_TileGidInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_PointListInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_NameInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_TypeInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_PropertyListInvalid() {
				return false; // TODO
			}

			bool testConvertToDefn() {
				return false; // TODO
			}

		}

	}

}
