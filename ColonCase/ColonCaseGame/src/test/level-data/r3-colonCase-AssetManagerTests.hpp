
#pragma once

namespace r3 {

	namespace colonCase {

		namespace AssetLoadingStatusTests {

			bool testGetLoadedPct(int loadedCount, int totalCount, float expectedLoadedPct);

		}

		namespace AssetLoadingTrackerTests {

			bool testConstructor();
			bool testMarkAsComplete();
			bool testMarkAsFailed();
			bool testAddResourceIdToLoad_NewResourceId();
			bool testAddResourceIdToLoad_ExistingResourceId();
			bool testMarkResourceIdLoaded_NotTracked();
			bool testMarkResourceIdLoaded_Tracked();
			bool testSetCurrentResourceId_NotTracked();
			bool testSetCurrentResourceId_Tracked();

		}

		namespace AssetManagerTests {

			bool testGetMapStatus_LoadingNotInitiated();
			bool testGetMapStatus_LoadingInitiated();
			bool testGetMapStatus_ErrorLoadingMap();
			bool testGetMapStatus_ErrorLoadingTexture();
			bool testDestructor_WaitsIfLoadingIncomplete();

		}

	}

}
