
#include <assert.h>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <regex>
#include <r3/colon-case/level-data/r3-colonCase-JsonGameLoader.hpp>

using namespace r3::colonCase;

r3::tiled::CustomPropertyDefn createBoolPropertyDefn(const char* name, bool value) {
	r3::tiled::CustomPropertyDefn result;
	result.name = name;
	result.type = r3::tiled::CustomPropertyType::BOOLEAN;
	result.boolValue = value;
	return result;
}

r3::tiled::MapTilesetDefn createMapTilesetDefn(int firstGid, const std::string& sourcePath) {
	r3::tiled::MapTilesetDefn result;
	result.firstGid = firstGid;
	result.sourcePath = sourcePath;
	return result;
}

r3::tiled::TilesetDefn createImageTilesetDefn() {
	r3::tiled::TilesetDefn result;
	result.version = 1.4;
	result.type = r3::tiled::TilesetType::IMAGE;
	result.columns = 3;
	result.tileCount = 6;
	result.tileWidth = 32;
	result.tileHeight = 16;
	result.margin = 2;
	result.spacing = 1;
	result.imageDefn.imagePath = "../textures/texture-atlas.png";
	result.imageDefn.imageWidth = 102;
	result.imageDefn.imageHeight = 37;
	return result;
}

r3::tiled::TilesetDefn createTileListTilesetDefn() {
	r3::tiled::TilesetTileDefn tile1Defn;
	tile1Defn.id = 0;
	tile1Defn.imageDefn.imagePath = "../textures/floor1.png";
	tile1Defn.imageDefn.imageWidth = 64;
	tile1Defn.imageDefn.imageHeight = 32;

	r3::tiled::TilesetTileDefn tile2Defn;
	tile2Defn.id = 1;
	tile2Defn.imageDefn.imagePath = "../textures/floor2.png";
	tile2Defn.imageDefn.imageWidth = 64;
	tile2Defn.imageDefn.imageHeight = 32;

	r3::tiled::TilesetDefn result;
	result.version = 1.4;
	result.type = r3::tiled::TilesetType::TILE_LIST;
	result.columns = 0;
	result.tileCount = 2;
	result.tileWidth = 64;
	result.tileHeight = 32;
	result.margin = 0;
	result.spacing = 0;
	result.tileDefnList.push_back(tile1Defn);
	result.tileDefnList.push_back(tile2Defn);
	return result;
}

r3::tiled::MapLayerObjectDefn createMapLayerObjectDefn() {
	r3::tiled::MapLayerObjectDefn result;
	result.id = 2;
	result.position.x = 90.0;
	result.position.y = 95.0;
	result.width = 64.0;
	result.height = 32.0;
	result.objectType = r3::tiled::MapLayerObjectType::TILE;
	result.tileGid = 4;
	return result;
}

r3::tiled::MapLayerDefn createCommonMapLayerDefn() {
	r3::tiled::MapLayerDefn result;
	result.id = 3;
	result.width = 3;
	result.height = 3;
	return result;
}

r3::tiled::MapLayerDefn createTileMapLayerDefn() {
	r3::tiled::MapLayerDefn result = createCommonMapLayerDefn();
	result.type = r3::tiled::MapLayerType::TILE;
	result.data = { 0, 0, 0, 0, 1, 0, 0, 0, 0 };
	return result;
}

r3::tiled::MapLayerDefn createObjectMapLayerDefn() {
	r3::tiled::MapLayerObjectDefn objectDefn = createMapLayerObjectDefn();

	r3::tiled::MapLayerDefn result = createCommonMapLayerDefn();
	result.type = r3::tiled::MapLayerType::OBJECT;
	result.objectDefnList.push_back(objectDefn);
	return result;
}

bool testConvertToTileImageDefnList_Image() {
	r3::tiled::MapTilesetDefn mapTilesetDefn = createMapTilesetDefn(1, "imagetileset.json");

	r3::tiled::TilesetDefn tilesetDefn = createImageTilesetDefn();

	std::vector<GameTileImageDefn> tileImageDefnList = JsonGameMapLoader::convertToTileImageDefnList(mapTilesetDefn, tilesetDefn);

	bool allTileImageMatch = true;
	for (const auto& currTileImageDefn : tileImageDefnList) {
		allTileImageMatch = allTileImageMatch &&
			(currTileImageDefn.filename.compare("../textures/texture-atlas.png") == 0) &&
			(currTileImageDefn.imageSize.x == 102) &&
			(currTileImageDefn.imageSize.y == 37) &&
			(currTileImageDefn.textureRect.width == 32) &&
			(currTileImageDefn.textureRect.height == 16);
	}

	bool result =
		(tileImageDefnList.size() == 6) &&
		allTileImageMatch &&
		(tileImageDefnList[0].tileId == 1) &&
		(tileImageDefnList[0].textureRect.left == 2) &&
		(tileImageDefnList[0].textureRect.top == 2) &&
		(tileImageDefnList[5].tileId == 6) &&
		(tileImageDefnList[5].textureRect.left == 68) &&
		(tileImageDefnList[5].textureRect.top == 19);
	return result;
}

