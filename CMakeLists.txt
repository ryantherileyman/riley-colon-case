
cmake_minimum_required(VERSION 3.19)

project(ColonCase VERSION 0.1)

add_subdirectory(dependencies/riley-cpp-utils)
add_subdirectory(dependencies/json-cpp)
add_subdirectory(dependencies/riley-json-cpp-utils)
add_subdirectory(dependencies/riley-tiled-json-loader)
add_subdirectory(dependencies/sfml)
add_subdirectory(dependencies/riley-sfml-utils)

add_subdirectory(src/main/r3/colon-case)

enable_testing()
add_subdirectory(src/test/r3/colon-case/level-data)
