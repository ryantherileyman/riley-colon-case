
#include <algorithm>
#include <math.h>
#include <r3/colon-case/gameplay/r3-colonCase-gameplay.hpp>
#include <r3/sfml/geometry/r3-sfml-Ellipse.hpp>

namespace r3 {

	namespace colonCase {

		const char* MAP_FILENAME = "levels/house-investigator.json";
		const float SECONDS_TO_MOVE = 0.5f;

		GameplaySceneController::GameplaySceneController(sf::RenderWindow& window) {
			this->window = &window;

			this->offscreenMapTexture.create(1920, 1080);

			this->defaultCursor.loadFromSystem(sf::Cursor::Arrow);
			this->investigateCursor.loadFromSystem(sf::Cursor::Hand);

			if (!this->playerTexture.loadFromFile("resources/textures/investigator-tileset.png")) {
				throw "Could not load player tileset texture";
			}

			this->assetManager.setCampaignFolder("colon-case");
			this->mapRendererPtr.reset(new GameMapRenderer(this->assetManager));

			this->pixelsPerTile = 96;
			this->requestedPlayerDirection = CompassDirection::NONE;
			this->playerPosition = sf::Vector2i(0, 0);
			this->playerDirection = CompassDirection::DOWN;
			this->playerMovingFlag = false;
			this->playerAnimationStartSeconds = 0.0f;

			this->currMouseCursorType = GameplayMouseCursorType::STANDARD;
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
				result = this->processKeyPressedEvent(event.key.code);
			}
			else if (event.type == sf::Event::KeyReleased) {
				this->processKeyReleasedEvent(event.key.code);
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
				GameplayMouseCursorType updatedMouseCursorType = this->resolveMouseCursorType();
				if (updatedMouseCursorType != this->currMouseCursorType) {
					this->changeMouseCursor(updatedMouseCursorType);
				}

				float gameplaySeconds = this->gameplayClock.getElapsedTime().asSeconds();
				sf::Vector2f playerRenderPosition = this->resolvePlayerPosition(gameplaySeconds);

				RenderGameMapInput renderGameMapInput;
				renderGameMapInput.mapFilename = MAP_FILENAME;
				renderGameMapInput.pixelsPerTile = this->pixelsPerTile;
				renderGameMapInput.centerPosition = sf::Vector2f(playerRenderPosition.x + 0.5f, playerRenderPosition.y + 0.5f);

				this->mapRendererPtr.get()->renderMap(this->offscreenMapTexture, renderGameMapInput);

				sf::Sprite playerSprite = this->createPlayerSprite(gameplaySeconds);
				playerSprite.setPosition(playerRenderPosition.x, playerRenderPosition.y);
				playerSprite.setScale(1.0f / 256.0f, 1.0f / 256.0f);
				this->offscreenMapTexture.draw(playerSprite);

				sf::View view;
				view.setCenter(0.0f, 0.0f);
				view.setSize((float)this->window->getSize().x, 0.0f - (float)this->window->getSize().y);

				this->window->setView(view);

				sf::Sprite mapSprite;
				mapSprite.setTexture(this->offscreenMapTexture.getTexture());
				mapSprite.setPosition(0.0f - ((float)this->offscreenMapTexture.getSize().x * 0.5f), 0.0f - ((float)this->offscreenMapTexture.getSize().y * 0.5f));
				this->window->draw(mapSprite);
				
				this->window->display();
			}
		}

		GameplaySceneClientRequest GameplaySceneController::processKeyPressedEvent(sf::Keyboard::Key keyCode) {
			GameplaySceneClientRequest result = GameplaySceneClientRequest::NONE;

			GameplayKeyPressedClientInput keyPressedClientInput;
			keyPressedClientInput.keyCode = keyCode;

			GameplayKeyPressedResult keyPressedResult = GameplayKeyboardEventUtils::processKeyPressed(keyPressedClientInput);

			if (keyPressedResult.keyPressedClientRequest == GameplayKeyPressedClientRequest::SCENE_REQUEST) {
				result = keyPressedResult.sceneClientRequest;
			}
			else if (keyPressedResult.keyPressedClientRequest == GameplayKeyPressedClientRequest::ZOOM_VIEW_IN_REQUEST) {
				this->pixelsPerTile = std::clamp(this->pixelsPerTile + 16, 64, 128);
			}
			else if (keyPressedResult.keyPressedClientRequest == GameplayKeyPressedClientRequest::ZOOM_VIEW_OUT_REQUEST) {
				this->pixelsPerTile = std::clamp(this->pixelsPerTile - 16, 64, 128);
			}
			else if (keyPressedResult.keyPressedClientRequest == GameplayKeyPressedClientRequest::MOVE_PLAYER) {
				this->requestedPlayerDirection = keyPressedResult.requestedPlayerDirection;
			}

			return result;
		}

		void GameplaySceneController::processKeyReleasedEvent(sf::Keyboard::Key keyCode) {
			GameplayKeyReleasedClientInput keyReleasedClientInput;
			keyReleasedClientInput.keyCode = keyCode;
			keyReleasedClientInput.requestedPlayerDirection = this->requestedPlayerDirection;

			GameplayKeyReleasedResult keyReleasedResult = GameplayKeyboardEventUtils::processKeyReleased(keyReleasedClientInput);

			if (keyReleasedResult.keyReleasedClientRequest == GameplayKeyReleasedClientRequest::STOP_PLAYER) {
				this->requestedPlayerDirection = CompassDirection::NONE;
			}
		}

		GameplayMouseCursorType GameplaySceneController::resolveMouseCursorType() {
			float gameplaySeconds = this->gameplayClock.getElapsedTime().asSeconds();
			sf::Vector2f playerRenderPosition = this->resolvePlayerPosition(gameplaySeconds);

			sf::Vector2f playerPosition = playerRenderPosition + sf::Vector2f(0.5f, 0.5f);
			sf::Vector2f viewSize = GameMapRenderUtils::resolveViewSize(this->window->getSize(), this->pixelsPerTile);
			sf::View view(playerPosition, viewSize);

			sf::Vector2i mousePosition = sf::Mouse::getPosition(*this->window);

			sf::Vector2f mapPosition = this->window->mapPixelToCoords(mousePosition, view);

			r3::sfml::FloatEllipse mugRegion(8.43f, 2.79f, 0.07f, 0.07f);
			sf::FloatRect bookRegion(14.68f, 5.21f, 0.34f, 0.28f);

			bool mouseInInvestigateRegion =
				mugRegion.contains(mapPosition) ||
				bookRegion.contains(mapPosition);

			GameplayMouseCursorType result = GameplayMouseCursorType::STANDARD;
			if (mouseInInvestigateRegion) {
				result = GameplayMouseCursorType::INVESTIGATE_ITEM;
			}
			return result;
		}

		void GameplaySceneController::changeMouseCursor(GameplayMouseCursorType mouseCursorType) {
			this->currMouseCursorType = mouseCursorType;

			if (mouseCursorType == GameplayMouseCursorType::STANDARD) {
				this->window->setMouseCursor(this->defaultCursor);
			}
			else if (mouseCursorType == GameplayMouseCursorType::INVESTIGATE_ITEM) {
				this->window->setMouseCursor(this->investigateCursor);
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

			result.setTextureRect(sf::IntRect(textureRectLeft, textureRectTop, 256, 256));

			return result;
		}

	}

}
