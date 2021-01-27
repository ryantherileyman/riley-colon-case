
#pragma once

namespace r3 {

	namespace colonCase {

		namespace GameLoaderUtilsTests {

			bool testIsValidPath(const char* campaignFolder, const char* filePath, bool expectedResult);

			bool testBuildFullPath(const char* campaignFolder, const char* filePath, const char* expectedFullPath);

			bool testResolveRelativeFilePath(const char* baseFilePath, const char* childFilePath, const char* expectedRelativeFilePath);

			bool testLocalizeInvalidPathError(const char* campaignFolder, const char* filePath);

		}

	}

}
