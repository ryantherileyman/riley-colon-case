
#include <math.h>
#include "r3-colonCase-gameplay.hpp"

namespace r3 {

	namespace colonCase {

		const float SECONDS_TO_MOVE = 0.5f;

		GameplaySceneController::GameplaySceneController(sf::RenderWindow& window) {
			this->window = &window;

			this->floorTexture = new sf::Texture();
			if (!this->floorTexture->loadFromFile("resources/textures/grass.png")) {
				throw "Could not load floor texture";
			}
			this->floorTexture->setRepeated(true);
			this->floorTexture->setSmooth(true);
			this->floorTexture->generateMipmap();

			this->playerTexture = new sf::Texture();
			if (!this->playerTexture->loadFromFile("resources/textures/investigator-tileset.png")) {
				throw "Could not load player tileset texture";
			}

			this->playerPosition = sf::Vector2i(0, 0);
			this->playerDirection = CompassDirection::DOWN;
			this->playerMovingFlag = false;
			this->playerAnimationStartSeconds = 0.0f;
		}

		GameplaySceneController::~GameplaySceneController() {
			delete this->floorTexture;
			delete this->playerTexture;
		}

		void GameplaySceneController::beginGameplay() {
			this->gameplayClock.restart();
			this->playerPosition = sf::Vector2i(0, 0);
			this->playerDirection = CompassDirection::DOWN;
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

				}
			}

			return result;
		}

		void GameplaySceneController::update() {
			float gameplaySeconds = this->gameplayClock.getElapsedTime().asSeconds();

			bool upPressedFlag = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
			bool rightPressedFlag = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
			bool downPressedFlag = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
			bool leftPressedFlag = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);

			CompassDirection currMovementDirection = CompassDirection::NONE;
			if (upPressedFlag && !downPressedFlag) {
				currMovementDirection = CompassDirection::UP;
			}
			if (downPressedFlag && !upPressedFlag) {
				currMovementDirection = CompassDirection::DOWN;
			}
			if (rightPressedFlag && !leftPressedFlag) {
				currMovementDirection = CompassDirection::RIGHT;
			}
			if (leftPressedFlag && !rightPressedFlag) {
				currMovementDirection = CompassDirection::LEFT;
			}

			if (currMovementDirection != CompassDirection::NONE) {
				if (!this->playerMovingFlag) {
					this->startPlayerMovement(currMovementDirection);
				}
				else if (gameplaySeconds - this->playerAnimationStartSeconds > SECONDS_TO_MOVE) {
					this->playerPosition += CompassDirectionUtils::convertToVector(this->playerDirection);
					this->startPlayerMovement(currMovementDirection);
				}
			}
			else {
				if (
					this->playerMovingFlag &&
					(gameplaySeconds - this->playerAnimationStartSeconds > SECONDS_TO_MOVE)
				) {
					this->playerPosition += CompassDirectionUtils::convertToVector(this->playerDirection);
					this->playerMovingFlag = false;
					this->playerAnimationStartSeconds = this->gameplayClock.getElapsedTime().asSeconds();
				}
			}
		}

		void GameplaySceneController::render() {
			float gameplaySeconds = this->gameplayClock.getElapsedTime().asSeconds();
			sf::Vector2f playerRenderPosition = this->resolvePlayerPosition(gameplaySeconds);

			float viewWidth = 15.0f * 2.0f;
			float viewHeight = 8.4375f * 2.0f;

			this->window->setView(sf::View(sf::FloatRect(playerRenderPosition.x - viewWidth / 2.0f, playerRenderPosition.y - viewHeight / 2.0f, viewWidth, viewHeight)));

			this->window->clear();

			this->window->draw(this->createGrassSprite());

			sf::Sprite playerSprite = this->createPlayerSprite(gameplaySeconds);
			playerSprite.setPosition(playerRenderPosition);
			this->window->draw(playerSprite);

			this->window->display();
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

		sf::Sprite GameplaySceneController::createGrassSprite() {
			sf::Sprite result(*this->floorTexture);
			result.setPosition(-15.0f / 2.0f, -8.4375f / 2.0f);
			result.setScale(1.0f / 256.0f, 1.0f / 256.0f);
			result.setTextureRect(sf::IntRect(0, 0, 3840, 2160));
			return result;
		}

		sf::Sprite GameplaySceneController::createPlayerSprite(float gameplaySeconds) {
			sf::Sprite result(*this->playerTexture);

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
