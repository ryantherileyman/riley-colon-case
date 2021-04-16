
#include <map>
#pragma once

namespace r3 {

	namespace colonCase {

		typedef struct ColonCase_MainMenuItemDefn {
			int menuItemId;
			const wchar_t* displayText;
		} MainMenuItemDefn;

		namespace MainMenuItemId {

			const int START_NEW_GAME = 1;
			const int EXIT_GAME = 2;

		}

		namespace MainMenuFactory {

			extern std::map<int, MainMenuItemDefn> createMainMenuItemDefnMap();

		}

		class MainMenu {

		private:
			std::map<int, MainMenuItemDefn> menuItemDefnMap;

			bool focusItemFlag;
			int focusItemId;

		public:
			MainMenu(const std::map<int, MainMenuItemDefn>& menuItemDefnList);

		public:
			std::map<int, MainMenuItemDefn> getMenuItemDefnMap() const;
			const MainMenuItemDefn& getItemDefn(int menuItemId) const;

			bool getFocusItemFlag() const;
			int getFocusItemId() const;
			const MainMenuItemDefn& getFocusItemDefn() const;

		public:
			void loseFocus();
			void setFocusItem(int menuItemId);
			int focusFirstItem();
			int focusNextItem();
			int focusPreviousItem();

		};

	}

}
