
#include <assert.h>
#include <stdio.h>
#include "r3-colonCase-GameMapTests.hpp"

using namespace r3::colonCase;

void runGameMapTests() {
	assert(GameMapTests::testGetLayerCount());
	assert(GameMapTests::testGetLayerType());
	assert(GameMapTests::testGetTileIdPtr_InvalidLayerType());
	assert(GameMapTests::testGetTileIdPtr_InvalidPosition());
	assert(GameMapTests::testGetTileIdPtr());
	assert(GameMapTests::testGetSpriteRenderDetailsList_InvalidLayerType());
	assert(GameMapTests::testGetSpriteRenderDetailsList_None());
	assert(GameMapTests::testGetSpriteRenderDetailsList_Partial());
}

int main() {
	runGameMapTests();

	printf("All tests passed!\n");
	return 0;
}
