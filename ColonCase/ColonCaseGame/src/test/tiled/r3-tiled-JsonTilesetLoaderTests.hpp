
#include <json/json.h>
#pragma once

namespace r3 {

	namespace tiled {

		namespace JsonTilesetImageLoaderTests {

			bool testValidate_Valid();

			bool testValidate_MissingImagePath();
			bool testValidate_InvalidImagePath();

			bool testValidate_MissingImageWidth();
			bool testValidate_ImageWidth(const Json::Value& imageWidthValue, bool expectedImageWidthValid);

			bool testValidate_MissingImageHeight();
			bool testValidate_ImageHeight(const Json::Value& imageHeightValue, bool expectedImageHeightValid);

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_ImagePathInvalid();
			bool testLocalizeValidationResult_ImageWidthInvalid();
			bool testLocalizeValidationResult_ImageHeightInvalid();

			bool testConvertToDefn();

		}

		namespace JsonTilesetTileLoaderTests {

			bool testValidate_Valid_NoPropertyList();
			bool testValidate_Valid_WithPropertyList();

			bool testValidate_InvalidRoot();

			bool testValidate_MissingId();
			bool testValidate_InvalidId();

			bool testValidate_InvalidImage();

			bool testValidate_InvalidPropertyList();

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_IdInvalid();
			bool testLocalizeValidationResult_ImageInvalid();
			bool testLocalizeValidationResult_PropertyInvalid();

			bool testConvertToDefn_EmptyPropertyList();
			bool testConvertToDefn_WithPropertyList();

		}

		namespace JsonTilesetLoaderTests {

			bool testValidate_Valid();

			bool testValidate_MissingVersion();
			bool testValidate_InvalidVersion();

			bool testValidate_MissingType();
			bool testValidate_InvalidType();

			bool testValidate_MissingColumns();
			bool testValidate_Columns(const Json::Value& columnsValue, bool expectedColumnsValid);

			bool testValidate_MissingTileCount();
			bool testValidate_TileCount(const Json::Value& tileCountValue, bool expectedTileCountValid);

			bool testValidate_MissingTileWidth();
			bool testValidate_TileWidth(const Json::Value& tileWidthValue, bool expectedTileWidthValid);

			bool testValidate_MissingTileHeight();
			bool testValidate_TileHeight(const Json::Value& tileHeightValue, bool expectedTileHeightValid);

			bool testValidate_MissingTilesetType();
			bool testValidate_EmptyMultiImageTileList();

			bool testValidate_InvalidSingleImage();

			bool testValidate_InvalidMultiImage();

			bool testValidate_InvalidPropertyList();

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_VersionInvalid();
			bool testLocalizeValidationResult_TypeInvalid();
			bool testLocalizeValidationResult_NameInvalid();
			bool testLocalizeValidationResult_ColumnsInvalid();
			bool testLocalizeValidationResult_TileCountInvalid();
			bool testLocalizeValidationResult_TileWidthInvalid();
			bool testLocalizeValidationResult_TileHeightInvalid();
			bool testLocalizeValidationResult_MarginInvalid();
			bool testLocalizeValidationResult_SpacingInvalid();
			bool testLocalizeValidationResult_TilesetTypeInvalid();
			bool testLocalizeValidationResult_ImageInvalid();
			bool testLocalizeValidationResult_TileInvalid();
			bool testLocalizeValidationResult_PropertyInvalid();

			bool testConvertToDefn_SingleImage();
			bool testConvertToDefn_MultiImage();

		}

	}

}
