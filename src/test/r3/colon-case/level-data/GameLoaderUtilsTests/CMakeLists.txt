
add_executable(
	GameLoaderUtilsTests
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameLoaderUtils.cpp
	GameLoaderUtilsTests-main.cpp
)
target_link_libraries(
	GameLoaderUtilsTests PRIVATE
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
	r3-TiledJsonLoader-lib
	sfml-graphics
)
target_include_directories(GameLoaderUtilsTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_test(NAME GameLoaderUtils COMMAND GameLoaderUtilsTests)
