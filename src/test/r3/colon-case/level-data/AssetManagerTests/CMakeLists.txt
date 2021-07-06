
add_executable(
	AssetManagerTests
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameLoaderUtils.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-JsonGameMapLoader.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameSpriteImage.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameSpriteTile.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMapSprite.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMapLayer.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMapObject.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameMap.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-AssetLoadingTracker.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-AssetManager.cpp
	AssetManagerTests-main.cpp
)
target_link_libraries(
	AssetManagerTests PRIVATE
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
	r3-TiledJsonLoader-lib
	sfml-graphics
)
target_include_directories(AssetManagerTests PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_custom_command(
	TARGET AssetManagerTests
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/src/test-resources/r3/colon-case/level-data/AssetManagerTests
		$<TARGET_FILE_DIR:AssetManagerTests>
)

add_test(NAME AssetManager COMMAND AssetManagerTests)
