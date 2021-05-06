
add_executable(
	JsonDictionaryLoaderTests
	${PROJECT_SOURCE_DIR}/src/main/r3/colon-case/level-data/r3-colonCase-JsonDictionaryLoader.cpp
	JsonDictionaryLoaderTests-main.cpp
)
target_link_libraries(
	JsonDictionaryLoaderTests PRIVATE
	r3-ValidationUtils-lib
	jsoncpp_static
	r3-JsonCppUtils-lib
)
target_include_directories(JsonDictionaryLoaderTests PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_test(NAME JsonDictionaryLoader COMMAND JsonDictionaryLoaderTests)