bool testConvertToTileImageDefnList_TileList() {
	r3::tiled::MapTilesetDefn mapTilesetDefn = createMapTilesetDefn(7, "tilelist.json");

	r3::tiled::TilesetDefn tilesetDefn = createTileListTilesetDefn();

	std::vector<GameTileImageDefn> tileImageDefnList = JsonGameMapLoader::convertToTileImageDefnList(mapTilesetDefn, tilesetDefn);

	bool allTileImageMatch = true;
	for (const auto& currTileImageDefn : tileImageDefnList) {
		allTileImageMatch = allTileImageMatch &&
			(currTileImageDefn.imageSize.x == 64) &&
			(currTileImageDefn.imageSize.y == 32) &&
			(currTileImageDefn.textureRect.width == 64) &&
			(currTileImageDefn.textureRect.height == 32);
	}

	bool result =
		(tileImageDefnList.size() == 2) &&
		allTileImageMatch &&
		(tileImageDefnList[0].filename.compare("../textures/floor1.png") == 0) &&
		(tileImageDefnList[1].filename.compare("../textures/floor2.png") == 0);
	return result;
}

bool testConvertToSpriteDefn_Success() {
	r3::tiled::MapLayerObjectDefn sourceObjectDefn = createMapLayerObjectDefn();

	GameMapSpriteDefn spriteDefn = JsonGameMapLoader::convertToSpriteDefn(sourceObjectDefn);

	bool result =
		(spriteDefn.tileId == 4) &&
		(lround(spriteDefn.position.x) == 90) &&
		(lround(spriteDefn.position.y) == 95) &&
		(lround(spriteDefn.size.x) == 64) &&
		(lround(spriteDefn.size.y) == 32);
	return result;
}

bool testConvertToSpriteDefn_InvalidType() {
	r3::tiled::MapLayerObjectDefn sourceObjectDefn = createMapLayerObjectDefn();
	sourceObjectDefn.objectType = r3::tiled::MapLayerObjectType::RECTANGLE;

	try {
		JsonGameMapLoader::convertToSpriteDefn(sourceObjectDefn);
		return false;
	}
	catch (std::invalid_argument&) {
		return true;
	}
}

bool testConvertToLayerDefn_Tiles() {
	r3::tiled::MapLayerDefn sourceLayerDefn = createTileMapLayerDefn();

	GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

	bool result =
		(layerDefn.layerType == GameMapLayerType::TILE) &&
		(!layerDefn.renderFlag) &&
		(!layerDefn.collisionFlag) &&
		(layerDefn.tileIdList.size() == 9) &&
		(layerDefn.tileIdList[4] == 1) &&
		(layerDefn.spriteDefnList.empty());
	return result;
}

bool testConvertToLayerDefn_Sprites() {
	r3::tiled::MapLayerDefn sourceLayerDefn = createObjectMapLayerDefn();

	GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

	bool result =
		(layerDefn.layerType == GameMapLayerType::SPRITE) &&
		(!layerDefn.renderFlag) &&
		(!layerDefn.collisionFlag) &&
		(layerDefn.tileIdList.empty()) &&
		(layerDefn.spriteDefnList.size() == 1);
	return result;
}

bool testConvertToLayerDefn_RenderFlag() {
	r3::tiled::MapLayerDefn sourceLayerDefn = createTileMapLayerDefn();
	sourceLayerDefn.propertyDefnList.push_back(createBoolPropertyDefn(LayerPropertyName::RENDER_FLAG, true));

	GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

	bool result =
		(layerDefn.layerType == GameMapLayerType::TILE) &&
		(layerDefn.renderFlag) &&
		(!layerDefn.collisionFlag) &&
		(layerDefn.tileIdList.size() == 9) &&
		(layerDefn.tileIdList[4] == 1) &&
		(layerDefn.spriteDefnList.empty());
	return result;
}

bool testConvertToLayerDefn_CollisionFlag() {
	r3::tiled::MapLayerDefn sourceLayerDefn = createTileMapLayerDefn();
	sourceLayerDefn.propertyDefnList.push_back(createBoolPropertyDefn(LayerPropertyName::COLLISION_FLAG, true));

	GameMapLayerDefn layerDefn = JsonGameMapLoader::convertToLayerDefn(sourceLayerDefn);

	bool result =
		(layerDefn.layerType == GameMapLayerType::TILE) &&
		(!layerDefn.renderFlag) &&
		(layerDefn.collisionFlag) &&
		(layerDefn.tileIdList.size() == 9) &&
		(layerDefn.tileIdList[4] == 1) &&
		(layerDefn.spriteDefnList.empty());
	return result;
}

