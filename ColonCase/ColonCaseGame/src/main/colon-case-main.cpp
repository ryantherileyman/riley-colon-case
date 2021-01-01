
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "sfml-utils/r3-sfml-utils.hpp"
#include "splash-screen/r3-colonCase-splashScreen.hpp"

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 450), L"Riley Entertainment - The Colon Case");
	window.setView(r3::SfmlUtils::ViewUtils::createView(800, 450));

	r3::colonCase::SplashSceneController splashSceneController(window);

	sf::Clock frameClock;
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			r3::colonCase::SplashSceneClientRequest clientRequest = splashSceneController.processEvent(event);
			if (clientRequest == r3::colonCase::SplashSceneClientRequest::EXIT_GAME) {
				window.close();
			}
		}

		if (window.isOpen()) {
			if (frameClock.getElapsedTime().asMicroseconds() >= 8333) {
				splashSceneController.render();
				frameClock.restart();
			}
		}

		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}

	return 0;
}
