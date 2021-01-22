
#include <assert.h>
#include <stdio.h>
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"
#include "r3-tiled-JsonCustomPropertyLoaderTests.hpp"
#include "r3-tiled-JsonTilesetLoaderTests.hpp"
#include "r3-tiled-JsonMapLoaderTests.hpp"

using namespace r3::tiled;

void runJsonCustomPropertyLoaderTests() {
	assert(JsonCustomPropertyLoaderTests::testValidate_Valid());

	assert(JsonCustomPropertyLoaderTests::testValidate_InvalidRoot());

	assert(JsonCustomPropertyLoaderTests::testValidate_MissingName());
	assert(JsonCustomPropertyLoaderTests::testValidate_InvalidName());

	assert(JsonCustomPropertyLoaderTests::testValidate_MissingType());
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::COLOR, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::FILE, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(JsonPropertyValue::CustomPropertyTypeValue::STRING, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type("unknowntype", false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Type(3, false));

	assert(JsonCustomPropertyLoaderTests::testValidate_MissingValue());
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, true, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "#ffcc9966", true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "this ain't no color", false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, 0xffcc9966, false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, 1.5, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, 1, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FILE, "../path.file.png", true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::FILE, 5, false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, 1, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, 1, true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, -1, false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::STRING, "anything", true));
	assert(JsonCustomPropertyLoaderTests::testValidate_Value(JsonPropertyValue::CustomPropertyTypeValue::STRING, 3, false));

	assert(JsonCustomPropertyLoaderTests::testLocalizeValidationResult_Valid());
	assert(JsonCustomPropertyLoaderTests::testLocalizeValidationResult_NameInvalid());
	assert(JsonCustomPropertyLoaderTests::testLocalizeValidationResult_TypeInvalid());
	assert(JsonCustomPropertyLoaderTests::testLocalizeValidationResult_ValueInvalid());

	assert(JsonCustomPropertyLoaderTests::testConvertToDefn_Boolean());
	assert(JsonCustomPropertyLoaderTests::testConvertToDefn_Color());
	assert(JsonCustomPropertyLoaderTests::testConvertToDefn_Float());
	assert(JsonCustomPropertyLoaderTests::testConvertToDefn_File());
	assert(JsonCustomPropertyLoaderTests::testConvertToDefn_Integer());
	assert(JsonCustomPropertyLoaderTests::testConvertToDefn_Object());
	assert(JsonCustomPropertyLoaderTests::testConvertToDefn_String());
}

void runJsonTilesetImageLoaderTests() {
	assert(JsonTilesetImageLoaderTests::testValidate_Valid());

	assert(JsonTilesetImageLoaderTests::testValidate_MissingImagePath());
	assert(JsonTilesetImageLoaderTests::testValidate_InvalidImagePath());

	assert(JsonTilesetImageLoaderTests::testValidate_MissingImageWidth());
	assert(JsonTilesetImageLoaderTests::testValidate_ImageWidth(64, true));
	assert(JsonTilesetImageLoaderTests::testValidate_ImageWidth(0, false));
	assert(JsonTilesetImageLoaderTests::testValidate_ImageWidth("cant be a string", false));

	assert(JsonTilesetImageLoaderTests::testValidate_MissingImageHeight());
	assert(JsonTilesetImageLoaderTests::testValidate_ImageHeight(32, true));
	assert(JsonTilesetImageLoaderTests::testValidate_ImageHeight(0, false));
	assert(JsonTilesetImageLoaderTests::testValidate_ImageHeight(true, false));

	assert(JsonTilesetImageLoaderTests::testLocalizeValidationResult_Valid());
	assert(JsonTilesetImageLoaderTests::testLocalizeValidationResult_ImagePathInvalid());
	assert(JsonTilesetImageLoaderTests::testLocalizeValidationResult_ImageWidthInvalid());
	assert(JsonTilesetImageLoaderTests::testLocalizeValidationResult_ImageHeightInvalid());

	assert(JsonTilesetImageLoaderTests::testConvertToDefn());
}

