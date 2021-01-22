
#include <json/json.h>
#pragma once

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerObjectPointLoaderTests {

			bool testValidate_Valid();

			bool testValidate_InvalidRoot();

			bool testValidate_MissingX();
			bool testValidate_X(const Json::Value& xValue, bool expectedXValid);

			bool testValidate_MissingY();
			bool testValidate_Y(const Json::Value& yValue, bool expectedYValid);

			bool testLocalizePointListError();

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_XInvalid();
			bool testLocalizeValidationResult_YInvalid();

			bool testConvertToDefn();

		}

		namespace JsonMapLayerObjectLoaderTests {

			bool testValidate_Valid_Rectangle();
			bool testValidate_Valid_Point();
			bool testValidate_Valid_Ellipse();
			bool testValidate_Valid_Polyline();
			bool testValidate_Valid_Polygon();
			bool testValidate_Valid_Tile();

			bool testValidate_InvalidRoot();

			bool testValidate_MissingId();
			bool testValidate_Id(const Json::Value& id, bool expectedIdValid);

			bool testValidate_MissingX();
			bool testValidate_X(const Json::Value& xValue, bool expectedXValid);

			bool testValidate_MissingY();
			bool testValidate_Y(const Json::Value& yValue, bool expectedYValid);

			bool testValidate_MissingRotation();
			bool testValidate_Rotation(const Json::Value& rotationValue, bool expectedRotationDegreesValid);

			bool testValidate_MissingWidth();
			bool testValidate_Width(bool pointFlag, const Json::Value& widthValue, bool expectedWidthValid);

			bool testValidate_MissingHeight();
			bool testValidate_Height(bool pointFlag, const Json::Value& heightValue, bool expectedHeightValid);

			bool testValidate_InvalidObjectType_Point();
			bool testValidate_InvalidObjectType_Ellipse();
			bool testValidate_InvalidObjectType_Polyline();
			bool testValidate_InvalidObjectType_Polygon();
			bool testValidate_InvalidObjectType_Tile();

			bool testValidate_TileGid(const Json::Value& tileGidValue, bool expectedTileGidValid);

			bool testValidate_InvalidPolylinePointList();
			bool testValidate_InvalidPolygonPointList();

			bool testValidate_MissingName();
			bool testValidate_Name(const Json::Value& nameValue, bool expectedNameValid);

			bool testValidate_MissingType();
			bool testValidate_Type(const Json::Value& typeValue, bool expectedTypeValid);

			bool testValidate_InvalidPropertyList();

			bool testLocalizeObjectListError();

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_IdInvalid();
			bool testLocalizeValidationResult_XInvalid();
			bool testLocalizeValidationResult_YInvalid();
			bool testLocalizeValidationResult_RotationInvalid();
			bool testLocalizeValidationResult_WidthInvalid();
			bool testLocalizeValidationResult_HeightInvalid();
			bool testLocalizeValidationResult_ObjectTypeInvalid();
			bool testLocalizeValidationResult_TileGidInvalid();
			bool testLocalizeValidationResult_PointListInvalid_Polyline();
			bool testLocalizeValidationResult_PointListInvalid_Polygon();
			bool testLocalizeValidationResult_NameInvalid();
			bool testLocalizeValidationResult_TypeInvalid();
			bool testLocalizeValidationResult_PropertyListInvalid();

			bool testConvertToDefn_Rectangle();
			bool testConvertToDefn_Point();
			bool testConvertToDefn_Ellipse();
			bool testConvertToDefn_Polyline();
			bool testConvertToDefn_Polygon();
			bool testConvertToDefn_Tile();

		}

		namespace JsonMapLayerLoaderTests {

			bool testValidate_Valid_Tile();
			bool testValidate_Valid_Object();
			bool testValidate_Valid_Group();

			bool testValidate_InvalidRoot();

			bool testValidate_MissingId();
			bool testValidate_Id(const Json::Value& idValue, bool expectedIdValid);
			
			bool testValidate_MissingType();
			bool testValidate_Type(const Json::Value& typeValue, bool expectedTypeValid);

			bool testValidate_MissingName();
			bool testValidate_Name(const Json::Value& nameValue, bool expectedNameValid);

			bool testValidate_MissingWidth();
			bool testValidate_Width(const Json::Value& widthValue, bool expectedWidthValid);

			bool testValidate_MissingHeight();
			bool testValidate_Height(const Json::Value& heightValue, bool expectedHeightValid);

			bool testValidate_MissingData();
			bool testValidate_InvalidData_NotArray(const Json::Value& dataValue);
			bool testValidate_InvalidData_Size();
			bool testValidate_InvalidData_CellType();

			bool testValidate_InvalidObjectList();

			bool testValidate_InvalidLayerList();

			bool testValidate_InvalidPropertyList();

			bool testLocalizeObjectListError();

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_IdInvalid();
			bool testLocalizeValidationResult_TypeInvalid();
			bool testLocalizeValidationResult_NameInvalid();
			bool testLocalizeValidationResult_WidthInvalid();
			bool testLocalizeValidationResult_HeightInvalid();
			bool testLocalizeValidationResult_DataInvalid();
			bool testLocalizeValidationResult_ObjectListInvalid();
			bool testLocalizeValidationResult_LayerListInvalid();
			bool testLocalizeValidationResult_PropertyListInvalid();

			bool testConvertToDefn_Tile();
			bool testConvertToDefn_Object();
			bool testConvertToDefn_Group();

		}

	}

}
