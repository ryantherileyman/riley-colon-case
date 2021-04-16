
#include <r3/colon-case/gameplay/r3-colonCase-gameplay.hpp>

namespace r3 {

	namespace colonCase {

		GameMapRenderer::GameMapRenderer(AssetManager& assetManager) {
			this->assetManager = &assetManager;
		}

		void GameMapRenderer::renderMap(sf::RenderTarget& renderTarget, const RenderGameMapInput& renderInput) {
			const GameMap& gameMap = this->assetManager->getMap(renderInput.mapFilename);

			sf::Vector2f viewSize = GameMapRenderUtils::resolveViewSize(renderTarget.getSize(), renderInput.pixelsPerTile);

			this->view = sf::View(renderInput.centerPosition, viewSize);
			this->visibleTileRect = GameMapRenderUtils::resolveVisibleTileRect(this->view, gameMap.getMapSize());

			renderTarget.setView(this->view);
			renderTarget.clear(gameMap.getBackgroundColor());

			for (int layerIndex = 0; layerIndex < gameMap.getLayerCount(); layerIndex++) {
				if (gameMap.getLayerType(layerIndex) == GameMapLayerType::TILE) {
					this->renderTileLayer(renderTarget, gameMap, layerIndex);
				}
				else if (gameMap.getLayerType(layerIndex) == GameMapLayerType::SPRITE) {
					this->renderSpriteLayer(renderTarget, gameMap, layerIndex);
				}
			}
		}

		void GameMapRenderer::renderTileLayer(sf::RenderTarget& renderTarget, const GameMap& gameMap, int layerIndex) {
			int xBoundary = this->visibleTileRect.left + this->visibleTileRect.width;
			int yBoundary = this->visibleTileRect.top + this->visibleTileRect.height;

			for (int y = this->visibleTileRect.top; y < yBoundary; y++) {
				const int* rowTileIdPtr = gameMap.getTileIdPtr(layerIndex, 0, y);
				for (int x = this->visibleTileRect.left; x < xBoundary; x++) {
					int tileId = rowTileIdPtr[x];

					if (tileId > 0) {
						sf::Sprite tileSprite = this->createTileSprite(gameMap, tileId);
						tileSprite.setPosition((float)x, (float)y);
						renderTarget.draw(tileSprite);
					}
				}
			}
		}

		void GameMapRenderer::renderSpriteLayer(sf::RenderTarget& renderTarget, const GameMap& gameMap, int layerIndex) {
			std::vector<GameSpriteRenderDetails> spriteRenderDetailsList = gameMap.getSpriteRenderDetailsList(layerIndex, this->visibleTileRect);

			for (size_t spriteIndex = 0; spriteIndex < spriteRenderDetailsList.size(); spriteIndex++) {
				GameSpriteRenderDetails& currSpriteRenderDetails = spriteRenderDetailsList.at(spriteIndex);

				sf::Sprite gameSprite = this->createGameSprite(gameMap, currSpriteRenderDetails);
				renderTarget.draw(gameSprite);
			}
		}

		sf::Sprite GameMapRenderer::createTileSprite(const GameMap& gameMap, int tileId) {
			sf::Sprite result;
			result.setTexture(this->assetManager->getTexture(gameMap.getTileImageFilename(tileId)));
			result.setTextureRect(gameMap.getTileTextureRect(tileId));
			result.setScale(1.0f / (float)gameMap.getTileSize().x, 1.0f / (float)gameMap.getTileSize().y);
			return result;
		}

		sf::Sprite GameMapRenderer::createGameSprite(const GameMap& gameMap, const GameSpriteRenderDetails& spriteRenderDetails) {
			sf::Texture& spriteTexture = this->assetManager->getTexture(spriteRenderDetails.filename);

			float spriteScaleX = (spriteRenderDetails.size.x / spriteRenderDetails.textureRect.width) * (1.0f / (float)gameMap.getTileSize().x);
			float spriteScaleY = (spriteRenderDetails.size.y / spriteRenderDetails.textureRect.height) * (1.0f / (float)gameMap.getTileSize().y);

			sf::Vector2f spriteTilePos;
			spriteTilePos.x = spriteRenderDetails.position.x / (float)gameMap.getTileSize().x;
			spriteTilePos.y = spriteRenderDetails.position.y / (float)gameMap.getTileSize().y;

			sf::Sprite result;
			result.setTexture(spriteTexture);
			result.setTextureRect(spriteRenderDetails.textureRect);
			result.setOrigin(0.0f, (float)spriteRenderDetails.textureRect.height);
			result.setPosition(spriteTilePos);
			result.setScale(spriteScaleX, spriteScaleY);

			return result;
		}

	}

}
