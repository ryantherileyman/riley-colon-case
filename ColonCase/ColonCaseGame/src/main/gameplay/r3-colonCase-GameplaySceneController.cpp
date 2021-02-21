
#include <math.h>
#include "r3-colonCase-gameplay.hpp"

namespace r3 {

	namespace colonCase {

		const char* MAP_FILENAME = "levels/house-investigator.json";
		const float SECONDS_TO_MOVE = 0.5f;

		GameplaySceneController::GameplaySceneController(sf::RenderWindow& window) {
			this->window = &window;

			if (!this->playerTexture.loadFromFile("resources/textures/investigator-tileset.png")) {
				throw "Could not load player tileset texture";
			}

			this->assetManager.setCampaignFolder("colon-case");

			this->requestedPlayerDirection = CompassDirection::NONE;
			this->playerPosition = sf::Vector2i(0, 0);
			this->playerDirection = CompassDirection::DOWN;
			this->playerMovingFlag = false;
			this->playerAnimationStartSeconds = 0.0f;
		}

		void GameplaySceneController::beginGameplay() {
			this->assetManager.loadMapAsync(MAP_FILENAME);

			this->gameplayClock.restart();

			this->requestedPlayerDirection = CompassDirection::NONE;
			this->playerPosition = sf::Vector2i(9, 5);
			this->playerDirection = CompassDirection::RIGHT;
			this->playerMovingFlag = false;
			this->playerAnimationStartSeconds = 0.0f;
		}

		GameplaySceneClientRequest GameplaySceneController::processEvent(sf::Event& event) {
			GameplaySceneClientRequest result = GameplaySceneClientRequest::NONE;

			if (event.type == sf::Event::Closed) {
				result = GameplaySceneClientRequest::EXIT_GAME;
			}
			else if ( event.type == sf::Event::KeyPressed ) {
				switch (event.key.code) {

				case sf::Keyboard::Key::Escape:
					result = GameplaySceneClientRequest::RETURN_TO_SPLASH;
					break;

				case sf::Keyboard::Key::Up:
					this->requestedPlayerDirection = CompassDirection::UP;
					break;

				case sf::Keyboard::Key::Right:
					this->requestedPlayerDirection = CompassDirection::RIGHT;
					break;

				case sf::Keyboard::Key::Down:
					this->requestedPlayerDirection = CompassDirection::DOWN;
					break;

				case sf::Keyboard::Key::Left:
					this->requestedPlayerDirection = CompassDirection::LEFT;
					break;

				}
			}
			else if (event.type == sf::Event::KeyReleased) {
				switch (event.key.code) {

				case sf::Keyboard::Key::Up:
					if (this->requestedPlayerDirection == CompassDirection::UP) {
						this->requestedPlayerDirection = CompassDirection::NONE;
					}
					break;

				case sf::Keyboard::Key::Right:
					if (this->requestedPlayerDirection == CompassDirection::RIGHT) {
						this->requestedPlayerDirection = CompassDirection::NONE;
					}
					break;

				case sf::Keyboard::Key::Down:
					if (this->requestedPlayerDirection == CompassDirection::DOWN) {
						this->requestedPlayerDirection = CompassDirection::NONE;
					}
					break;

				case sf::Keyboard::Key::Left:
					if (this->requestedPlayerDirection == CompassDirection::LEFT) {
						this->requestedPlayerDirection = CompassDirection::NONE;
					}
					break;

				}
			}

			return result;
		}

