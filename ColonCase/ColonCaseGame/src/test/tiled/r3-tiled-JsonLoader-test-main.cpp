
#include <assert.h>
#include <stdio.h>
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"
#include "r3-tiled-JsonCustomPropertyLoaderTests.hpp"
#include "r3-tiled-JsonTilesetLoaderTests.hpp"

using namespace r3::tiled;

void runJsonCustomPropertyLoaderTests() {
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Valid());

	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_InvalidRoot());

	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_MissingName());
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_InvalidName());

	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_MissingType());
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(JsonPropertyValue::CustomPropertyTypeValue::COLOR, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(JsonPropertyValue::CustomPropertyTypeValue::FILE, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(JsonPropertyValue::CustomPropertyTypeValue::STRING, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type("unknowntype", false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Type(3, false));

	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_MissingValue());
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, true, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "#ffcc9966", true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, "this ain't no color", false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::COLOR, 0xffcc9966, false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, 1.5, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, 1, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::FLOAT, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::FILE, "../path.file.png", true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::FILE, 5, false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, 1, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::INTEGER, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, 1, true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, -1, false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::OBJECT, "mismatch type", false));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::STRING, "anything", true));
	assert(JsonCustomPropertyLoaderTests::testValidateCustomProperty_Value(JsonPropertyValue::CustomPropertyTypeValue::STRING, 3, false));

	assert(JsonCustomPropertyLoaderTests::testLocalizeCustomPropertyValidationResult_Valid());
	assert(JsonCustomPropertyLoaderTests::testLocalizeCustomPropertyValidationResult_NameInvalid());
	assert(JsonCustomPropertyLoaderTests::testLocalizeCustomPropertyValidationResult_TypeInvalid());
	assert(JsonCustomPropertyLoaderTests::testLocalizeCustomPropertyValidationResult_ValueInvalid());

	assert(JsonCustomPropertyLoaderTests::testConvertToCustomPropertyDefn_Boolean());
	assert(JsonCustomPropertyLoaderTests::testConvertToCustomPropertyDefn_Color());
	assert(JsonCustomPropertyLoaderTests::testConvertToCustomPropertyDefn_Float());
	assert(JsonCustomPropertyLoaderTests::testConvertToCustomPropertyDefn_File());
	assert(JsonCustomPropertyLoaderTests::testConvertToCustomPropertyDefn_Integer());
	assert(JsonCustomPropertyLoaderTests::testConvertToCustomPropertyDefn_Object());
	assert(JsonCustomPropertyLoaderTests::testConvertToCustomPropertyDefn_String());
}

void runJsonTilesetLoaderTests() {
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_Valid());

	assert(JsonTilesetLoaderTests::testValidateTilesetImage_MissingImagePath());
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_InvalidImagePath());

	assert(JsonTilesetLoaderTests::testValidateTilesetImage_MissingImageWidth());
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_ImageWidth(64, true));
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_ImageWidth(0, false));
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_ImageWidth("cant be a string", false));

	assert(JsonTilesetLoaderTests::testValidateTilesetImage_MissingImageHeight());
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_ImageHeight(32, true));
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_ImageHeight(0, false));
	assert(JsonTilesetLoaderTests::testValidateTilesetImage_ImageHeight(true, false));

	assert(JsonTilesetLoaderTests::testValidateTilesetTile_Valid_NoPropertyList());
	assert(JsonTilesetLoaderTests::testValidateTilesetTile_Valid_WithPropertyList());

	assert(JsonTilesetLoaderTests::testValidateTilesetTile_InvalidRoot());

	assert(JsonTilesetLoaderTests::testValidateTilesetTile_MissingId());
	assert(JsonTilesetLoaderTests::testValidateTilesetTile_InvalidId());

	assert(JsonTilesetLoaderTests::testValidateTilesetTile_InvalidImage());

	assert(JsonTilesetLoaderTests::testValidateTilesetTile_InvalidPropertyList());

	assert(JsonTilesetLoaderTests::testValidateTileset_Valid());

	assert(JsonTilesetLoaderTests::testValidateTileset_MissingVersion());
	assert(JsonTilesetLoaderTests::testValidateTileset_InvalidVersion());

	assert(JsonTilesetLoaderTests::testValidateTileset_MissingType());
	assert(JsonTilesetLoaderTests::testValidateTileset_InvalidType());

	assert(JsonTilesetLoaderTests::testValidateTileset_MissingColumns());
	assert(JsonTilesetLoaderTests::testValidateTileset_Columns(0, true));
	assert(JsonTilesetLoaderTests::testValidateTileset_Columns(-1, false));
	assert(JsonTilesetLoaderTests::testValidateTileset_Columns("wrong type", false));

	assert(JsonTilesetLoaderTests::testValidateTileset_MissingTileCount());
	assert(JsonTilesetLoaderTests::testValidateTileset_TileCount(1, true));
	assert(JsonTilesetLoaderTests::testValidateTileset_TileCount(0, false));
	assert(JsonTilesetLoaderTests::testValidateTileset_TileCount("wrong type", false));

	assert(JsonTilesetLoaderTests::testValidateTileset_MissingTileWidth());
	assert(JsonTilesetLoaderTests::testValidateTileset_TileWidth(1, true));
	assert(JsonTilesetLoaderTests::testValidateTileset_TileWidth(0, false));
	assert(JsonTilesetLoaderTests::testValidateTileset_TileWidth("wrong type", false));

	assert(JsonTilesetLoaderTests::testValidateTileset_MissingTileHeight());
	assert(JsonTilesetLoaderTests::testValidateTileset_TileHeight(1, true));
	assert(JsonTilesetLoaderTests::testValidateTileset_TileHeight(0, false));
	assert(JsonTilesetLoaderTests::testValidateTileset_TileHeight("incorrect type", false));

	assert(JsonTilesetLoaderTests::testValidateTileset_MissingTilesetType());
	assert(JsonTilesetLoaderTests::testValidateTileset_EmptyMultiImageTileList());

	assert(JsonTilesetLoaderTests::testValidateTileset_InvalidSingleImage());
	
	assert(JsonTilesetLoaderTests::testValidateTileset_InvalidMultiImage());

	assert(JsonTilesetLoaderTests::testValidateTileset_InvalidPropertyList());

	assert(JsonTilesetLoaderTests::testConvertToTilesetImageDefn());

	assert(JsonTilesetLoaderTests::testConvertToTilesetTileDefn_EmptyPropertyList());
	assert(JsonTilesetLoaderTests::testConvertToTilesetTileDefn_WithPropertyList());

	assert(JsonTilesetLoaderTests::testConvertToTilesetDefn_SingleImage());
	assert(JsonTilesetLoaderTests::testConvertToTilesetDefn_MultiImage());
}

int main() {
	runJsonCustomPropertyLoaderTests();
	runJsonTilesetLoaderTests();

	printf("All tests passed!\n");
	return 0;
}
