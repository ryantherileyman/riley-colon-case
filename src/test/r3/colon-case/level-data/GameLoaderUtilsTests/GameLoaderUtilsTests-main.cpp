
#include <assert.h>
#include <filesystem>
#include <iostream>
#include <r3/colon-case/level-data/r3-colonCase-JsonGameLoader.hpp>

using namespace r3::colonCase;

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

int main() {
	assert(testIsValidPath("test-campaign", "some-file.json", true));
	assert(testIsValidPath("Test-Campaign_0", "some-file.json", true));
	assert(testIsValidPath("../test-campaign", "some-file.json", false));
	assert(testIsValidPath("test-campaign", "../some-file.json", false));

	assert(testBuildFullPath("test-campaign", "some-file.json", "resources/campaigns/test-campaign/some-file.json"));
	assert(testBuildFullPath("test-campaign", "../some-file.json", "resources/campaigns/some-file.json"));
	assert(testBuildFullPath("test-campaign", "../../../../some-file.json", "../some-file.json"));

	assert(testResolveRelativeFilePath("maps/mymap.json", "mytileset.json", "maps/mytileset.json"));
	assert(testResolveRelativeFilePath("maps/mymap.json", "../tilesets/mytileset.json", "tilesets/mytileset.json"));

	assert(testLocalizeInvalidPathError("test-campaign", "../some-file.json"));

	std::cout << "All tests passed!\n";
	return 0;
}