		void GameplaySceneController::update() {
			float gameplaySeconds = this->gameplayClock.getElapsedTime().asSeconds();

			bool acceptMovement =
				!playerMovingFlag ||
				(
					playerMovingFlag &&
					((gameplaySeconds - this->playerAnimationStartSeconds) > SECONDS_TO_MOVE)
				);

			if (acceptMovement) {
				if (playerMovingFlag) {
					this->playerPosition += CompassDirectionUtils::convertToVector(this->playerDirection);
				}

				CompassDirection currMovementDirection = this->requestedPlayerDirection;

				AssetLoadingStatus mapLoadingStatus = this->assetManager.getMapStatus(MAP_FILENAME);
				if (mapLoadingStatus.completionStatus == AssetLoadingCompletionStatus::COMPLETE) {
					GameMap& gameMap = this->assetManager.getMap(MAP_FILENAME);

					sf::Vector2i destination = this->playerPosition + CompassDirectionUtils::convertToVector(currMovementDirection);
					if (gameMap.getPositionOccupied(destination.x, destination.y)) {
						currMovementDirection = CompassDirection::NONE;
					}
				}

				if (currMovementDirection == CompassDirection::NONE) {
					this->playerMovingFlag = false;

					if (this->requestedPlayerDirection != CompassDirection::NONE) {
						this->playerDirection = this->requestedPlayerDirection;
					}
				}
				else {
					this->startPlayerMovement(currMovementDirection);
				}
			}
		}

		void GameplaySceneController::render() {
			AssetLoadingStatus mapLoadingStatus = this->assetManager.getMapStatus(MAP_FILENAME);
			if (mapLoadingStatus.completionStatus == AssetLoadingCompletionStatus::COMPLETE) {
				GameMap& gameMap = this->assetManager.getMap(MAP_FILENAME);

				float gameplaySeconds = this->gameplayClock.getElapsedTime().asSeconds();
				sf::Vector2f playerRenderPosition = this->resolvePlayerPosition(gameplaySeconds);

				sf::Vector2u windowSize = this->window->getSize();
				sf::Vector2f viewCenter(sf::Vector2f(playerRenderPosition.x + 0.5f, playerRenderPosition.y + 0.5f));
				sf::Vector2f viewSize(sf::Vector2f((float)windowSize.x / 92.0f, (float)windowSize.y / 92.0f));
				sf::Vector2f viewTopLeft(sf::Vector2f(viewCenter.x - viewSize.x * 0.5f, viewCenter.y - viewSize.y * 0.5f));

				sf::IntRect visibleTileRect(sf::Vector2i((int)floorf(viewTopLeft.x), (int)floorf(viewTopLeft.y)), sf::Vector2i((int)ceilf(viewSize.x) + 1, (int)ceilf(viewSize.y) + 1));

				sf::Vector2i visibleTileTopLeft(std::clamp(visibleTileRect.left, 0, gameMap.getMapSize().x - 1), std::clamp(visibleTileRect.top, 0, gameMap.getMapSize().y - 1));
				sf::Vector2i visibleTileBottomRight(std::clamp(visibleTileRect.left + visibleTileRect.width, 0, gameMap.getMapSize().x - 1), std::clamp(visibleTileRect.top + visibleTileRect.height, 0, gameMap.getMapSize().y - 1));

				this->window->setView(sf::View(viewCenter, viewSize));

				this->window->clear(gameMap.getBackgroundColor());

				for (auto layerIndex = 0; layerIndex < gameMap.getLayerCount(); layerIndex++) {
					if (gameMap.getLayerType(layerIndex) == GameMapLayerType::TILE) {
						for (auto y = visibleTileTopLeft.y; y <= visibleTileBottomRight.y; y++) {
							const int* rowTileIdPtr = gameMap.getTileIdPtr(layerIndex, 0, y);
							for (auto x = visibleTileTopLeft.x; x <= visibleTileBottomRight.x; x++) {
								int tileId = rowTileIdPtr[x];

								if (tileId > 0) {
									sf::Sprite tileSprite;
									tileSprite.setTexture(this->assetManager.getTexture(gameMap.getTileImageFilename(tileId)));
									tileSprite.setTextureRect(gameMap.getTileTextureRect(tileId));
									tileSprite.setPosition((float)x, (float)y);
									tileSprite.setScale(1.0f / (float)gameMap.getTileSize().x, 1.0f / (float)gameMap.getTileSize().y);
									this->window->draw(tileSprite);
								}
							}
						}
					}

					if (gameMap.getLayerType(layerIndex) == GameMapLayerType::SPRITE) {
						std::vector<GameSpriteRenderDetails> spriteRenderDetailsList = gameMap.getSpriteRenderDetailsList(layerIndex, visibleTileRect);
						for (size_t spriteIndex = 0; spriteIndex < spriteRenderDetailsList.size(); spriteIndex++) {
							GameSpriteRenderDetails& currSpriteRenderDetails = spriteRenderDetailsList.at(spriteIndex);

							sf::Texture& spriteTexture = this->assetManager.getTexture(currSpriteRenderDetails.filename);

							float spriteScaleX = (currSpriteRenderDetails.size.x / currSpriteRenderDetails.textureRect.width) * (1.0f / (float)gameMap.getTileSize().x);
							float spriteScaleY = (currSpriteRenderDetails.size.y / currSpriteRenderDetails.textureRect.height) * (1.0f / (float)gameMap.getTileSize().y);

							sf::Vector2f spriteTilePos;
							spriteTilePos.x = currSpriteRenderDetails.position.x / (float)gameMap.getTileSize().x;
							spriteTilePos.y = (currSpriteRenderDetails.position.y / (float)gameMap.getTileSize().y) - (currSpriteRenderDetails.size.y / (float)gameMap.getTileSize().y);

							sf::Sprite currSprite;
							currSprite.setTexture(spriteTexture);
							currSprite.setTextureRect(currSpriteRenderDetails.textureRect);
							currSprite.setPosition(spriteTilePos);
							currSprite.setScale(spriteScaleX, spriteScaleY);
							this->window->draw(currSprite);
						}
					}
				}

				sf::Sprite playerSprite = this->createPlayerSprite(gameplaySeconds);
				playerSprite.setPosition(playerRenderPosition);
				this->window->draw(playerSprite);

				this->window->display();
			}
		}

