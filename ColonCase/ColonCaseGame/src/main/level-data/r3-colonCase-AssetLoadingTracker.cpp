
#include <assert.h>
#include <stdexcept>
#include "r3-colonCase-AssetManager.hpp"

namespace r3 {

	namespace colonCase {

		AssetLoadingTracker::AssetLoadingTracker() {
			this->status = AssetLoadingCompletionStatus::PENDING;
		}

		AssetLoadingStatus AssetLoadingTracker::getStatus() {
			AssetLoadingStatus result;
			result.completionStatus = this->status;
			result.loadedCount = this->calcLoadedCount();
			result.totalCount = this->calcTotalCount();
			result.currentResourceId = this->currentResourceId;
			return result;
		}

		void AssetLoadingTracker::markAsComplete() {
			this->status = AssetLoadingCompletionStatus::COMPLETE;
		}

		void AssetLoadingTracker::markAsFailed() {
			this->status = AssetLoadingCompletionStatus::FAILED;
		}

		void AssetLoadingTracker::addResourceIdToLoad(const std::string& resourceId) {
			if (this->resourceIdLoadedMap.count(resourceId) > 0) {
				throw std::logic_error("Resource already being loaded");
			}

			this->status = AssetLoadingCompletionStatus::LOADING;
			this->resourceIdLoadedMap[resourceId] = false;
		}

		void AssetLoadingTracker::markResourceIdLoaded(const std::string& resourceId) {
			if (this->resourceIdLoadedMap.count(resourceId) == 0) {
				throw std::logic_error("Resource did not yet begin loading");
			}

			this->resourceIdLoadedMap[resourceId] = true;
		}

		void AssetLoadingTracker::setCurrentResourceId(const std::string& resourceId) {
			this->currentResourceId = resourceId;
		}

		int AssetLoadingTracker::calcLoadedCount() {
			int result = 0;
			for (const auto& currResourceIdLoadedPair : this->resourceIdLoadedMap) {
				if (currResourceIdLoadedPair.second) {
					result++;
				}
			}
			return result;
		}

		int AssetLoadingTracker::calcTotalCount() {
			int result = this->resourceIdLoadedMap.size();
			return result;
		}

	}

}
