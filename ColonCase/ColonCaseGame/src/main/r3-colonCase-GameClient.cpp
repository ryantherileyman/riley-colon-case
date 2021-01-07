
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
			this->clientMode = ClientMode::SPLASH_SCREEN;

			this->window.create(sf::VideoMode(WINDOW_INITIAL_WIDTH, WINDOW_INITIAL_HEIGHT), L"Riley Entertainment - The Colon Case");
			this->window.setView(r3::SfmlUtils::ViewUtils::createView(this->window.getSize().x, this->window.getSize().y));

			this->splashSceneController = new SplashSceneController(this->window);
			this->gameplaySceneController = new GameplaySceneController(this->window);
		}

		GameClient::~GameClient() {
			delete this->splashSceneController;
			delete this->gameplaySceneController;
		}

		void GameClient::run() {
			sf::Clock frameClock;

			while (this->window.isOpen()) {
				sf::Event event;
				while (this->window.pollEvent(event)) {
					switch (this->clientMode) {

					case ClientMode::SPLASH_SCREEN:
						this->processSplashSceneEvent(event);
						break;

					case ClientMode::GAMEPLAY_SCREEN:
						this->processGameplaySceneEvent(event);
						break;

					}
				}

				switch (this->clientMode) {

				case ClientMode::GAMEPLAY_SCREEN:
					this->gameplaySceneController->update();
					break;

				}

				if (window.isOpen()) {
					if (frameClock.getElapsedTime().asMicroseconds() >= 8333) {
						switch (this->clientMode) {

						case ClientMode::SPLASH_SCREEN:
							this->splashSceneController->render();
							break;

						case ClientMode::GAMEPLAY_SCREEN:
							this->gameplaySceneController->render();
							break;
						}

						frameClock.restart();
					}
				}

				std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		}

		void GameClient::processSplashSceneEvent(sf::Event& event) {
			SplashSceneClientRequest clientRequest = this->splashSceneController->processEvent(event);

			switch (clientRequest) {

			case SplashSceneClientRequest::START_NEW_GAME:
				this->clientMode = ClientMode::GAMEPLAY_SCREEN;
				this->gameplaySceneController->beginGameplay();
				break;

			case SplashSceneClientRequest::EXIT_GAME:
				this->window.close();
				break;

			}
		}

		void GameClient::processGameplaySceneEvent(sf::Event& event) {
			GameplaySceneClientRequest clientRequest = this->gameplaySceneController->processEvent(event);

			switch (clientRequest) {

			case GameplaySceneClientRequest::RETURN_TO_SPLASH:
				this->clientMode = ClientMode::SPLASH_SCREEN;
				break;

			case GameplaySceneClientRequest::EXIT_GAME:
				this->window.close();
				break;

			}
		}

	}

}
