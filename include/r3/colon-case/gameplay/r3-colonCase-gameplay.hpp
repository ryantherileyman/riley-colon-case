
#include <memory>
#include <SFML/Graphics.hpp>
#include <r3/colon-case/level-data/r3-colonCase-AssetManager.hpp>
#pragma once

namespace r3 {

	namespace colonCase {

		typedef enum class ColonCase_CompassDirection {
			NONE,
			UP,
			RIGHT,
			DOWN,
			LEFT,
		} CompassDirection;

		namespace CompassDirectionUtils {

			extern CompassDirection convertFromKeyCode(sf::Keyboard::Key code);
			extern sf::Vector2i convertToVector(CompassDirection direction);

		}

		typedef enum class ColonCase_GameplaySceneClientRequest {
			NONE,
			RETURN_TO_SPLASH,
			EXIT_GAME,
		} GameplaySceneClientRequest;

		typedef struct ColonCase_GameplayKeyPressedClientInput {
			sf::Keyboard::Key keyCode = sf::Keyboard::Key::Unknown;
		} GameplayKeyPressedClientInput;

		typedef enum class ColonCase_GameplayKeyPressedClientRequest {
			NONE,
			SCENE_REQUEST,
			ZOOM_VIEW_IN_REQUEST,
			ZOOM_VIEW_OUT_REQUEST,
			MOVE_PLAYER,
		} GameplayKeyPressedClientRequest;

		typedef struct ColonCase_GameplayKeyPressedResult {
			GameplayKeyPressedClientRequest keyPressedClientRequest = GameplayKeyPressedClientRequest::NONE;
			GameplaySceneClientRequest sceneClientRequest = GameplaySceneClientRequest::NONE;
			CompassDirection requestedPlayerDirection = CompassDirection::NONE;
		} GameplayKeyPressedResult;

		typedef struct ColonCase_GameplayKeyReleasedClientInput {
			sf::Keyboard::Key keyCode = sf::Keyboard::Key::Unknown;
			CompassDirection requestedPlayerDirection = CompassDirection::NONE;
		} GameplayKeyReleasedClientInput;

		typedef enum class ColonCase_GameplayKeyReleasedClientRequest {
			NONE,
			STOP_PLAYER,
		} GameplayKeyReleasedClientRequest;

		typedef struct ColonCase_GameplayKeyReleasedResult {
			GameplayKeyReleasedClientRequest keyReleasedClientRequest = GameplayKeyReleasedClientRequest::NONE;
		} GameplayKeyReleasedResult;

		namespace GameplayKeyboardEventUtils {

			extern GameplayKeyPressedResult processKeyPressed(const GameplayKeyPressedClientInput& input);
			extern GameplayKeyReleasedResult processKeyReleased(const GameplayKeyReleasedClientInput& input);

		}

		typedef enum class ColonCase_GameplayMouseCursorType {
			STANDARD,
			INVESTIGATE_ITEM,
		} GameplayMouseCursorType;

		typedef struct ColonCase_RenderGameMapInput {
			std::string mapFilename;
			int pixelsPerTile = 0;
			sf::Vector2f centerPosition;
		} RenderGameMapInput;

		namespace GameMapRenderUtils {
			
			extern sf::Vector2f resolveViewSize(const sf::Vector2u& targetSize, int pixelsPerTile);
			extern sf::IntRect resolveVisibleTileRect(const sf::View& view, const sf::Vector2i& mapSize);

		}

		class GameMapRenderer;
		class GameplaySceneController;
		
		class GameplaySceneController {

		private:
			sf::RenderWindow* window;
			sf::RenderTexture offscreenMapTexture;

		private:
			sf::Cursor defaultCursor;
			sf::Cursor investigateCursor;
			sf::Texture playerTexture;
			AssetManager assetManager;
			std::unique_ptr<GameMapRenderer> mapRendererPtr;

		private:
			sf::Clock gameplayClock;
			int pixelsPerTile;
			CompassDirection requestedPlayerDirection;
			sf::Vector2i playerPosition;
			CompassDirection playerDirection;
			bool playerMovingFlag;
			float playerAnimationStartSeconds;

		private:
			GameplayMouseCursorType currMouseCursorType;

		public:
			GameplaySceneController(sf::RenderWindow& window);

		public:
			void beginGameplay();
			GameplaySceneClientRequest processEvent(sf::Event& event);
			void update();
			void render();

		private:
			GameplaySceneClientRequest processKeyPressedEvent(sf::Keyboard::Key keyCode);
			void processKeyReleasedEvent(sf::Keyboard::Key keyCode);

		private:
			GameplayMouseCursorType resolveMouseCursorType();
			void changeMouseCursor(GameplayMouseCursorType mouseCursorType);

		private:
			void startPlayerMovement(CompassDirection direction);

		private:
			sf::Vector2f resolvePlayerPosition(float gameplaySeconds);
			sf::Sprite createPlayerSprite(float gameplaySeconds);

		};

		class GameMapRenderer {

		private:
			AssetManager* assetManager;

		private:
			sf::View view;
			sf::IntRect visibleTileRect;

		public:
			GameMapRenderer(AssetManager& assetManager);

		public:
			void renderMap(sf::RenderTarget& renderTarget, const RenderGameMapInput& renderInput);

		private:
			void renderTileLayer(sf::RenderTarget& renderTarget, const GameMap& gameMap, int layerIndex);
			void renderSpriteLayer(sf::RenderTarget& renderTarget, const GameMap& gameMap, int layerIndex);

		private:
			sf::Sprite createTileSprite(const GameMap& gameMap, int tileId);
			sf::Sprite createGameSprite(const GameMap& gameMap, const GameSpriteRenderDetails& spriteRenderDetails);

		};

	}

}
