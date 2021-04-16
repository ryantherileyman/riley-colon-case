
#include <assert.h>
#include <iostream>
#include <r3/colon-case/level-data/r3-colonCase-AssetManager.hpp>

using namespace r3::colonCase;

bool testConstructor() {
	AssetLoadingTracker assetLoadingTracker;

	AssetLoadingStatus status = assetLoadingTracker.getStatus();

	bool result =
		(status.completionStatus == AssetLoadingCompletionStatus::PENDING) &&
		(status.loadedCount == 0) &&
		(status.totalCount == 0) &&
		(status.currentResourceId.empty());
	return result;
}

bool testMarkAsComplete() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.markAsComplete();

	AssetLoadingStatus status = assetLoadingTracker.getStatus();

	bool result = (status.completionStatus == AssetLoadingCompletionStatus::COMPLETE);
	return result;
}

bool testMarkAsFailed() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.markAsFailed();

	AssetLoadingStatus status = assetLoadingTracker.getStatus();

	bool result = (status.completionStatus == AssetLoadingCompletionStatus::FAILED);
	return result;
}

bool testAddResourceIdToLoad_NewResourceId() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.addResourceIdToLoad("new_resource");

	AssetLoadingStatus status = assetLoadingTracker.getStatus();

	bool result =
		(status.completionStatus == AssetLoadingCompletionStatus::LOADING) &&
		(status.totalCount == 1);
	return result;
}

bool testAddResourceIdToLoad_ExistingResourceId() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.addResourceIdToLoad("existing_resource");
	assetLoadingTracker.addResourceIdToLoad("existing_resource");

	AssetLoadingStatus status = assetLoadingTracker.getStatus();

	bool result =
		(status.completionStatus == AssetLoadingCompletionStatus::LOADING) &&
		(status.totalCount == 1);
	return result;
}

bool testMarkResourceIdLoaded_NotTracked() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.addResourceIdToLoad("track_something_else");

	try {
		assetLoadingTracker.markResourceIdLoaded("not_yet_tracked");
		return false;
	}
	catch (std::logic_error) {
		return true;
	}
}

bool testMarkResourceIdLoaded_Tracked() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.addResourceIdToLoad("being_tracked");
	assetLoadingTracker.markResourceIdLoaded("being_tracked");

	AssetLoadingStatus status = assetLoadingTracker.getStatus();

	bool result =
		(status.loadedCount == 1) &&
		(status.totalCount == 1);
	return result;
}

bool testSetCurrentResourceId_NotTracked() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.addResourceIdToLoad("track_something_else");

	try {
		assetLoadingTracker.setCurrentResourceId("not_yet_tracked");
		return false;
	}
	catch (std::logic_error) {
		return true;
	}
}

bool testSetCurrentResourceId_Tracked() {
	AssetLoadingTracker assetLoadingTracker;
	assetLoadingTracker.addResourceIdToLoad("being_tracked");
	assetLoadingTracker.setCurrentResourceId("being_tracked");

	AssetLoadingStatus status = assetLoadingTracker.getStatus();

	bool result = (status.currentResourceId.compare("being_tracked") == 0);
	return result;
}

int main() {
	assert(testConstructor());

	assert(testMarkAsComplete());
	assert(testMarkAsFailed());

	assert(testAddResourceIdToLoad_NewResourceId());
	assert(testAddResourceIdToLoad_ExistingResourceId());

	assert(testMarkResourceIdLoaded_NotTracked());
	assert(testMarkResourceIdLoaded_Tracked());

	assert(testSetCurrentResourceId_NotTracked());
	assert(testSetCurrentResourceId_Tracked());

	std::cout << "All tests passed!\n";
	return 0;
}
