
#include <SFML/Graphics.hpp>
#include "splash-screen/r3-colonCase-splashScreen.hpp"
#include "gameplay/r3-colonCase-gameplay.hpp"
#pragma once

namespace r3 {

	namespace colonCase {

		typedef enum class ColonCase_ClientMode {
			SPLASH_SCREEN,
			GAMEPLAY_SCREEN,
		} ClientMode;

		class GameClient;

		class GameClient {

		private:
			ClientMode clientMode;
			sf::RenderWindow window;

		private:
			SplashSceneController* splashSceneController;
			GameplaySceneController* gameplaySceneController;

		public:
			GameClient();

		public:
			~GameClient();

		public:
			void run();

		private:
			void processSplashSceneEvent(sf::Event& event);
			void processGameplaySceneEvent(sf::Event& event);

		};

	}

}
