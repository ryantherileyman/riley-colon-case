
#include <assert.h>
#include <iostream>
#include <r3/colon-case/level-data/r3-colonCase-levelDefn.hpp>
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>

using namespace r3::colonCase;

GameTileImageDefn createAtlasTileImageDefn(int x, int y) {
	GameTileImageDefn result;
	result.tileId = y * 4 + x;
	result.filename = "texture-atlas.png";
	result.imageSize = sf::Vector2i(128, 96);
	result.textureRect = sf::IntRect(x * 32, y * 32, 32, 32);
	return result;
}

GameTileImageDefn createSprite1ImageDefn() {
	GameTileImageDefn result;
	result.tileId = 12;
	result.filename = "sprite1.png";
	result.imageSize = sf::Vector2i(64, 64);
	result.textureRect = sf::IntRect(0, 0, 64, 64);
	return result;
}

GameTileImageDefn createSprite2ImageDefn() {
	GameTileImageDefn result;
	result.tileId = 13;
	result.filename = "sprite2.png";
	result.imageSize = sf::Vector2i(48, 48);
	result.textureRect = sf::IntRect(0, 0, 48, 48);
	return result;
}

GameMapLayerDefn createFloorLayerDefn() {
	int tileIdArray[70] = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 2, 3, 4, 0, 2, 4, 0, 1,
		1, 0, 5, 6, 0, 0, 5, 6, 0, 1,
		1, 0, 7, 9, 0, 7, 8, 9, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

	GameMapLayerDefn result;
	result.layerType = GameMapLayerType::TILE;
	result.renderFlag = true;
	result.collisionFlag = true;
	result.tileIdList.insert(std::begin(result.tileIdList), std::begin(tileIdArray), std::end(tileIdArray));

	return result;
}

GameMapLayerDefn createSpriteLayerDefn() {
	GameMapSpriteDefn sprite1Defn;
	sprite1Defn.tileId = 12;
	sprite1Defn.position = sf::Vector2f(64.0f, 128.0f);
	sprite1Defn.size = sf::Vector2f(64.0f, 64.0f);

	GameMapSpriteDefn sprite2Defn;
	sprite2Defn.tileId = 13;
	sprite2Defn.position = sf::Vector2f(208.0f, 112.0f);
	sprite2Defn.size = sf::Vector2f(48.0f, 48.0f);

	GameMapLayerDefn result;
	result.layerType = GameMapLayerType::SPRITE;
	result.renderFlag = true;
	result.spriteDefnList.push_back(sprite1Defn);
	result.spriteDefnList.push_back(sprite2Defn);

	return result;
}

GameMapLayerDefn createCollisionTileLayerDefn() {
	int tileIdArray[70] = {
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	};

	GameMapLayerDefn result;
	result.layerType = GameMapLayerType::TILE;
	result.collisionFlag = true;
	result.tileIdList.insert(std::begin(result.tileIdList), std::begin(tileIdArray), std::end(tileIdArray));

	return result;
}

GameMapDefn createGameMapDefn() {
	GameMapDefn result;

	result.size = sf::Vector2i(10, 7);
	result.tileSize = sf::Vector2i(32, 32);

	result.tileImageDefnMap[0] = createAtlasTileImageDefn(0, 0);
	result.tileImageDefnMap[1] = createAtlasTileImageDefn(1, 0);
	result.tileImageDefnMap[2] = createAtlasTileImageDefn(2, 0);
	result.tileImageDefnMap[3] = createAtlasTileImageDefn(3, 0);
	result.tileImageDefnMap[4] = createAtlasTileImageDefn(0, 1);
	result.tileImageDefnMap[5] = createAtlasTileImageDefn(1, 1);
	result.tileImageDefnMap[6] = createAtlasTileImageDefn(2, 1);
	result.tileImageDefnMap[7] = createAtlasTileImageDefn(3, 1);
	result.tileImageDefnMap[8] = createAtlasTileImageDefn(0, 2);
	result.tileImageDefnMap[9] = createAtlasTileImageDefn(1, 2);
	result.tileImageDefnMap[10] = createAtlasTileImageDefn(2, 2);
	result.tileImageDefnMap[11] = createAtlasTileImageDefn(3, 2);
	result.tileImageDefnMap[12] = createSprite1ImageDefn();
	result.tileImageDefnMap[13] = createSprite2ImageDefn();

	result.layerDefnList.push_back(createFloorLayerDefn());
	result.layerDefnList.push_back(createSpriteLayerDefn());
	result.layerDefnList.push_back(createCollisionTileLayerDefn());

	return result;
}

bool testGetLayerCount() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	bool result = (map.getLayerCount() == 2);
	return result;
}

bool testGetLayerType() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	bool result =
		(map.getLayerType(0) == GameMapLayerType::TILE) &&
		(map.getLayerType(1) == GameMapLayerType::SPRITE);
	return result;
}

