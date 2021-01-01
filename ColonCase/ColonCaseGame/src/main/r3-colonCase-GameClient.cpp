
#include <chrono>
#include <thread>
#include "sfml-utils/r3-sfml-utils.hpp"
#include "r3-colonCase-client.hpp"

namespace r3 {

	namespace colonCase {

		const wchar_t* WINDOW_TITLE = L"Riley Entertainment - The Colon Case";
		const unsigned int WINDOW_INITIAL_WIDTH = 800;
		const unsigned int WINDOW_INITIAL_HEIGHT = 450;

		GameClient::GameClient() {
			this->window.create(sf::VideoMode(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT), L"Riley Entertainment - The Colon Case");
			this->window.setView(r3::SfmlUtils::ViewUtils::createView(this->window.getSize().x, this->window.getSize().y));

			this->splashSceneController = new SplashSceneController(this->window);
		}

		GameClient::~GameClient() {
			delete this->splashSceneController;
		}

		void GameClient::run() {
			sf::Clock frameClock;

			while (this->window.isOpen()) {
				sf::Event event;
				while (this->window.pollEvent(event)) {
					r3::colonCase::SplashSceneClientRequest clientRequest = this->splashSceneController->processEvent(event);
					if (clientRequest == r3::colonCase::SplashSceneClientRequest::EXIT_GAME) {
						this->window.close();
					}
				}

				if (window.isOpen()) {
					if (frameClock.getElapsedTime().asMicroseconds() >= 8333) {
						this->splashSceneController->render();
						frameClock.restart();
					}
				}

				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		}

	}

}
