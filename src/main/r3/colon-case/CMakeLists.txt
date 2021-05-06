
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(R3_COLON_CASE_SOURCES
	gameplay/GameMapRenderer.cpp
	gameplay/r3-colonCase-CompassDirectionUtils.cpp
	gameplay/r3-colonCase-GameMapRenderUtils.cpp
	gameplay/r3-colonCase-GameplayKeyboardEventUtils.cpp
	gameplay/r3-colonCase-GameplaySceneController.cpp
	level-data/r3-colonCase-AssetLoadingTracker.cpp
	level-data/r3-colonCase-AssetManager.cpp
	level-data/r3-colonCase-GameLoaderUtils.cpp
	level-data/r3-colonCase-GameMap.cpp
	level-data/r3-colonCase-GameMapLayer.cpp
	level-data/r3-colonCase-GameMapSprite.cpp
	level-data/r3-colonCase-GameSpriteImage.cpp
	level-data/r3-colonCase-GameSpriteTile.cpp
	level-data/r3-colonCase-JsonGameMapLoader.cpp
	level-data/r3-colonCase-JsonDictionaryLoader.cpp
	sfml-utils/r3-sfml-utils.cpp
	splash-screen/r3-colonCase-MainMenu.cpp
	splash-screen/r3-colonCase-MainMenuFactory.cpp
	splash-screen/r3-colonCase-MainMenuUiUtils.cpp
	splash-screen/r3-colonCase-SplashSceneController.cpp
	splash-screen/r3-colonCase-SplashSceneRenderer.cpp
	r3-colonCase-GameClient.cpp
	colon-case-main.cpp
)

add_executable(
	ColonCase
	${R3_COLON_CASE_SOURCES}
)
target_link_libraries(
	ColonCase
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
	r3-TiledJsonLoader-lib
	sfml-graphics
	sfml-audio
	sfml-window
	sfml-system
	sfml-main
	r3-SfmlGeometryUtils-lib
)
target_include_directories(ColonCase PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_custom_command(
	TARGET ColonCase
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/src/resources
		$<TARGET_FILE_DIR:ColonCase>/resources
)
