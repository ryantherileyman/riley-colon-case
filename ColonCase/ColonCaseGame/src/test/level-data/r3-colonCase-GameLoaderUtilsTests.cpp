
#include <filesystem>
#include "r3-colonCase-GameLoaderUtilsTest.hpp"
#include "../../main/level-data/r3-colonCase-JsonGameLoader.hpp"

namespace r3 {

	namespace colonCase {

		namespace GameLoaderUtilsTests {

			char PATH_SEPARATOR = std::filesystem::path::preferred_separator;

			bool testIsValidPath(const char* campaignFolder, const char* filePath, bool expectedResult) {
				bool actualResult = GameLoaderUtils::isValidPath(campaignFolder, filePath);

				bool result = (actualResult == expectedResult);
				return result;
			}

			bool testBuildFullPath(const char* campaignFolder, const char* filePath, const char* expectedFullPath) {
				std::string actualFullPath = GameLoaderUtils::buildFullPath(campaignFolder, filePath);

				std::string expected(expectedFullPath);
				std::replace(expected.begin(), expected.end(), '/', PATH_SEPARATOR);

				bool result = (actualFullPath.compare(expected) == 0);
				return result;
			}

			bool testResolveRelativeFilePath(const char* baseFilePath, const char* childFilePath, const char* expectedRelativeFilePath) {
				std::string actualRelativeFilePath = GameLoaderUtils::resolveRelativeFilePath(baseFilePath, childFilePath);

				std::string expected(expectedRelativeFilePath);
				std::replace(expected.begin(), expected.end(), '/', PATH_SEPARATOR);

				bool result = (actualRelativeFilePath.compare(expected) == 0);
				return result;
			}

			bool testLocalizeInvalidPathError(const char* campaignFolder, const char* filePath) {
				std::string actualError = GameLoaderUtils::localizeInvalidPathError(campaignFolder, filePath);

				bool result =
					(actualError.find("The path to file") != std::string::npos) &&
					(actualError.find("is not valid") != std::string::npos);
				return result;
			}

		}

	}

}
