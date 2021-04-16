
add_executable(
	AssetLoadingStatusTests
	AssetLoadingStatusTests-main.cpp
)
target_link_libraries(
	AssetLoadingStatusTests PRIVATE
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
	r3-TiledJsonLoader-lib
	sfml-graphics
)
target_include_directories(AssetLoadingStatusTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_test(NAME AssetLoadingStatus COMMAND AssetLoadingStatusTests)
