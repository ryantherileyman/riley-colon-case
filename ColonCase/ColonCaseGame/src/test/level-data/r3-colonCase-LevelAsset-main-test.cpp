
#include <assert.h>
#include <stdio.h>
#include "r3-colonCase-GameMapTests.hpp"
#include "r3-colonCase-AssetManagerTests.hpp"

using namespace r3::colonCase;

void runGameMapTests() {
	assert(GameMapTests::testGetLayerCount());

	assert(GameMapTests::testGetLayerType());

	assert(GameMapTests::testGetTileIdPtr_InvalidLayerType());
	assert(GameMapTests::testGetTileIdPtr_InvalidPosition());
	assert(GameMapTests::testGetTileIdPtr());

	assert(GameMapTests::testGetTileImageFilename());

	assert(GameMapTests::testGetTileTextureRect());

	assert(GameMapTests::testGetSpriteRenderDetailsList_InvalidLayerType());
	assert(GameMapTests::testGetSpriteRenderDetailsList_None());
	assert(GameMapTests::testGetSpriteRenderDetailsList_Partial());
}

void runAssetLoadingStatusTests() {
	assert(AssetLoadingStatusTests::testGetLoadedPct(0, 0, 0.00f));
	assert(AssetLoadingStatusTests::testGetLoadedPct(0, 1, 0.00f));
	assert(AssetLoadingStatusTests::testGetLoadedPct(1, 1, 100.00f));
	assert(AssetLoadingStatusTests::testGetLoadedPct(2, 9, 22.22f));
}

void runAssetLoadingTrackerTests() {
	assert(AssetLoadingTrackerTests::testConstructor());

	assert(AssetLoadingTrackerTests::testMarkAsComplete());
	assert(AssetLoadingTrackerTests::testMarkAsFailed());

	assert(AssetLoadingTrackerTests::testAddResourceIdToLoad_NewResourceId());
	assert(AssetLoadingTrackerTests::testAddResourceIdToLoad_ExistingResourceId());

	assert(AssetLoadingTrackerTests::testMarkResourceIdLoaded_NotTracked());
	assert(AssetLoadingTrackerTests::testMarkResourceIdLoaded_Tracked());

	assert(AssetLoadingTrackerTests::testSetCurrentResourceId_NotTracked());
	assert(AssetLoadingTrackerTests::testSetCurrentResourceId_Tracked());
}

void runAssetManagerTests() {
	assert(AssetManagerTests::testGetMapStatus_LoadingNotInitiated());
	assert(AssetManagerTests::testGetMapStatus_LoadingInitiated());
	assert(AssetManagerTests::testGetMapStatus_ErrorLoadingMap());
	assert(AssetManagerTests::testGetMapStatus_ErrorLoadingTexture());

	assert(AssetManagerTests::testDestructor_WaitsIfLoadingIncomplete());
}

int main() {
	runGameMapTests();

	runAssetLoadingStatusTests();
	runAssetLoadingTrackerTests();
	runAssetManagerTests();

	printf("All tests passed!\n");
	return 0;
}
