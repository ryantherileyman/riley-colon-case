
#include <chrono>
#include <thread>
#include <SFML/Graphics.hpp>
#include "r3-colonCase-AssetManagerTests.hpp"
#include "../../main/level-data/r3-colonCase-AssetManager.hpp"

namespace r3 {

	namespace colonCase {

		namespace AssetManagerTests {

			bool testGetMapStatus_LoadingNotInitiated() {
				AssetManager assetManager;
				assetManager.setCampaignFolder("good-campaign");

				AssetLoadingStatus status = assetManager.getMapStatus("levels/valid_map.json");

				bool result = (status.completionStatus == AssetLoadingCompletionStatus::NON_EXISTENT);
				return result;
			}

			bool testGetMapStatus_LoadingInitiated() {
				AssetManager assetManager;
				assetManager.setCampaignFolder("good-campaign");
				assetManager.loadMapAsync("levels/valid_map.json");

				AssetLoadingStatus immediateStatus = assetManager.getMapStatus("levels/valid_map.json");
				bool immediateResult = (immediateStatus.completionStatus != AssetLoadingCompletionStatus::COMPLETE);

				bool completeFlag = false;
				while (!completeFlag) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					AssetLoadingStatus waitedStatus = assetManager.getMapStatus("levels/valid_map.json");
					completeFlag = (waitedStatus.completionStatus == AssetLoadingCompletionStatus::COMPLETE);

					if (waitedStatus.completionStatus == AssetLoadingCompletionStatus::FAILED) {
						return false;
					}
				}

				AssetLoadingStatus completedStatus = assetManager.getMapStatus("levels/valid_map.json");
				bool completedResult =
					(completedStatus.loadedCount == 4) &&
					(lroundf(completedStatus.getLoadedPct()) == 100);

				GameMap& gameMap = assetManager.getMap("levels/valid_map.json");
				sf::Texture& tilesetTexture = assetManager.getTexture(gameMap.getTileImageFilename(3));

				bool result =
					immediateResult &&
					completedResult &&
					(gameMap.getLayerCount() == 2) &&
					(tilesetTexture.getSize().x == 21);
				return result;
			}

			bool testGetMapStatus_ErrorLoadingMap() {
				AssetManager assetManager;
				assetManager.setCampaignFolder("good-campaign");
				assetManager.loadMapAsync("levels/non_existent_map.json");

				bool failedFlag = false;
				while (!failedFlag) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					AssetLoadingStatus waitedStatus = assetManager.getMapStatus("levels/non_existent_map.json");
					failedFlag = (waitedStatus.completionStatus == AssetLoadingCompletionStatus::FAILED);

					if (waitedStatus.completionStatus == AssetLoadingCompletionStatus::COMPLETE) {
						return false;
					}
				}

				return true;
			}

			bool testGetMapStatus_ErrorLoadingTexture() {
				AssetManager assetManager;
				assetManager.setCampaignFolder("bad-campaign");
				assetManager.loadMapAsync("levels/invalid_map.json");

				bool failedFlag = false;
				while (!failedFlag) {
					std::this_thread::sleep_for(std::chrono::milliseconds(1));

					AssetLoadingStatus waitedStatus = assetManager.getMapStatus("levels/invalid_map.json");
					failedFlag = (waitedStatus.completionStatus == AssetLoadingCompletionStatus::FAILED);

					if (waitedStatus.completionStatus == AssetLoadingCompletionStatus::COMPLETE) {
						return false;
					}
				}

				return true;
			}

			bool testDestructor_WaitsIfLoadingIncomplete() {
				{
					AssetManager assetManager;
					assetManager.setCampaignFolder("good-campaign");
					assetManager.loadMapAsync("levels/valid_map.json");
				}

				std::this_thread::sleep_for(std::chrono::milliseconds(1));

				return true;
			}

		}

	}

}
