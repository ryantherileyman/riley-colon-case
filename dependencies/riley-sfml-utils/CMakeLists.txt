
include(FetchContent)

set(RILEY_SFML_UTILS_WITH_EXAMPLES OFF)
set(RILEY_SFML_UTILS_WITH_TESTS OFF)
FetchContent_Declare(
	RileySfmlUtils
	GIT_REPOSITORY https://github.com/ryantherileyman/riley-sfml-utils.git
	GIT_TAG 1.1.0
)
FetchContent_MakeAvailable(RileySfmlUtils)
