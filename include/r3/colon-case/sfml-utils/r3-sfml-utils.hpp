
#include <SFML/Graphics.hpp>
#pragma once

namespace r3 {

	namespace SfmlUtils {

		namespace ViewUtils {

			extern float VIEW_ASPECT_RATIO;
			extern sf::Vector2f VIEW_SIZE;

			extern sf::View createView(unsigned int windowWidth, unsigned int windowHeight);

		}

		namespace FontUtils {

			extern float resolveTextWidth(sf::Text& text);

		}

	}

}
