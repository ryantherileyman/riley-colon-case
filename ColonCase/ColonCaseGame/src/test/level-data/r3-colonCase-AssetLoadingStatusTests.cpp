
#include <math.h>
#include "r3-colonCase-AssetManagerTests.hpp"
#include "../../main/level-data/r3-colonCase-AssetManager.hpp"

namespace r3 {

	namespace colonCase {

		namespace AssetLoadingStatusTests {

			bool testGetLoadedPct(int loadedCount, int totalCount, float expectedLoadedPct) {
				AssetLoadingStatus assetLoadingStatus;
				assetLoadingStatus.completionStatus = AssetLoadingCompletionStatus::LOADING;
				assetLoadingStatus.loadedCount = loadedCount;
				assetLoadingStatus.totalCount = totalCount;

				float actual = assetLoadingStatus.getLoadedPct();

				bool result = (lroundf(actual * 100.0f) == (lroundf(expectedLoadedPct * 100.0f)));
				return result;
			}

		}

	}

}
