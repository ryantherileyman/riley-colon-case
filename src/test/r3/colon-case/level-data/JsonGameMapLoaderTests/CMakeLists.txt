
add_executable(
	JsonGameMapLoaderTests
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-GameLoaderUtils.cpp
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-JsonGameMapLoader.cpp
	JsonGameMapLoaderTests-main.cpp
)
target_link_libraries(
	JsonGameMapLoaderTests PRIVATE
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
	r3-TiledJsonLoader-lib
	sfml-graphics
)
target_include_directories(JsonGameMapLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")
add_custom_command(
	TARGET JsonGameMapLoaderTests
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/src/test-resources/r3/colon-case/level-data/JsonGameMapLoaderTests
		$<TARGET_FILE_DIR:JsonGameMapLoaderTests>
)

add_test(NAME JsonGameMapLoader COMMAND JsonGameMapLoaderTests)
