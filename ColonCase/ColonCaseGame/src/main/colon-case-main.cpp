
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>

int main() {
	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 450), L"Riley Entertainment - The Colon Case");
	window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, 1920.0f, 1080.0f)));

	sf::Texture splashTexture;
	if (!splashTexture.loadFromFile("resources/colon-case-splash.png")) {
		throw "Could not load splash screen graphic";
	}
	sf::Sprite splashSprite;
	splashSprite.setTexture(splashTexture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (window.isOpen()) {
			window.draw(splashSprite);
			window.display();
		}

		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}

	return 0;
}
