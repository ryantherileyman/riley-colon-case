
#include <assert.h>
#include <stdio.h>
#include "r3-colonCase-GameLoaderUtilsTest.hpp"
#include "r3-colonCase-JsonGameMapLoaderTests.hpp"

using namespace r3::colonCase;

void runGameLoaderUtilsTests() {
	assert(GameLoaderUtilsTests::testIsValidPath("test-campaign", "some-file.json", true));
	assert(GameLoaderUtilsTests::testIsValidPath("Test-Campaign_0", "some-file.json", true));
	assert(GameLoaderUtilsTests::testIsValidPath("../test-campaign", "some-file.json", false));
	assert(GameLoaderUtilsTests::testIsValidPath("test-campaign", "../some-file.json", false));

	assert(GameLoaderUtilsTests::testBuildFullPath("test-campaign", "some-file.json", "resources/campaigns/test-campaign/some-file.json"));
	assert(GameLoaderUtilsTests::testBuildFullPath("test-campaign", "../some-file.json", "resources/campaigns/some-file.json"));
	assert(GameLoaderUtilsTests::testBuildFullPath("test-campaign", "../../../../some-file.json", "../some-file.json"));

	assert(GameLoaderUtilsTests::testResolveRelativeFilePath("maps/mymap.json", "mytileset.json", "maps/mytileset.json"));
	assert(GameLoaderUtilsTests::testResolveRelativeFilePath("maps/mymap.json", "../tilesets/mytileset.json", "tilesets/mytileset.json"));

	assert(GameLoaderUtilsTests::testLocalizeInvalidPathError("test-campaign", "../some-file.json"));
}

void runJsonGameMapLoaderTests() {
	assert(JsonGameMapLoaderTests::testConvertToTileImageDefnList_Image());
	assert(JsonGameMapLoaderTests::testConvertToTileImageDefnList_TileList());

	assert(JsonGameMapLoaderTests::testConvertToSpriteDefn_Success());
	assert(JsonGameMapLoaderTests::testConvertToSpriteDefn_InvalidType());

	assert(JsonGameMapLoaderTests::testConvertToLayerDefn_Tiles());
	assert(JsonGameMapLoaderTests::testConvertToLayerDefn_Sprites());
	assert(JsonGameMapLoaderTests::testConvertToLayerDefn_RenderFlag());
	assert(JsonGameMapLoaderTests::testConvertToLayerDefn_CollisionFlag());
}

int main() {
	runGameLoaderUtilsTests();

	runJsonGameMapLoaderTests();

	printf("All tests passed!\n");
	return 0;
}
