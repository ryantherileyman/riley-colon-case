
#include <assert.h>
#include <r3/colon-case/splash-screen/r3-colonCase-mainMenu.hpp>

namespace r3 {

	namespace colonCase {

		MainMenu::MainMenu(const std::map<int, MainMenuItemDefn>& menuItemDefnList) {
			for (auto const& currMenuItemDefn : menuItemDefnList) {
				this->menuItemDefnMap[currMenuItemDefn.first] = currMenuItemDefn.second;
			}

			this->focusItemFlag = false;
			this->focusItemId = 0;
		}

		std::map<int, MainMenuItemDefn> MainMenu::getMenuItemDefnMap() const {
			return this->menuItemDefnMap;
		}

		const MainMenuItemDefn& MainMenu::getItemDefn(int menuItemId) const {
			const MainMenuItemDefn& result = this->menuItemDefnMap.at(menuItemId);
			return result;
		}

		bool MainMenu::getFocusItemFlag() const {
			return this->focusItemFlag;
		}

		int MainMenu::getFocusItemId() const {
			assert(this->focusItemFlag);

			return this->focusItemId;
		}

		const MainMenuItemDefn& MainMenu::getFocusItemDefn() const {
			assert(this->focusItemFlag);

			const MainMenuItemDefn& result = this->menuItemDefnMap.at(this->focusItemId);
			return result;
		}

		void MainMenu::loseFocus() {
			this->focusItemFlag = false;
			this->focusItemId = 0;
		}

		int MainMenu::focusFirstItem() {
			this->focusItemFlag = true;
			this->focusItemId = this->menuItemDefnMap.begin()->first;

			return this->focusItemId;
		}

		void MainMenu::setFocusItem(int menuItemId) {
			assert(this->menuItemDefnMap.count(menuItemId) == 1);

			this->focusItemFlag = true;
			this->focusItemId = menuItemId;
		}

		int MainMenu::focusNextItem() {
			if (this->focusItemFlag) {
				std::map<int, MainMenuItemDefn>::iterator nextIterator = ++this->menuItemDefnMap.find(this->focusItemId);
				if (nextIterator == this->menuItemDefnMap.end()) {
					nextIterator = this->menuItemDefnMap.begin();
				}

				this->focusItemId = nextIterator->first;
			}
			else {
				this->focusItemFlag = true;
				this->focusItemId = this->menuItemDefnMap.begin()->first;
			}

			return this->focusItemId;
		}

		int MainMenu::focusPreviousItem() {
			if (this->focusItemFlag) {
				std::map<int, MainMenuItemDefn>::iterator prevIterator = --this->menuItemDefnMap.find(this->focusItemId);
				if (prevIterator == this->menuItemDefnMap.end()) {
					--prevIterator;
				}

				this->focusItemId = prevIterator->first;
			}
			else {
				this->focusItemFlag = true;
				this->focusItemId = this->menuItemDefnMap.begin()->first;
			}

			return this->focusItemId;
		}

	}

}