bool testGetTileIdPtr_InvalidLayerType() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	try {
		map.getTileIdPtr(1, 0, 0);
		return false;
	}
	catch (std::invalid_argument) {
		return true;
	}
}

bool testGetTileIdPtr_InvalidPosition() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	bool result = true;

	try {
		map.getTileIdPtr(0, -1, 0);
		result = false;
	}
	catch (std::out_of_range) {
	}

	try {
		map.getTileIdPtr(0, 0, -1);
		result = false;
	}
	catch (std::out_of_range) {
	}

	try {
		map.getTileIdPtr(0, 10, 0);
		result = false;
	}
	catch (std::out_of_range) {
	}

	try {
		map.getTileIdPtr(0, 0, 7);
		result = false;
	}
	catch (std::out_of_range) {
	}

	return result;
}

bool testGetTileIdPtr() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	const int* tileIdPtr = map.getTileIdPtr(0, 4, 2);

	bool result =
		(tileIdPtr[0] == 4) &&
		(tileIdPtr[1] == 0) &&
		(tileIdPtr[2] == 2) &&
		(tileIdPtr[3] == 4) &&
		(tileIdPtr[4] == 0) &&
		(tileIdPtr[5] == 1);
	return result;
}

bool testGetTileImageFilename() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	std::string filename = map.getTileImageFilename(4);

	bool result = (filename.compare("texture-atlas.png") == 0);
	return result;
}

bool testGetTileTextureRect() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	sf::IntRect textureRect = map.getTileTextureRect(7);

	bool result =
		(textureRect.left == 96) &&
		(textureRect.top == 32) &&
		(textureRect.width == 32) &&
		(textureRect.height == 32);
	return result;
}

bool testGetSpriteRenderDetailsList_InvalidLayerType() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	try {
		map.getSpriteRenderDetailsList(0, sf::IntRect(0, 0, 10, 7));
		return false;
	}
	catch (std::invalid_argument) {
		return true;
	}
}

bool testGetSpriteRenderDetailsList_None() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	const std::vector<GameSpriteRenderDetails> spriteRenderDetailsList = map.getSpriteRenderDetailsList(1, sf::IntRect(4, 4, 4, 2));

	bool result = spriteRenderDetailsList.empty();
	return result;
}

bool testGetSpriteRenderDetailsList_Partial() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	const std::vector<GameSpriteRenderDetails> spriteRenderDetailsList = map.getSpriteRenderDetailsList(1, sf::IntRect(0, 3, 4, 2));

	bool result =
		(spriteRenderDetailsList.size() == 1) &&
		(spriteRenderDetailsList[0].filename.compare("sprite1.png") == 0) &&
		(spriteRenderDetailsList[0].imageSize.x == 64) &&
		(spriteRenderDetailsList[0].imageSize.y == 64) &&
		(spriteRenderDetailsList[0].textureRect.left == 0) &&
		(spriteRenderDetailsList[0].textureRect.top == 0) &&
		(spriteRenderDetailsList[0].textureRect.width == 64) &&
		(spriteRenderDetailsList[0].textureRect.height == 64) &&
		(lround(spriteRenderDetailsList[0].position.x) == 64) &&
		(lround(spriteRenderDetailsList[0].position.y) == 128) &&
		(lround(spriteRenderDetailsList[0].size.x) == 64) &&
		(lround(spriteRenderDetailsList[0].size.y) == 64);
	return result;
}

bool testGetPositionOccupied_InvalidPosition() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	bool result = true;

	try {
		map.getPositionOccupied(-1, 0);
		result = false;
	}
	catch (std::out_of_range) {
	}

	try {
		map.getPositionOccupied(10, 0);
		result = false;
	}
	catch (std::out_of_range) {
	}

	try {
		map.getPositionOccupied(0, -1);
		result = false;
	}
	catch (std::out_of_range) {
	}

	try {
		map.getPositionOccupied(0, 10);
		result = false;
	}
	catch (std::out_of_range) {
	}

	return result;
}

bool testGetPositionOccupied_NotOccupied() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	bool result = !map.getPositionOccupied(2, 1);
	return result;
}

bool testGetPositionOccupied_Occupied() {
	GameMapDefn mapDefn = createGameMapDefn();

	GameMap map(mapDefn);

	bool result = map.getPositionOccupied(2, 2);
	return result;
}

int main() {
	assert(testGetLayerCount());

	assert(testGetLayerType());

	assert(testGetTileIdPtr_InvalidLayerType());
	assert(testGetTileIdPtr_InvalidPosition());
	assert(testGetTileIdPtr());

	assert(testGetTileImageFilename());

	assert(testGetTileTextureRect());

	assert(testGetSpriteRenderDetailsList_InvalidLayerType());
	assert(testGetSpriteRenderDetailsList_None());
	assert(testGetSpriteRenderDetailsList_Partial());

	assert(testGetPositionOccupied_InvalidPosition());
	assert(testGetPositionOccupied_NotOccupied());
	assert(testGetPositionOccupied_Occupied());

	std::cout << "All tests passed!\n";
	return 0;
}
