
#include <r3/colon-case/splash-screen/r3-colonCase-splashScreen.hpp>

namespace r3 {

	namespace colonCase {

		const char* SPLASH_UI_FONT_PATH = "resources/fonts/OpenSans-Bold.ttf";

		const sf::Color SPLASH_BACKGROUND_COLOR = sf::Color(5, 4, 3, 255);
		const char* SPLASH_IMAGE_PATH = "resources/textures/colon-case-splash.png";

		const float SPLASH_MENU_TOP = 680.0f;
		const float SPLASH_MENU_LEFT = 60.0f;
		const float SPLASH_MENU_ITEM_HEIGHT = 80.0f;
		const float SPLASH_MENU_ITEM_VERT_MARGIN = 20.0f;
		const float SPLASH_MENU_ITEM_HORZ_MARGIN = 30.0f;
		const float SPLASH_MENU_ITEM_VERT_BACKGROUND_OFFSET = 5.0f;

		SplashSceneRenderer::SplashSceneRenderer() {
			this->uiFont = new sf::Font();
			this->splashTexture = new sf::Texture();
			
			if (!this->uiFont->loadFromFile(SPLASH_UI_FONT_PATH)) {
				throw "Could not load user interface font";
			}

			if (!this->splashTexture->loadFromFile(SPLASH_IMAGE_PATH)) {
				throw "Could not load splash screen";
			}

			this->splashSprite.setTexture(*this->splashTexture);
		}

		SplashSceneRenderer::~SplashSceneRenderer() {
			delete this->uiFont;
			delete this->splashTexture;
		}

		void SplashSceneRenderer::render(sf::RenderTarget& renderTarget, const MainMenu& menu) {
			renderTarget.clear(SPLASH_BACKGROUND_COLOR);
			renderTarget.draw(this->splashSprite);
			this->renderMenu(renderTarget, menu);
		}

		MainMenuMousePositionResult SplashSceneRenderer::resolveMenuMousePositionResult(const MainMenu& menu, const sf::Vector2f& cursorPosition) const {
			MainMenuMousePositionResult result;

			float highestMenuItemWidth = MainMenuUiUtils::resolveHighestMenuItemWidth(menu, *this->uiFont);
			float menuWidth = highestMenuItemWidth + (SPLASH_MENU_ITEM_HORZ_MARGIN * 2.0f);
			
			float currTop = SPLASH_MENU_TOP;
			
			for (auto const& currMenuItemDefn : menu.getMenuItemDefnMap()) {
				sf::FloatRect menuItemBounds(SPLASH_MENU_LEFT, currTop, menuWidth, SPLASH_MENU_ITEM_HEIGHT);
				if (menuItemBounds.contains(cursorPosition)) {
					result.overMenuItemFlag = true;
					result.overMenuItemId = currMenuItemDefn.first;
				}

				currTop += SPLASH_MENU_ITEM_HEIGHT;
			}

			return result;
		}

		void SplashSceneRenderer::renderMenu(sf::RenderTarget& renderTarget, const MainMenu& menu) {
			MainMenuItemRenderState itemRenderState(menu, SPLASH_MENU_TOP);
			itemRenderState.backgroundWidth = (SPLASH_MENU_ITEM_HORZ_MARGIN * 2.0f) + MainMenuUiUtils::resolveHighestMenuItemWidth(menu, *this->uiFont);

			for (auto const& currMenuItemDefn : menu.getMenuItemDefnMap()) {
				itemRenderState.menuItemId = currMenuItemDefn.first;
				this->renderMenuItem(renderTarget, itemRenderState);

				itemRenderState.top += SPLASH_MENU_ITEM_HEIGHT;
			}
		}

		void SplashSceneRenderer::renderMenuItem(sf::RenderTarget& renderTarget, const MainMenuItemRenderState& itemRenderState) {
			MainMenuItemDefn menuItemDefn = itemRenderState.menu->getItemDefn(itemRenderState.menuItemId);

			if (
				itemRenderState.menu->getFocusItemFlag() &&
				(itemRenderState.menu->getFocusItemId() == itemRenderState.menuItemId)
			) {
				this->renderFocusedMenuItemBackground(renderTarget, itemRenderState);
			}

			this->renderMenuItemLabel(renderTarget, itemRenderState);
		}

		void SplashSceneRenderer::renderFocusedMenuItemBackground(sf::RenderTarget& renderTarget, const MainMenuItemRenderState& itemRenderState) {
			sf::RectangleShape backgroundShape(sf::Vector2f(itemRenderState.backgroundWidth, SPLASH_MENU_ITEM_HEIGHT));
			backgroundShape.setPosition(SPLASH_MENU_LEFT, itemRenderState.top + SPLASH_MENU_ITEM_VERT_BACKGROUND_OFFSET);
			backgroundShape.setFillColor(sf::Color(26, 16, 11, 192));
			
			renderTarget.draw(backgroundShape);
		}

		void SplashSceneRenderer::renderMenuItemLabel(sf::RenderTarget& renderTarget, const MainMenuItemRenderState& itemRenderState) {
			sf::Text menuItemText = MainMenuUiUtils::createEmptyMenuItemText(*this->uiFont);
			menuItemText.setPosition(SPLASH_MENU_LEFT + SPLASH_MENU_ITEM_HORZ_MARGIN, itemRenderState.top + (SPLASH_MENU_ITEM_VERT_MARGIN / 2.0f));
			menuItemText.setString(itemRenderState.menu->getItemDefn(itemRenderState.menuItemId).displayText);

			renderTarget.draw(menuItemText);
		}

	}

}