void runJsonTilesetTileLoaderTests() {
	assert(JsonTilesetTileLoaderTests::testValidate_Valid_NoPropertyList());
	assert(JsonTilesetTileLoaderTests::testValidate_Valid_WithPropertyList());

	assert(JsonTilesetTileLoaderTests::testValidate_InvalidRoot());

	assert(JsonTilesetTileLoaderTests::testValidate_MissingId());
	assert(JsonTilesetTileLoaderTests::testValidate_InvalidId());

	assert(JsonTilesetTileLoaderTests::testValidate_InvalidImage());

	assert(JsonTilesetTileLoaderTests::testValidate_InvalidPropertyList());

	assert(JsonTilesetTileLoaderTests::testLocalizeValidationResult_Valid());
	assert(JsonTilesetTileLoaderTests::testLocalizeValidationResult_IdInvalid());
	assert(JsonTilesetTileLoaderTests::testLocalizeValidationResult_ImageInvalid());
	assert(JsonTilesetTileLoaderTests::testLocalizeValidationResult_PropertyInvalid());

	assert(JsonTilesetTileLoaderTests::testConvertToDefn_EmptyPropertyList());
	assert(JsonTilesetTileLoaderTests::testConvertToDefn_WithPropertyList());
}

void runJsonTilesetLoaderTests() {
	assert(JsonTilesetLoaderTests::testValidate_Valid());

	assert(JsonTilesetLoaderTests::testValidate_MissingVersion());
	assert(JsonTilesetLoaderTests::testValidate_InvalidVersion());

	assert(JsonTilesetLoaderTests::testValidate_MissingType());
	assert(JsonTilesetLoaderTests::testValidate_InvalidType());

	assert(JsonTilesetLoaderTests::testValidate_MissingColumns());
	assert(JsonTilesetLoaderTests::testValidate_Columns(0, true));
	assert(JsonTilesetLoaderTests::testValidate_Columns(-1, false));
	assert(JsonTilesetLoaderTests::testValidate_Columns("wrong type", false));

	assert(JsonTilesetLoaderTests::testValidate_MissingTileCount());
	assert(JsonTilesetLoaderTests::testValidate_TileCount(1, true));
	assert(JsonTilesetLoaderTests::testValidate_TileCount(0, false));
	assert(JsonTilesetLoaderTests::testValidate_TileCount("wrong type", false));

	assert(JsonTilesetLoaderTests::testValidate_MissingTileWidth());
	assert(JsonTilesetLoaderTests::testValidate_TileWidth(1, true));
	assert(JsonTilesetLoaderTests::testValidate_TileWidth(0, false));
	assert(JsonTilesetLoaderTests::testValidate_TileWidth("wrong type", false));

	assert(JsonTilesetLoaderTests::testValidate_MissingTileHeight());
	assert(JsonTilesetLoaderTests::testValidate_TileHeight(1, true));
	assert(JsonTilesetLoaderTests::testValidate_TileHeight(0, false));
	assert(JsonTilesetLoaderTests::testValidate_TileHeight("incorrect type", false));

	assert(JsonTilesetLoaderTests::testValidate_MissingTilesetType());
	assert(JsonTilesetLoaderTests::testValidate_EmptyMultiImageTileList());

	assert(JsonTilesetLoaderTests::testValidate_InvalidSingleImage());
	
	assert(JsonTilesetLoaderTests::testValidate_InvalidMultiImage());

	assert(JsonTilesetLoaderTests::testValidate_InvalidPropertyList());

	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_Valid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_VersionInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_TypeInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_NameInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_ColumnsInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_TileCountInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_TileWidthInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_TileHeightInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_MarginInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_SpacingInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_TilesetTypeInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_ImageInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_TileInvalid());
	assert(JsonTilesetLoaderTests::testLocalizeValidationResult_PropertyInvalid());

	assert(JsonTilesetLoaderTests::testConvertToDefn_SingleImage());
	assert(JsonTilesetLoaderTests::testConvertToDefn_MultiImage());

	assert(JsonTilesetLoaderTests::testLoadFromJsonFile_InvalidJson());
	assert(JsonTilesetLoaderTests::testLoadFromJsonFile_InvalidTileset());
	assert(JsonTilesetLoaderTests::testLoadFromJsonFile_ValidTileset());
}

