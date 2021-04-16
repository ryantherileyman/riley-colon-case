
include(FetchContent)

set(RILEY_CPP_UTILS_WITH_TESTS OFF)
FetchContent_Declare(
	RileyCppUtils
	GIT_REPOSITORY https://github.com/ryantherileyman/riley-cpp-utils.git
	GIT_TAG 1.1.0
)
FetchContent_MakeAvailable(RileyCppUtils)
