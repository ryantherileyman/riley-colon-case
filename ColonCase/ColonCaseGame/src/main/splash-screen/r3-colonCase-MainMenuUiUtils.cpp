
#include "../sfml-utils/r3-sfml-utils.hpp"
#include "r3-colonCase-splashScreen.hpp"

namespace r3 {

	namespace colonCase {

		namespace MainMenuUiUtils {

			MainMenuKeypressResult processKeypressEvent(sf::Event& event, MainMenu& mainMenu) {
				MainMenuKeypressResult result;

				switch (event.key.code) {

				case sf::Keyboard::Key::Enter:
				case sf::Keyboard::Key::Space:
					if (mainMenu.getFocusItemFlag()) {
						result.performedActionFlag = true;
						result.actionMenuItemId = mainMenu.getFocusItemId();
					}
					break;

				case sf::Keyboard::Key::Up:
					mainMenu.focusPreviousItem();
					break;

				case sf::Keyboard::Key::Down:
					mainMenu.focusNextItem();
					break;

				}

				return result;
			}

			float resolveHighestMenuItemWidth(const MainMenu& mainMenu, const sf::Font& font) {
				float result = 0.0f;

				sf::Text menuItemText = createEmptyMenuItemText(font);

				for (auto const& currMenuItemDefn : mainMenu.getMenuItemDefnMap()) {
					menuItemText.setString(currMenuItemDefn.second.displayText);

					float itemWidth = r3::SfmlUtils::FontUtils::resolveTextWidth(menuItemText);

					if (itemWidth > result) {
						result = itemWidth;
					}
				}

				return result;
			}

			sf::Text createEmptyMenuItemText(const sf::Font& font) {
				sf::Text result;
				result.setFont(font);
				result.setCharacterSize(56);
				result.setFillColor(sf::Color(149, 117, 79, 240));
				return result;
			}

		}

	}

}