void runJsonMapLayerObjectPointLoaderTests() {
	assert(JsonMapLayerObjectPointLoaderTests::testValidate_Valid());

	assert(JsonMapLayerObjectPointLoaderTests::testValidate_InvalidRoot());

	assert(JsonMapLayerObjectPointLoaderTests::testValidate_MissingX());
	assert(JsonMapLayerObjectPointLoaderTests::testValidate_X(10, true));
	assert(JsonMapLayerObjectPointLoaderTests::testValidate_X(10.5, true));
	assert(JsonMapLayerObjectPointLoaderTests::testValidate_X("no strings allowed", false));

	assert(JsonMapLayerObjectPointLoaderTests::testValidate_MissingY());
	assert(JsonMapLayerObjectPointLoaderTests::testValidate_Y(20, true));
	assert(JsonMapLayerObjectPointLoaderTests::testValidate_Y(20.5, true));
	assert(JsonMapLayerObjectPointLoaderTests::testValidate_Y("uh", false));

	assert(JsonMapLayerObjectPointLoaderTests::testLocalizePointListError());

	assert(JsonMapLayerObjectPointLoaderTests::testLocalizeValidationResult_Valid());
	assert(JsonMapLayerObjectPointLoaderTests::testLocalizeValidationResult_XInvalid());
	assert(JsonMapLayerObjectPointLoaderTests::testLocalizeValidationResult_YInvalid());

	assert(JsonMapLayerObjectPointLoaderTests::testConvertToDefn());
}

