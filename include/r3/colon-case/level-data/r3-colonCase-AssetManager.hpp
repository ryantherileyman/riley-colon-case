
#include <future>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>
#pragma once

namespace r3 {

	namespace colonCase {

		typedef enum class ColonCase_AssetLoadingCompletionStatus {
			NON_EXISTENT,
			PENDING,
			LOADING,
			COMPLETE,
			FAILED,
		} AssetLoadingCompletionStatus;

		typedef struct ColonCase_AssetLoadingStatus {
			AssetLoadingCompletionStatus completionStatus = AssetLoadingCompletionStatus::NON_EXISTENT;
			int loadedCount = 0;
			int totalCount = 0;
			std::string currentResourceId;

		public:
			float getLoadedPct() {
				float result = 0;
				if (totalCount > 0) {
					result = 100.0f * ((float)loadedCount / (float)totalCount);
				}
				return result;
			}
		} AssetLoadingStatus;

		class AssetLoadingTracker;
		class AssetManager;

		class AssetLoadingTracker {

		private:
			AssetLoadingCompletionStatus status;
			std::unordered_map<std::string, bool> resourceIdLoadedMap;
			std::string currentResourceId;

		public:
			AssetLoadingTracker();

		public:
			AssetLoadingStatus getStatus();
			void markAsComplete();
			void markAsFailed();
			void addResourceIdToLoad(const std::string& resourceId);
			void markResourceIdLoaded(const std::string& resourceId);
			void setCurrentResourceId(const std::string& resourceId);

		private:
			int calcLoadedCount();
			int calcTotalCount();

		};

		class AssetManager {

		private:
			std::string campaignFolder;

		private:
			std::unique_ptr<std::mutex> queueMutexPtr;
			std::optional<std::future<void>> pendingLoadingFuture;

		private:
			std::unordered_map<std::string, AssetLoadingTracker> mapLoadingTrackerMap;
			std::unordered_map<std::string, GameMap> mapMap;

		private:
			std::unordered_map<std::string, sf::Texture> textureMap;

		public:
			AssetManager();
			~AssetManager();

		public:
			const std::string& getCampaignFolder() const;
			void setCampaignFolder(const std::string& campaignFolder);

		public:
			void loadMapAsync(const std::string& filename);
			AssetLoadingStatus getMapStatus(const std::string& filename);
			GameMap& getMap(const std::string& filename);

		public:
			sf::Texture& getTexture(const std::string& filename);

		private:
			void clearLoadingFutureIfComplete();
			void startLoadingFutureIfNotStarted();

		private:
			void addToMapQueue(const std::string& filename);
			std::optional<std::string> findNextQueuedMapFilename();
			void loadAllQueuedMapAssets();
			void loadMapAsset(const std::string& filename);

		private:
			void markAsComplete(AssetLoadingTracker& tracker);
			void markAsFailed(AssetLoadingTracker& tracker);
			void addResourceIdToLoad(AssetLoadingTracker& tracker, const std::string& resourceId);
			void markResourceIdLoaded(AssetLoadingTracker& tracker, const std::string& resourceId);
			void setCurrentResourceId(AssetLoadingTracker& tracker, const std::string& resourceId);

		};

	}

}
