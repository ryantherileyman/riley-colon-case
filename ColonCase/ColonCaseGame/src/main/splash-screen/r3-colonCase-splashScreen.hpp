
#include "r3-colonCase-mainMenu.hpp"
#include <SFML/Graphics.hpp>
#pragma once

namespace r3 {

	namespace colonCase {

		typedef struct ColonCase_MainMenuKeypressResult {
			bool performedActionFlag = false;
			int actionMenuItemId = 0;
		} MainMenuKeypressResult;

		typedef struct ColonCase_MainMenuMousePositionResult {
			bool overMenuItemFlag = false;
			int overMenuItemId = 0;
		} MainMenuMousePositionResult;

		typedef enum class ColonCase_SplashSceneClientRequest {
			NONE,
			EXIT_GAME,
		} SplashSceneClientRequest;

		namespace MainMenuUiUtils {

			extern MainMenuKeypressResult processKeypressEvent(sf::Event& event, MainMenu& mainMenu);

			extern float resolveHighestMenuItemWidth(const MainMenu& mainMenu, const sf::Font& font);
			extern sf::Text createEmptyMenuItemText(const sf::Font& font);

		}

		class SplashSceneController;
		class SplashSceneRenderer;

		class SplashSceneController {

		private:
			sf::RenderWindow* window;
			SplashSceneRenderer* renderer;

		private:
			MainMenu* mainMenu;

		public:
			SplashSceneController(sf::RenderWindow& window);

		public:
			~SplashSceneController();

		public:
			SplashSceneClientRequest processEvent(sf::Event& event);
			void render();

		private:
			SplashSceneClientRequest processKeypressEvent(sf::Event& event);
			void processMouseMovedEvent(sf::Event& event);
			SplashSceneClientRequest processLeftMouseButtonPressedEvent(sf::Event& event);

		private:
			SplashSceneClientRequest performMainMenuItemAction(int menuItemId);

		};

		typedef struct ColonCase_MainMenuItemRenderState {
			const MainMenu* menu;
			int menuItemId;
			float top;
			float backgroundWidth;

			struct ColonCase_MainMenuItemRenderState(const MainMenu& menu, float top) {
				this->menu = &menu;
				this->menuItemId = 0;
				this->top = top;
				this->backgroundWidth = 0.0f;
			}
		} MainMenuItemRenderState;

		class SplashSceneRenderer {

		private:
			sf::Font* uiFont;
			sf::Texture* splashTexture;

		private:
			sf::Sprite splashSprite;

		public:
			SplashSceneRenderer();

		public:
			~SplashSceneRenderer();

		public:
			void render(sf::RenderTarget& renderTarget, const MainMenu& menu);

		public:
			MainMenuMousePositionResult resolveMenuMousePositionResult(const MainMenu& menu, const sf::Vector2f& cursorPosition) const;

		private:
			void renderMenu(sf::RenderTarget& renderTarget, const MainMenu& menu);
			void renderMenuItem(sf::RenderTarget& renderTarget, const MainMenuItemRenderState& itemRenderState);
			void renderFocusedMenuItemBackground(sf::RenderTarget& renderTarget, const MainMenuItemRenderState& itemRenderState);
			void renderMenuItemLabel(sf::RenderTarget& renderTarget, const MainMenuItemRenderState& itemRenderState);

		};

	}

}
