
include(FetchContent)

set(BUILD_SHARED_LIBS ON)
set(JSONCPP_WITH_TESTS OFF)
set(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
FetchContent_Declare(
	JsonCpp
	GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp.git
	GIT_TAG 1.9.4
)
FetchContent_MakeAvailable(JsonCpp)
unset(CMAKE_ARCHIVE_OUTPUT_DIRECTORY CACHE)
unset(CMAKE_LIBRARY_OUTPUT_DIRECTORY CACHE)
unset(CMAKE_PDB_OUTPUT_DIRECTORY CACHE)
unset(CMAKE_RUNTIME_OUTPUT_DIRECTORY CACHE)
