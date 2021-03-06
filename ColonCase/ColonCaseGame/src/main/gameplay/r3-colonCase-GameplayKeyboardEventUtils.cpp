
#include "r3-colonCase-gameplay.hpp"

namespace r3 {

	namespace colonCase {

		namespace GameplayKeyboardEventUtils {

			GameplayKeyPressedResult processKeyPressed(const GameplayKeyPressedClientInput& input) {
				GameplayKeyPressedResult result;

				switch (input.keyCode) {

				case sf::Keyboard::Escape:
					result.keyPressedClientRequest = GameplayKeyPressedClientRequest::SCENE_REQUEST;
					result.sceneClientRequest = GameplaySceneClientRequest::RETURN_TO_SPLASH;
					break;

				case sf::Keyboard::Add:
					result.keyPressedClientRequest = GameplayKeyPressedClientRequest::ZOOM_VIEW_IN_REQUEST;
					break;

				case sf::Keyboard::Subtract:
					result.keyPressedClientRequest = GameplayKeyPressedClientRequest::ZOOM_VIEW_OUT_REQUEST;
					break;

				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					result.keyPressedClientRequest = GameplayKeyPressedClientRequest::MOVE_PLAYER;
					result.requestedPlayerDirection = CompassDirection::UP;
					break;

				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					result.keyPressedClientRequest = GameplayKeyPressedClientRequest::MOVE_PLAYER;
					result.requestedPlayerDirection = CompassDirection::RIGHT;
					break;

				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					result.keyPressedClientRequest = GameplayKeyPressedClientRequest::MOVE_PLAYER;
					result.requestedPlayerDirection = CompassDirection::DOWN;
					break;

				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					result.keyPressedClientRequest = GameplayKeyPressedClientRequest::MOVE_PLAYER;
					result.requestedPlayerDirection = CompassDirection::LEFT;
					break;

				}

				return result;
			}

			GameplayKeyReleasedResult processKeyReleased(const GameplayKeyReleasedClientInput& input) {
				GameplayKeyReleasedResult result;

				switch (input.keyCode) {

				case sf::Keyboard::Up:
				case sf::Keyboard::W:
					if (input.requestedPlayerDirection == CompassDirection::UP) {
						result.keyReleasedClientRequest = GameplayKeyReleasedClientRequest::STOP_PLAYER;
					}
					break;

				case sf::Keyboard::Right:
				case sf::Keyboard::D:
					if (input.requestedPlayerDirection == CompassDirection::RIGHT) {
						result.keyReleasedClientRequest = GameplayKeyReleasedClientRequest::STOP_PLAYER;
					}
					break;

				case sf::Keyboard::Down:
				case sf::Keyboard::S:
					if (input.requestedPlayerDirection == CompassDirection::DOWN) {
						result.keyReleasedClientRequest = GameplayKeyReleasedClientRequest::STOP_PLAYER;
					}
					break;

				case sf::Keyboard::Left:
				case sf::Keyboard::A:
					if (input.requestedPlayerDirection == CompassDirection::LEFT) {
						result.keyReleasedClientRequest = GameplayKeyReleasedClientRequest::STOP_PLAYER;
					}
					break;

				}

				return result;
			}

		}

	}

}
