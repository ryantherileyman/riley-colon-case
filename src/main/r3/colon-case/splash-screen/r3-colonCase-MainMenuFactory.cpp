
#include <r3/colon-case/splash-screen/r3-colonCase-mainMenu.hpp>

namespace r3 {

	namespace colonCase {

		namespace MainMenuLabels {

			const wchar_t* START_NEW_GAME_LABEL = L"START NEW GAME";

			const wchar_t* EXIT_GAME_LABEL = L"EXIT GAME";

		}

		namespace MainMenuFactory {

			std::map<int, MainMenuItemDefn> createMainMenuItemDefnMap() {
				std::map<int, MainMenuItemDefn> result;

				result[MainMenuItemId::START_NEW_GAME] = MainMenuItemDefn{ MainMenuItemId::START_NEW_GAME, MainMenuLabels::START_NEW_GAME_LABEL };
				result[MainMenuItemId::EXIT_GAME] = MainMenuItemDefn{ MainMenuItemId::EXIT_GAME, MainMenuLabels::EXIT_GAME_LABEL };

				return result;
			}

		}

	}

}
