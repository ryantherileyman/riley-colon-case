
add_executable(
	GameMapTests
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameSpriteImage.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameSpriteTile.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMapSprite.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMapLayer.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMapObject.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMap.cpp
	GameMapTests-main.cpp
)
target_link_libraries(
	GameMapTests PRIVATE
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
	r3-TiledJsonLoader-lib
	sfml-graphics
)
target_include_directories(GameMapTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_test(NAME GameMap COMMAND GameMapTests)
