
#include <assert.h>
#include <iostream>
#include <r3/colon-case/level-data/r3-colonCase-AssetManager.hpp>

using namespace r3::colonCase;

bool testGetLoadedPct(int loadedCount, int totalCount, float expectedLoadedPct) {
	AssetLoadingStatus assetLoadingStatus;
	assetLoadingStatus.completionStatus = AssetLoadingCompletionStatus::LOADING;
	assetLoadingStatus.loadedCount = loadedCount;
	assetLoadingStatus.totalCount = totalCount;

	float actual = assetLoadingStatus.getLoadedPct();

	bool result = (lroundf(actual * 100.0f) == (lroundf(expectedLoadedPct * 100.0f)));
	return result;
}

int main() {
	assert(testGetLoadedPct(0, 0, 0.00f));
	assert(testGetLoadedPct(0, 1, 0.00f));
	assert(testGetLoadedPct(1, 1, 100.00f));
	assert(testGetLoadedPct(2, 9, 22.22f));

	std::cout << "All tests passed!\n";
	return 0;
}
