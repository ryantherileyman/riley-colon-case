
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#pragma once

namespace r3 {

	namespace colonCase {

		typedef enum class ColonCase_GameMapLayerType {
			UNKNOWN,
			TILE,
			SPRITE,
		} GameMapLayerType;

		typedef enum class ColonCase_GameMapObjectType {
			UNKNOWN,
			POPUP_TEXT,
		} GameMapObjectType;

		typedef enum class ColonCase_GameMapObjectShape {
			UNKNOWN,
			RECTANGLE,
			ELLIPSE,
		} GameMapObjectShape;

		typedef struct ColonCase_GameTileImageDefn {
			int tileId = 0;
			std::string filename;
			sf::Vector2i imageSize;
			sf::IntRect textureRect;
		} GameTileImageDefn;

		typedef struct ColonCase_GameMapSpriteDefn {
			int tileId = 0;
			sf::Vector2f position;
			sf::Vector2f size;
		} GameMapSpriteDefn;

		typedef struct ColonCase_GameMapLayerDefn {
			GameMapLayerType layerType = GameMapLayerType::UNKNOWN;
			bool renderFlag = false;
			bool collisionFlag = false;
			bool interactiveFlag = false;
			std::vector<int> tileIdList;
			std::vector<GameMapSpriteDefn> spriteDefnList;
		} GameMapLayerDefn;

		typedef struct ColonCase_GameMapObjectDefn {
			GameMapObjectType objectType = GameMapObjectType::UNKNOWN;
			GameMapObjectShape shape = GameMapObjectShape::UNKNOWN;
			sf::Vector2f position;
			sf::Vector2f size;
			std::string key;
		} GameMapObjectDefn;

		typedef struct ColonCase_GameMapDefn {
			sf::Vector2i size;
			sf::Vector2i tileSize;
			sf::Color backgroundColor;
			std::unordered_map<int, GameTileImageDefn> tileImageDefnMap;
			std::vector<GameMapLayerDefn> layerDefnList;
			std::vector<GameMapObjectDefn> objectDefnList;
		} GameMapDefn;

	}

}
