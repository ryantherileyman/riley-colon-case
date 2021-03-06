
#include "../level-data/r3-colonCase-AssetManager.hpp"
#include <SFML/Graphics.hpp>
#pragma once

namespace r3 {

	namespace colonCase {

		typedef enum class ColonCase_CompassDirection {
			NONE,
			UP,
			RIGHT,
			DOWN,
			LEFT,
		} CompassDirection;

		namespace CompassDirectionUtils {

			extern CompassDirection convertFromKeyCode(sf::Keyboard::Key code);
			extern sf::Vector2i convertToVector(CompassDirection direction);

		}

		typedef enum class ColonCase_GameplaySceneClientRequest {
			NONE,
			RETURN_TO_SPLASH,
			EXIT_GAME,
		} GameplaySceneClientRequest;

		typedef struct ColonCase_GameplayKeyPressedClientInput {
			sf::Keyboard::Key keyCode = sf::Keyboard::Key::Unknown;
		} GameplayKeyPressedClientInput;

		typedef enum class ColonCase_GameplayKeyPressedClientRequest {
			NONE,
			SCENE_REQUEST,
			ZOOM_VIEW_IN_REQUEST,
			ZOOM_VIEW_OUT_REQUEST,
			MOVE_PLAYER,
		} GameplayKeyPressedClientRequest;

		typedef struct ColonCase_GameplayKeyPressedResult {
			GameplayKeyPressedClientRequest keyPressedClientRequest = GameplayKeyPressedClientRequest::NONE;
			GameplaySceneClientRequest sceneClientRequest = GameplaySceneClientRequest::NONE;
			CompassDirection requestedPlayerDirection = CompassDirection::NONE;
		} GameplayKeyPressedResult;

		typedef struct ColonCase_GameplayKeyReleasedClientInput {
			sf::Keyboard::Key keyCode = sf::Keyboard::Key::Unknown;
			CompassDirection requestedPlayerDirection = CompassDirection::NONE;
		} GameplayKeyReleasedClientInput;

		typedef enum class ColonCase_GameplayKeyReleasedClientRequest {
			NONE,
			STOP_PLAYER,
		} GameplayKeyReleasedClientRequest;

		typedef struct ColonCase_GameplayKeyReleasedResult {
			GameplayKeyReleasedClientRequest keyReleasedClientRequest = GameplayKeyReleasedClientRequest::NONE;
		} GameplayKeyReleasedResult;

		namespace GameplayKeyboardEventUtils {

			extern GameplayKeyPressedResult processKeyPressed(const GameplayKeyPressedClientInput& input);
			extern GameplayKeyReleasedResult processKeyReleased(const GameplayKeyReleasedClientInput& input);

		}

		class GameplaySceneController;
		
		class GameplaySceneController {

		private:
			sf::RenderWindow* window;

		private:
			sf::Texture playerTexture;
			AssetManager assetManager;

		private:
			sf::Clock gameplayClock;
			int pixelsPerTile;
			CompassDirection requestedPlayerDirection;
			sf::Vector2i playerPosition;
			CompassDirection playerDirection;
			bool playerMovingFlag;
			float playerAnimationStartSeconds;

		public:
			GameplaySceneController(sf::RenderWindow& window);

		public:
			void beginGameplay();
			GameplaySceneClientRequest processEvent(sf::Event& event);
			void update();
			void render();

		private:
			GameplaySceneClientRequest processKeyPressedEvent(sf::Keyboard::Key keyCode);
			void processKeyReleasedEvent(sf::Keyboard::Key keyCode);

		private:
			void startPlayerMovement(CompassDirection direction);

		private:
			sf::Vector2f resolvePlayerPosition(float gameplaySeconds);
			sf::Sprite createPlayerSprite(float gameplaySeconds);

		};

	}

}
