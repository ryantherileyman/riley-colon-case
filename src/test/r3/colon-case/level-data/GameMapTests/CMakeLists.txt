
add_executable(
	GameMapObjectTests
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMapObject.cpp
	GameMapObjectTests-main.cpp
)
target_link_libraries(
	GameMapObjectTests PRIVATE
	sfml-graphics
	r3-SfmlGeometryUtils-lib
)
target_include_directories(GameMapObjectTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

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
	sfml-graphics
	r3-SfmlGeometryUtils-lib
)
target_include_directories(GameMapTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_test(NAME GameMapObject COMMAND GameMapObjectTests)
add_test(NAME GameMap COMMAND GameMapTests)
