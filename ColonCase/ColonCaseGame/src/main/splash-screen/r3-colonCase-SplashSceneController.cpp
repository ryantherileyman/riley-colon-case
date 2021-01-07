
#include "../sfml-utils/r3-sfml-utils.hpp"
#include "r3-colonCase-splashScreen.hpp"

namespace r3 {

	namespace colonCase {

		SplashSceneController::SplashSceneController(sf::RenderWindow& window) {
			this->window = &window;
			this->renderer = new SplashSceneRenderer();

			this->mainMenu = new MainMenu(MainMenuFactory::createMainMenuItemDefnMap());
		}

		SplashSceneController::~SplashSceneController() {
			delete this->renderer;
			delete this->mainMenu;
		}

		SplashSceneClientRequest SplashSceneController::processEvent(sf::Event& event) {
			SplashSceneClientRequest result = SplashSceneClientRequest::NONE;

			if (event.type == sf::Event::Closed) {
				result = SplashSceneClientRequest::EXIT_GAME;
			}
			else if (event.type == sf::Event::Resized) {
				this->window->setView(r3::SfmlUtils::ViewUtils::createView(event.size.width, event.size.height));
			}
			else if (event.type == sf::Event::KeyPressed) {
				result = this->processKeypressEvent(event);
			}
			else if (event.type == sf::Event::MouseMoved) {
				this->processMouseMovedEvent(event);
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					result = this->processLeftMouseButtonPressedEvent(event);
				}
			}

			return result;
		}

		void SplashSceneController::render() {
			this->window->setView(r3::SfmlUtils::ViewUtils::createView(this->window->getSize().x, this->window->getSize().y));
			this->renderer->render(*this->window, *this->mainMenu);
			this->window->display();
		}

		SplashSceneClientRequest SplashSceneController::processKeypressEvent(sf::Event& event) {
			SplashSceneClientRequest result = SplashSceneClientRequest::NONE;

			MainMenuKeypressResult keypressResult = MainMenuUiUtils::processKeypressEvent(event, *this->mainMenu);
			if (keypressResult.performedActionFlag) {
				result = this->performMainMenuItemAction(this->mainMenu->getFocusItemId());
			}

			return result;
		}

		void SplashSceneController::processMouseMovedEvent(sf::Event& event) {
			sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
			MainMenuMousePositionResult mousePositionResult = this->renderer->resolveMenuMousePositionResult(*this->mainMenu, mousePosition);

			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (mousePositionResult.overMenuItemFlag) {
					this->mainMenu->setFocusItem(mousePositionResult.overMenuItemId);
				}
			}
		}

		SplashSceneClientRequest SplashSceneController::processLeftMouseButtonPressedEvent(sf::Event& event) {
			SplashSceneClientRequest result = SplashSceneClientRequest::NONE;

			sf::Vector2f mousePosition = this->window->mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			MainMenuMousePositionResult mousePositionResult = this->renderer->resolveMenuMousePositionResult(*this->mainMenu, mousePosition);

			if (mousePositionResult.overMenuItemFlag) {
				switch (mousePositionResult.overMenuItemId) {

				case MainMenuItemId::START_NEW_GAME:
					result = SplashSceneClientRequest::START_NEW_GAME;
					break;

				case MainMenuItemId::EXIT_GAME:
					result = SplashSceneClientRequest::EXIT_GAME;
					break;

				}
			}
			else {
				this->mainMenu->loseFocus();
			}

			return result;
		}

		SplashSceneClientRequest SplashSceneController::performMainMenuItemAction(int menuItemId) {
			SplashSceneClientRequest result = SplashSceneClientRequest::NONE;

			switch (menuItemId) {

			case MainMenuItemId::START_NEW_GAME:
				result = SplashSceneClientRequest::START_NEW_GAME;
				break;

			case MainMenuItemId::EXIT_GAME:
				result = SplashSceneClientRequest::EXIT_GAME;
				break;

			}

			return result;
		}

	}

}
