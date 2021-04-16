
#include <r3/colon-case/gameplay/r3-colonCase-gameplay.hpp>

namespace r3 {

	namespace colonCase {

		namespace CompassDirectionUtils {

			CompassDirection convertFromKeyCode(sf::Keyboard::Key code) {
				CompassDirection result = CompassDirection::NONE;

				switch (code) {

				case sf::Keyboard::Key::Up:
					result = CompassDirection::UP;
					break;

				case sf::Keyboard::Key::Right:
					result = CompassDirection::RIGHT;
					break;

				case sf::Keyboard::Key::Down:
					result = CompassDirection::DOWN;
					break;

				case sf::Keyboard::Key::Left:
					result = CompassDirection::LEFT;
					break;

				}

				return result;
			}

			sf::Vector2i convertToVector(CompassDirection direction) {
				sf::Vector2i result(0, 0);

				switch (direction) {

				case CompassDirection::UP:
					result = sf::Vector2i(0, -1);
					break;

				case CompassDirection::RIGHT:
					result = sf::Vector2i(1, 0);
					break;

				case CompassDirection::DOWN:
					result = sf::Vector2i(0, 1);
					break;

				case CompassDirection::LEFT:
					result = sf::Vector2i(-1, 0);
					break;

				}

				return result;
			}

		}

	}

}