bool testLoadFromFile_InvalidMapPath() {
	JsonGameMapLoader::LoadGameMapResult gameMapResult = JsonGameMapLoader::loadFromFile("my-campaign", "../missing.json");

	bool result =
		(gameMapResult.errorList.size() == 1) &&
		(gameMapResult.errorList.at(0).find("The path to file") != std::string::npos) &&
		(gameMapResult.errorList.at(0).find("is not valid") != std::string::npos);
	return result;
}

bool testLoadFromFile_MissingMapFile() {
	JsonGameMapLoader::LoadGameMapResult gameMapResult = JsonGameMapLoader::loadFromFile("my-campaign", "missing.json");

	bool result =
		(gameMapResult.errorList.size() == 1) &&
		(gameMapResult.errorList.at(0).find("Syntax error") != std::string::npos);
	return result;
}

bool testLoadFromFile_InvalidTilesetPath() {
	JsonGameMapLoader::LoadGameMapResult gameMapResult = JsonGameMapLoader::loadFromFile("bad-campaign", "levels/bad_tileset_path_map.json");

	bool result =
		(gameMapResult.errorList.size() == 2) &&
		(gameMapResult.errorList.at(0).find("The path to file") != std::string::npos) &&
		(gameMapResult.errorList.at(0).find("is not valid") != std::string::npos) &&
		(gameMapResult.errorList.at(1).find("The path to file") != std::string::npos) &&
		(gameMapResult.errorList.at(1).find("is not valid") != std::string::npos);
	return result;
}

bool testLoadFromFile_MissingTilesetFile() {
	JsonGameMapLoader::LoadGameMapResult gameMapResult = JsonGameMapLoader::loadFromFile("bad-campaign", "levels/missing_tileset_path_map.json");

	bool result =
		(gameMapResult.errorList.size() == 2) &&
		(gameMapResult.errorList.at(0).find("Syntax error") != std::string::npos) &&
		(gameMapResult.errorList.at(1).find("Syntax error") != std::string::npos);
	return result;
}

bool testLoadFromFile_Valid() {
	JsonGameMapLoader::LoadGameMapResult gameMapResult = JsonGameMapLoader::loadFromFile("good-campaign", "levels/valid_map.json");

	bool result =
		(gameMapResult.errorList.empty()) &&
		(gameMapResult.mapDefn.size.x == 10) &&
		(gameMapResult.mapDefn.size.y == 10) &&
		(gameMapResult.mapDefn.tileSize.x == 8) &&
		(gameMapResult.mapDefn.tileSize.y == 8) &&
		(gameMapResult.mapDefn.backgroundColor.toInteger() == 0x804000f0) &&
		(gameMapResult.mapDefn.tileImageDefnMap.size() == 6) &&
		(std::regex_match(gameMapResult.mapDefn.tileImageDefnMap[1].filename, std::regex("textures[\\\\/]grass.png"))) &&
		(std::regex_match(gameMapResult.mapDefn.tileImageDefnMap[2].filename, std::regex("textures[\\\\/]path.png"))) &&
		(gameMapResult.mapDefn.tileImageDefnMap[4].textureRect.left == 11) &&
		(gameMapResult.mapDefn.tileImageDefnMap[4].textureRect.top == 2) &&
		(gameMapResult.mapDefn.layerDefnList.size() == 3) &&
		(!gameMapResult.mapDefn.layerDefnList[0].collisionFlag) &&
		(gameMapResult.mapDefn.layerDefnList[0].tileIdList.size() == 100) &&
		(gameMapResult.mapDefn.layerDefnList[1].collisionFlag) &&
		(gameMapResult.mapDefn.layerDefnList[1].tileIdList.size() == 100) &&
		(gameMapResult.mapDefn.layerDefnList[2].spriteDefnList.size() == 4);
	return result;
}

int main() {
	assert(testConvertToTileImageDefnList_Image());
	assert(testConvertToTileImageDefnList_TileList());

	assert(testConvertToSpriteDefn_Success());
	assert(testConvertToSpriteDefn_InvalidType());

	assert(testConvertToLayerDefn_Tiles());
	assert(testConvertToLayerDefn_Sprites());
	assert(testConvertToLayerDefn_RenderFlag());
	assert(testConvertToLayerDefn_CollisionFlag());

	assert(testLoadFromFile_InvalidMapPath());
	assert(testLoadFromFile_MissingMapFile());
	assert(testLoadFromFile_InvalidTilesetPath());
	assert(testLoadFromFile_MissingTilesetFile());
	assert(testLoadFromFile_Valid());

	std::cout << "All tests passed!\n";
	return 0;
}