
#include <SFML/Graphics.hpp>
#include "splash-screen/r3-colonCase-splashScreen.hpp"
#pragma once

namespace r3 {

	namespace colonCase {

		class GameClient;

		class GameClient {

		private:
			sf::RenderWindow window;

		private:
			SplashSceneController* splashSceneController;

		public:
			GameClient();

		public:
			~GameClient();

		public:
			void run();

		};

	}

}
