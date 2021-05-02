
include(FetchContent)

set(RILEY_JSONCPP_UTILS_WITH_TESTS OFF)
FetchContent_Declare(
	RileyJsonCppUtils
	GIT_REPOSITORY https://github.com/ryantherileyman/riley-jsoncpp-utils.git
	GIT_TAG 1.1.0
)
FetchContent_MakeAvailable(RileyJsonCppUtils)