void runJsonMapLayerObjectLoaderTests() {
	assert(JsonMapLayerObjectLoaderTests::testValidate_Valid_Rectangle());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Valid_Point());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Valid_Ellipse());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Valid_Polyline());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Valid_Polygon());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Valid_Tile());

	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidRoot());

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingId());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Id(1, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Id(0, false));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Id("wut", false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingX());
	assert(JsonMapLayerObjectLoaderTests::testValidate_X(1, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_X(1.5, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_X("nope", false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingY());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Y(-1, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Y(-1.5, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Y("um", false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingRotation());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Rotation(50, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Rotation(50.5, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Rotation("not a chance", false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingWidth());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Width(false, 1.5, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Width(true, 0, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Width(false, 0, false));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Width(false, -2, false));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Width(false, "ugh", false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingHeight());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Height(false, 100.5, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Height(true, 0, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Height(false, 0, false));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Height(false, -1, false));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Height(false, "no way", false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidObjectType_Point());
	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidObjectType_Ellipse());
	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidObjectType_Polyline());
	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidObjectType_Polygon());
	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidObjectType_Tile());

	assert(JsonMapLayerObjectLoaderTests::testValidate_TileGid(1, true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_TileGid(0, false));
	assert(JsonMapLayerObjectLoaderTests::testValidate_TileGid("nuh uh", false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidPolylinePointList());
	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidPolygonPointList());

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingName());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Name("The Thing", true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Name("", true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Name(1, false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_MissingType());
	assert(JsonMapLayerObjectLoaderTests::testValidate_Type("Goblin", true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Type("", true));
	assert(JsonMapLayerObjectLoaderTests::testValidate_Type(2, false));

	assert(JsonMapLayerObjectLoaderTests::testValidate_InvalidPropertyList());

	assert(JsonMapLayerObjectLoaderTests::testLocalizeObjectListError());

	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_Valid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_IdInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_XInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_YInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_RotationInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_WidthInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_HeightInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_ObjectTypeInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_TileGidInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_PointListInvalid_Polyline());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_PointListInvalid_Polygon());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_NameInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_TypeInvalid());
	assert(JsonMapLayerObjectLoaderTests::testLocalizeValidationResult_PropertyListInvalid());

	assert(JsonMapLayerObjectLoaderTests::testConvertToDefn_Rectangle());
	assert(JsonMapLayerObjectLoaderTests::testConvertToDefn_Point());
	assert(JsonMapLayerObjectLoaderTests::testConvertToDefn_Ellipse());
	assert(JsonMapLayerObjectLoaderTests::testConvertToDefn_Polyline());
	assert(JsonMapLayerObjectLoaderTests::testConvertToDefn_Polygon());
	assert(JsonMapLayerObjectLoaderTests::testConvertToDefn_Tile());
}

void runJsonMapLayerLoaderTests() {
	assert(JsonMapLayerLoaderTests::testValidate_Valid_Tile());
	assert(JsonMapLayerLoaderTests::testValidate_Valid_Object());
	assert(JsonMapLayerLoaderTests::testValidate_Valid_Group());

	assert(JsonMapLayerLoaderTests::testValidate_InvalidRoot());

	assert(JsonMapLayerLoaderTests::testValidate_MissingId());
	assert(JsonMapLayerLoaderTests::testValidate_Id(1, true));
	assert(JsonMapLayerLoaderTests::testValidate_Id(0, false));
	assert(JsonMapLayerLoaderTests::testValidate_Id("no", false));

	assert(JsonMapLayerLoaderTests::testValidate_MissingType());
	assert(JsonMapLayerLoaderTests::testValidate_Type(JsonPropertyValue::MapLayerTypeValue::TILE, true));
	assert(JsonMapLayerLoaderTests::testValidate_Type(JsonPropertyValue::MapLayerTypeValue::OBJECT, true));
	assert(JsonMapLayerLoaderTests::testValidate_Type(JsonPropertyValue::MapLayerTypeValue::GROUP, true));
	assert(JsonMapLayerLoaderTests::testValidate_Type("idontknowyou", false));
	assert(JsonMapLayerLoaderTests::testValidate_Type(5, false));

	assert(JsonMapLayerLoaderTests::testValidate_MissingName());
	assert(JsonMapLayerLoaderTests::testValidate_Name("Ground", true));
	assert(JsonMapLayerLoaderTests::testValidate_Name(42, false));

	assert(JsonMapLayerLoaderTests::testValidate_MissingWidth());
	assert(JsonMapLayerLoaderTests::testValidate_Width(1, true));
	assert(JsonMapLayerLoaderTests::testValidate_Width(0, false));
	assert(JsonMapLayerLoaderTests::testValidate_Width("5", false));

	assert(JsonMapLayerLoaderTests::testValidate_MissingHeight());
	assert(JsonMapLayerLoaderTests::testValidate_Height(1, true));
	assert(JsonMapLayerLoaderTests::testValidate_Height(0, false));
	assert(JsonMapLayerLoaderTests::testValidate_Height("1", false));

	assert(JsonMapLayerLoaderTests::testValidate_MissingData());
	assert(JsonMapLayerLoaderTests::testValidate_InvalidData_NotArray(1));
	assert(JsonMapLayerLoaderTests::testValidate_InvalidData_NotArray("huh"));
	assert(JsonMapLayerLoaderTests::testValidate_InvalidData_Size());
	assert(JsonMapLayerLoaderTests::testValidate_InvalidData_CellType());

	assert(JsonMapLayerLoaderTests::testValidate_InvalidObjectList());

	assert(JsonMapLayerLoaderTests::testValidate_InvalidLayerList());

	assert(JsonMapLayerLoaderTests::testValidate_InvalidPropertyList());

	assert(JsonMapLayerLoaderTests::testLocalizeObjectListError());

	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_Valid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_IdInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_TypeInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_NameInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_WidthInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_HeightInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_DataInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_ObjectListInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_LayerListInvalid());
	assert(JsonMapLayerLoaderTests::testLocalizeValidationResult_PropertyListInvalid());

	assert(JsonMapLayerLoaderTests::testConvertToDefn_Tile());
	assert(JsonMapLayerLoaderTests::testConvertToDefn_Object());
	assert(JsonMapLayerLoaderTests::testConvertToDefn_Group());
}

void runJsonMapTilesetLoaderTests() {
	assert(JsonMapTilesetLoaderTests::testValidate_Valid());

	assert(JsonMapTilesetLoaderTests::testValidate_InvalidRoot());

	assert(JsonMapTilesetLoaderTests::testValidate_MissingFirstGid());
	assert(JsonMapTilesetLoaderTests::testValidate_FirstGid(1, true));
	assert(JsonMapTilesetLoaderTests::testValidate_FirstGid(0, false));
	assert(JsonMapTilesetLoaderTests::testValidate_FirstGid("nope", false));

	assert(JsonMapTilesetLoaderTests::testValidate_MissingSourcePath());
	assert(JsonMapTilesetLoaderTests::testValidate_SourcePath("tileset.json", true));
	assert(JsonMapTilesetLoaderTests::testValidate_SourcePath(1, false));
}

int main() {
	runJsonCustomPropertyLoaderTests();

	runJsonTilesetImageLoaderTests();
	runJsonTilesetTileLoaderTests();
	runJsonTilesetLoaderTests();

	runJsonMapLayerObjectPointLoaderTests();
	runJsonMapLayerObjectLoaderTests();
	runJsonMapLayerLoaderTests();
	runJsonMapTilesetLoaderTests();

	printf("All tests passed!\n");
	return 0;
}
