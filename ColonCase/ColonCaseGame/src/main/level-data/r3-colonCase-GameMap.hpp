
#include <string>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "r3-colonCase-levelDefn.hpp"
#pragma once

namespace r3 {

	namespace colonCase {

		typedef struct ColonCase_GameSpriteRenderDetails {
			std::string filename;
			sf::Vector2i imageSize;
			sf::IntRect textureRect;
			sf::Vector2f position;
			sf::Vector2f size;
		} GameSpriteRenderDetails;

		class GameSpriteImage;
		class GameSpriteTile;
		class GameMapSprite;
		class GameMapLayer;
		class GameMap;

		class GameSpriteImage {

		private:
			int imageId;
			std::string filename;
			sf::Vector2i imageSize;

		public:
			GameSpriteImage();
			GameSpriteImage(int imageId, const GameTileImageDefn& imageDefn);

		public:
			int getImageId() const;
			const std::string& getFilename() const;
			const sf::Vector2i& getImageSize() const;

		};

		class GameSpriteTile {

		private:
			int tileId;
			int imageId;
			sf::IntRect textureRect;

		public:
			GameSpriteTile();
			GameSpriteTile(int imageId, const GameTileImageDefn& imageDefn);

		public:
			int getTileId() const;
			int getImageId() const;
			const sf::IntRect& getTextureRect() const;

		};

		class GameMapSprite {

		private:
			int tileId;
			sf::Vector2f position;
			sf::Vector2f size;

		public:
			GameMapSprite(const GameMapSpriteDefn& spriteDefn);

		public:
			int getTileId() const;
			const sf::Vector2f& getPosition() const;
			const sf::Vector2f& getSize() const;

		};

		class GameMapLayer {

		private:
			GameMapLayerType layerType;
			std::vector<int> tileIdList;
			std::vector<GameMapSprite> spriteList;

		protected:
			GameMapLayer();

		public:
			static GameMapLayer createTileLayer(const GameMapLayerDefn& layerDefn);
			static GameMapLayer createSpriteLayer(const GameMapLayerDefn& layerDefn);

		public:
			const GameMapLayerType getLayerType() const;
			const int* getTileIdPtr() const;
			const std::vector<GameMapSprite>& getSpriteList() const;

		};

		class GameMap {

		private:
			sf::Color backgroundColor;
			sf::Vector2i mapSize;
			sf::Vector2i tileSize;
			std::unordered_map<int, GameSpriteImage> imageMap;
			std::unordered_map<int, GameSpriteTile> tileMap;
			std::vector<GameMapLayer> layerList;
			std::vector<bool> collisionFlagList;

		public:
			GameMap(const GameMapDefn& mapDefn);

		private:
			void initializeImageAndTileMap(const GameMapDefn& mapDefn);
			void initializeLayerList(const GameMapDefn& mapDefn);
			void initializeCollectionFlagList(const GameMapDefn& mapDefn);

		public:
			const sf::Color& getBackgroundColor() const;
			const sf::Vector2i& getMapSize() const;
			const sf::Vector2i& getTileSize() const;
			int getLayerCount() const;
			const GameMapLayerType getLayerType(int layerIndex) const;
			const int* getTileIdPtr(int layerIndex, int x, int y) const;
			const std::string& getTileImageFilename(int tileId) const;
			const sf::IntRect& getTileTextureRect(int tileId) const;
			const std::vector<GameSpriteRenderDetails> getSpriteRenderDetailsList(int layerIndex, const sf::IntRect& visibleTileRect) const;

		public:
			bool getPositionOccupied(int x, int y) const;

		private:
			GameSpriteRenderDetails buildSpriteRenderDetails(const GameMapSprite& sprite) const;

		};

	}

}
