
include(FetchContent)

set(RILEY_TILED_JSON_LOADER_WITH_TESTS OFF)
FetchContent_Declare(
	RileyTiledJsonLoader
	GIT_REPOSITORY https://github.com/ryantherileyman/riley-tiled-json-loader.git
	GIT_TAG 0.2.0
)
FetchContent_MakeAvailable(RileyTiledJsonLoader)