		void GameplaySceneController::startPlayerMovement(CompassDirection direction) {
			this->playerDirection = direction;
			this->playerMovingFlag = true;
			this->playerAnimationStartSeconds = this->gameplayClock.getElapsedTime().asSeconds();
		}

		sf::Vector2f GameplaySceneController::resolvePlayerPosition(float gameplaySeconds) {
			sf::Vector2f result((float)this->playerPosition.x, (float)this->playerPosition.y);

			if (this->playerMovingFlag) {
				float secondsSinceAnimationStart = gameplaySeconds - this->playerAnimationStartSeconds;
				float positionDiff = truncf(secondsSinceAnimationStart * 8.0f / SECONDS_TO_MOVE) / 8.0f;
				sf::Vector2i compassChange = CompassDirectionUtils::convertToVector(this->playerDirection);

				result.x += (float)compassChange.x * positionDiff;
				result.y += (float)compassChange.y * positionDiff;
			}

			return result;
		}

		sf::Sprite GameplaySceneController::createPlayerSprite(float gameplaySeconds) {
			sf::Sprite result(this->playerTexture);

			int textureRectTop = 0;
			int textureRectLeft = 0;

			switch (this->playerDirection) {

			case CompassDirection::DOWN:
				textureRectTop = 0;
				break;

			case CompassDirection::UP:
				textureRectTop = 256;
				break;

			case CompassDirection::LEFT:
				textureRectTop = 512;
				break;

			case CompassDirection::RIGHT:
				textureRectTop = 768;
				break;
			}

			float secondsSinceAnimationStart = gameplaySeconds - this->playerAnimationStartSeconds;
			if (!this->playerMovingFlag) {
				float secondsIntoAnimation = secondsSinceAnimationStart - truncf(secondsSinceAnimationStart / 1.0f);

				if (secondsIntoAnimation >= 0.5f) {
					textureRectLeft = 256;
				}
			}
			else {
				textureRectLeft = 512 + (256 * (int)truncf((secondsSinceAnimationStart / SECONDS_TO_MOVE) * 4));
			}

			result.setScale(1.0f / 256.0f, 1.0f / 256.0f);
			result.setTextureRect(sf::IntRect(textureRectLeft, textureRectTop, 256, 256));

			return result;
		}

	}

}
