
#include <assert.h>
#include <string>
#include <unordered_map>
#include <math.h>
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include "r3-colonCase-GameMap.hpp"

namespace r3 {

	namespace colonCase {

		GameMap::GameMap(const GameMapDefn& mapDefn) {
			this->mapSize = mapDefn.size;
			this->tileSize = mapDefn.tileSize;
			this->initializeImageAndTileMap(mapDefn);
			this->initializeLayerList(mapDefn);
			this->initializeCollectionFlagList(mapDefn);
		}

		void GameMap::initializeImageAndTileMap(const GameMapDefn& mapDefn) {
			std::unordered_map<std::string, int> imageIdMap;

			int nextImageId = 0;
			for (const auto& currTileImageDefnPair : mapDefn.tileImageDefnMap) {
				if (imageIdMap.count(currTileImageDefnPair.second.filename) == 0) {
					imageIdMap[currTileImageDefnPair.second.filename] = nextImageId;
					nextImageId++;
				}
			}

			for (const auto& currTileImageDefnPair : mapDefn.tileImageDefnMap) {
				int matchingImageId = imageIdMap[currTileImageDefnPair.second.filename];
				this->imageMap[matchingImageId] = GameSpriteImage(matchingImageId, currTileImageDefnPair.second);
				this->tileMap[currTileImageDefnPair.first] = GameSpriteTile(matchingImageId, currTileImageDefnPair.second);
			}
		}

		void GameMap::initializeLayerList(const GameMapDefn& mapDefn) {
			for (const auto& currLayerDefn : mapDefn.layerDefnList) {
				if (currLayerDefn.renderFlag) {
					if (currLayerDefn.layerType == GameMapLayerType::TILE) {
						this->layerList.push_back(GameMapLayer::createTileLayer(currLayerDefn));
					}
					else if (currLayerDefn.layerType == GameMapLayerType::SPRITE) {
						this->layerList.push_back(GameMapLayer::createSpriteLayer(currLayerDefn));
					}
				}
			}
		}

		void GameMap::initializeCollectionFlagList(const GameMapDefn& mapDefn) {
			this->collisionFlagList = std::vector<bool>(mapDefn.size.x * mapDefn.size.y, false);

			for (const auto& currLayerDefn : mapDefn.layerDefnList) {
				if (
					currLayerDefn.collisionFlag &&
					(currLayerDefn.layerType == GameMapLayerType::TILE)
				) {
					int index = 0;
					for (auto currTileId : currLayerDefn.tileIdList) {
						if (currTileId > 0) {
							this->collisionFlagList[index] = true;
						}
						index++;
					}
				}
			}
		}

		const sf::Vector2i& GameMap::getMapSize() const {
			return this->mapSize;
		}

		const sf::Vector2i& GameMap::getTileSize() const {
			return this->tileSize;
		}

		int GameMap::getLayerCount() const {
			int result = this->layerList.size();
			return result;
		}

		const GameMapLayerType GameMap::getLayerType(int layerIndex) {
			GameMapLayerType result = this->layerList[layerIndex].getLayerType();
			return result;
		}

		const int* GameMap::getTileIdPtr(int layerIndex, int x, int y) const {
			if (this->layerList[layerIndex].getLayerType() != GameMapLayerType::TILE) {
				throw std::invalid_argument("Layer must be of type TILE");
			}

			if (
				(x < 0) ||
				(x >= this->mapSize.x) ||
				(y < 0) ||
				(y >= this->mapSize.y)
			) {
				throw std::out_of_range("x, y position is outside of the map size");
			}

			const int* result = this->layerList[layerIndex].getTileIdPtr();
			result += (this->mapSize.x * y) + x;
			return result;
		}

		const std::string& GameMap::getTileImageFilename(int tileId) const {
			const GameSpriteTile& tile = this->tileMap.at(tileId);
			const GameSpriteImage& image = this->imageMap.at(tile.getImageId());
			const std::string& result = image.getFilename();
			return result;
		}

		const sf::IntRect& GameMap::getTileTextureRect(int tileId) const {
			const GameSpriteTile& tile = this->tileMap.at(tileId);
			const sf::IntRect& result = tile.getTextureRect();
			return result;
		}

		const std::vector<GameSpriteRenderDetails> GameMap::getSpriteRenderDetailsList(int layerIndex, const sf::IntRect& visibleTileRect) const {
			if (this->layerList[layerIndex].getLayerType() != GameMapLayerType::SPRITE) {
				throw std::invalid_argument("Layer must be of type SPRITE");
			}

			sf::IntRect visiblePixelRect;
			visiblePixelRect.left = visibleTileRect.left * this->tileSize.x;
			visiblePixelRect.top = visibleTileRect.top * this->tileSize.y;
			visiblePixelRect.width = visibleTileRect.width * this->tileSize.x;
			visiblePixelRect.height = visibleTileRect.height * this->tileSize.y;

			std::vector<GameSpriteRenderDetails> result;

			for (const auto& currSprite : this->layerList[layerIndex].getSpriteList()) {
				sf::IntRect spritePixelRect;
				spritePixelRect.left = lround(currSprite.getPosition().x);
				spritePixelRect.top = lround(currSprite.getPosition().y - currSprite.getSize().y);
				spritePixelRect.width = lround(currSprite.getSize().x);
				spritePixelRect.height = lround(currSprite.getSize().y);

				if (spritePixelRect.intersects(visiblePixelRect)) {
					result.push_back(this->buildSpriteRenderDetails(currSprite));
				}
			}

			return result;
		}

		GameSpriteRenderDetails GameMap::buildSpriteRenderDetails(const GameMapSprite& sprite) const {
			const GameSpriteTile& tile = this->tileMap.at(sprite.getTileId());
			const GameSpriteImage& image = this->imageMap.at(tile.getImageId());

			GameSpriteRenderDetails result;
			result.filename = image.getFilename();
			result.imageSize = image.getImageSize();
			result.textureRect = tile.getTextureRect();
			result.position = sprite.getPosition();
			result.size = sprite.getSize();

			return result;
		}

		bool GameMap::getPositionOccupied(int x, int y) const {
			if (
				(x < 0) ||
				(x >= this->mapSize.x) ||
				(y < 0) ||
				(y >= this->mapSize.y)
			) {
				throw std::out_of_range("x, y position is outside of the map size");
			}

			bool result = this->collisionFlagList.at(y * this->mapSize.x + x);
			return result;
		}

	}

}
