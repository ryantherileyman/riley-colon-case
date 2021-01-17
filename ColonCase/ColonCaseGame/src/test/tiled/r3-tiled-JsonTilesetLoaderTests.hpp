
#include <json/json.h>
#pragma once

namespace r3 {

	namespace tiled {

		namespace JsonTilesetLoaderTests {

			bool testValidateTilesetImage_Valid();

			bool testValidateTilesetImage_MissingImagePath();
			bool testValidateTilesetImage_InvalidImagePath();

			bool testValidateTilesetImage_MissingImageWidth();
			bool testValidateTilesetImage_ImageWidth(const Json::Value& imageWidthValue, bool expectedImageWidthValid);

			bool testValidateTilesetImage_MissingImageHeight();
			bool testValidateTilesetImage_ImageHeight(const Json::Value& imageHeightValue, bool expectedImageHeightValid);

			bool testValidateTilesetTile_Valid_NoPropertyList();
			bool testValidateTilesetTile_Valid_WithPropertyList();

			bool testValidateTilesetTile_InvalidRoot();

			bool testValidateTilesetTile_MissingId();
			bool testValidateTilesetTile_InvalidId();

			bool testValidateTilesetTile_InvalidImage();

			bool testValidateTilesetTile_InvalidPropertyList();

			bool testValidateTileset_Valid();

			bool testValidateTileset_MissingVersion();
			bool testValidateTileset_InvalidVersion();

			bool testValidateTileset_MissingType();
			bool testValidateTileset_InvalidType();

			bool testValidateTileset_MissingColumns();
			bool testValidateTileset_Columns(const Json::Value& columnsValue, bool expectedColumnsValid);

			bool testValidateTileset_MissingTileCount();
			bool testValidateTileset_TileCount(const Json::Value& tileCountValue, bool expectedTileCountValid);

			bool testValidateTileset_MissingTileWidth();
			bool testValidateTileset_TileWidth(const Json::Value& tileWidthValue, bool expectedTileWidthValid);

			bool testValidateTileset_MissingTileHeight();
			bool testValidateTileset_TileHeight(const Json::Value& tileHeightValue, bool expectedTileHeightValid);

			bool testValidateTileset_MissingTilesetType();
			bool testValidateTileset_EmptyMultiImageTileList();

			bool testValidateTileset_InvalidSingleImage();

			bool testValidateTileset_InvalidMultiImage();

			bool testValidateTileset_InvalidPropertyList();

			bool testConvertToTilesetImageDefn();

			bool testConvertToTilesetTileDefn_EmptyPropertyList();
			bool testConvertToTilesetTileDefn_WithPropertyList();

			bool testConvertToTilesetDefn_SingleImage();
			bool testConvertToTilesetDefn_MultiImage();

		}

	}

}
