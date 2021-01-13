
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

		class GameplaySceneController;
		
		class GameplaySceneController {

		private:
			sf::RenderWindow* window;

		private:
			sf::Texture* floorTexture;
			sf::Texture* playerTexture;

		private:
			sf::Clock gameplayClock;
			sf::Vector2i playerPosition;
			CompassDirection playerDirection;
			bool playerMovingFlag;
			float playerAnimationStartSeconds;

		public:
			GameplaySceneController(sf::RenderWindow& window);

		public:
			~GameplaySceneController();

		public:
			void beginGameplay();
			GameplaySceneClientRequest processEvent(sf::Event& event);
			void update();
			void render();

		private:
			void startPlayerMovement(CompassDirection direction);

		private:
			sf::Vector2f resolvePlayerPosition(float gameplaySeconds);
			sf::Sprite createGrassSprite();
			sf::Sprite createPlayerSprite(float gameplaySeconds);

		};

	}

}