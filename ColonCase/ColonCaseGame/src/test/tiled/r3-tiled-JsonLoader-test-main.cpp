
#include <assert.h>
#include <stdio.h>
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"
#include "r3-tiled-JsonCustomPropertyLoaderTests.hpp"
#include "r3-tiled-JsonTilesetLoaderTests.hpp"

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

	assert(JsonTilesetLoaderTests::testConvertToDefn_SingleImage());
	assert(JsonTilesetLoaderTests::testConvertToDefn_MultiImage());
}

int main() {
	runJsonCustomPropertyLoaderTests();

	runJsonTilesetImageLoaderTests();
	runJsonTilesetTileLoaderTests();
	runJsonTilesetLoaderTests();

	printf("All tests passed!\n");
	return 0;
}
