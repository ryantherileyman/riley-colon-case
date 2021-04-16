
#include <chrono>
#include <future>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <r3/colon-case/level-data/r3-colonCase-AssetManager.hpp>
#include <r3/colon-case/level-data/r3-colonCase-JsonGameLoader.hpp>

namespace r3 {

	namespace colonCase {

		AssetManager::AssetManager() {
			this->queueMutexPtr.reset(new std::mutex());
		}
		AssetManager::~AssetManager() {
			if (this->pendingLoadingFuture.has_value()) {
				this->pendingLoadingFuture.value().get();
			}
		}

		const std::string& AssetManager::getCampaignFolder() const {
			return this->campaignFolder;
		}

		void AssetManager::setCampaignFolder(const std::string& campaignFolder) {
			this->campaignFolder = campaignFolder;
		}

		void AssetManager::loadMapAsync(const std::string& filename) {
			this->clearLoadingFutureIfComplete();

			this->addToMapQueue(filename);

			this->startLoadingFutureIfNotStarted();
		}

		AssetLoadingStatus AssetManager::getMapStatus(const std::string& filename) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			AssetLoadingStatus result;
			if (this->mapLoadingTrackerMap.count(filename) > 0) {
				result = this->mapLoadingTrackerMap.at(filename).getStatus();
			}
			return result;
		}

		GameMap& AssetManager::getMap(const std::string& filename) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			if (this->mapMap.count(filename) > 0) {
				return this->mapMap.at(filename);
			}
			else if (this->mapLoadingTrackerMap.count(filename) > 0) {
				throw std::logic_error("Map is currently being loaded");
			}
			else {
				throw std::logic_error("Map is not being managed");
			}
		}

		sf::Texture& AssetManager::getTexture(const std::string& filename) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			if (this->textureMap.count(filename) > 0) {
				return this->textureMap.at(filename);
			}
			else {
				throw std::logic_error("Texture is not being managed");
			}
		}

		void AssetManager::clearLoadingFutureIfComplete() {
			if (this->pendingLoadingFuture.has_value()) {
				std::future_status status = this->pendingLoadingFuture.value().wait_for(std::chrono::seconds(0));
				if (status == std::future_status::ready) {
					this->pendingLoadingFuture.value().get();
					this->pendingLoadingFuture.reset();
				}
			}
		}

		void AssetManager::startLoadingFutureIfNotStarted() {
			if (!this->pendingLoadingFuture.has_value()) {
				this->pendingLoadingFuture = std::async(&AssetManager::loadAllQueuedMapAssets, this);
			}
		}

		void AssetManager::addToMapQueue(const std::string& filename) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			if (
				(this->mapLoadingTrackerMap.count(filename) > 0) ||
				(this->mapMap.count(filename) > 0)
			) {
				throw std::logic_error("Map is already being managed");
			}

			this->mapLoadingTrackerMap.insert(std::make_pair(filename, AssetLoadingTracker()));
		}

		void AssetManager::loadAllQueuedMapAssets() {
			std::optional<std::string> optionalFilename = this->findNextQueuedMapFilename();
			while (optionalFilename.has_value()) {
				this->loadMapAsset(optionalFilename.value());
				optionalFilename = this->findNextQueuedMapFilename();
			}
		}

		std::optional<std::string> AssetManager::findNextQueuedMapFilename() {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			std::optional<std::string> result;
			for (auto& currMapLoadingTrackerPair : this->mapLoadingTrackerMap) {
				AssetLoadingStatus status = currMapLoadingTrackerPair.second.getStatus();
				if (status.completionStatus == AssetLoadingCompletionStatus::PENDING) {
					result = currMapLoadingTrackerPair.first;
					break;
				}
			}

			return result;
		}

		void AssetManager::loadMapAsset(const std::string& filename) {
			AssetLoadingTracker& mapLoadingTracker = this->mapLoadingTrackerMap.at(filename);

			this->addResourceIdToLoad(mapLoadingTracker, filename);

			bool allMapResourcesLoaded = true;

			this->setCurrentResourceId(mapLoadingTracker, filename);
			JsonGameMapLoader::LoadGameMapResult loadResult = JsonGameMapLoader::loadFromFile(this->campaignFolder.c_str(), filename.c_str());

			if (loadResult.errorList.empty()) {
				std::set<std::string> imageFilenameSet;
				for (const auto& currTileImageDefnPair : loadResult.mapDefn.tileImageDefnMap) {
					const std::string& currImageFilename = currTileImageDefnPair.second.filename;
					this->addResourceIdToLoad(mapLoadingTracker, currImageFilename);
					imageFilenameSet.insert(currImageFilename);
				}

				for (const auto& currImageFilename : imageFilenameSet) {
					this->setCurrentResourceId(mapLoadingTracker, currImageFilename);

					if (this->textureMap.count(currImageFilename) == 0) {
						std::string imagePath = GameLoaderUtils::buildFullPath(this->campaignFolder.c_str(), currImageFilename.c_str());

						this->textureMap.insert(std::make_pair(currImageFilename, sf::Texture()));
						if (this->textureMap.at(currImageFilename).loadFromFile(imagePath)) {
							this->markResourceIdLoaded(mapLoadingTracker, currImageFilename);
						}
						else {
							// TODO probably want to log that this image file failed to load
							allMapResourcesLoaded = false;
						}
					}
					else {
						this->markResourceIdLoaded(mapLoadingTracker, currImageFilename);
					}
				}
			}
			else {
				// TODO probably want to log the errors somewhere...
				allMapResourcesLoaded = false;
			}

			if (allMapResourcesLoaded) {
				this->mapMap.insert(std::make_pair(filename, GameMap(loadResult.mapDefn)));

				this->markResourceIdLoaded(mapLoadingTracker, filename);
				this->markAsComplete(mapLoadingTracker);
			}
			else {
				this->markAsFailed(mapLoadingTracker);
			}
		}

		void AssetManager::markAsComplete(AssetLoadingTracker& tracker) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			tracker.markAsComplete();
		}

		void AssetManager::markAsFailed(AssetLoadingTracker& tracker) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			tracker.markAsFailed();
		}

		void AssetManager::addResourceIdToLoad(AssetLoadingTracker& tracker, const std::string& resourceId) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			tracker.addResourceIdToLoad(resourceId);
		}

		void AssetManager::markResourceIdLoaded(AssetLoadingTracker& tracker, const std::string& resourceId) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			tracker.markResourceIdLoaded(resourceId);
		}

		void AssetManager::setCurrentResourceId(AssetLoadingTracker& tracker, const std::string& resourceId) {
			std::unique_lock<std::mutex> queueLock(*this->queueMutexPtr.get());

			tracker.setCurrentResourceId(resourceId);
		}

	}

}
