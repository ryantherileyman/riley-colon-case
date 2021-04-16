
#include <assert.h>
#include <algorithm>
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>

namespace r3 {

	namespace colonCase {

		GameMapLayer::GameMapLayer() {
			this->layerType = GameMapLayerType::UNKNOWN;
		}

		GameMapLayer GameMapLayer::createTileLayer(const GameMapLayerDefn& layerDefn) {
			assert(layerDefn.layerType == GameMapLayerType::TILE);
			assert(layerDefn.renderFlag);
			
			GameMapLayer result;
			result.layerType = GameMapLayerType::TILE;
			result.tileIdList.reserve(layerDefn.tileIdList.size());
			result.tileIdList.insert(std::begin(result.tileIdList), std::begin(layerDefn.tileIdList), std::end(layerDefn.tileIdList));

			return result;
		}

		GameMapLayer GameMapLayer::createSpriteLayer(const GameMapLayerDefn& layerDefn) {
			assert(layerDefn.layerType == GameMapLayerType::SPRITE);
			assert(layerDefn.renderFlag);

			GameMapLayer result;
			result.layerType = GameMapLayerType::SPRITE;
			result.spriteList.reserve(layerDefn.spriteDefnList.size());
			for (const auto& currSourceDefn : layerDefn.spriteDefnList) {
				result.spriteList.push_back(GameMapSprite(currSourceDefn));
			}

			return result;
		}

		const GameMapLayerType GameMapLayer::getLayerType() const {
			return this->layerType;
		}

		const int* GameMapLayer::getTileIdPtr() const {
			const int* result = this->tileIdList.data();
			return result;
		}

		const std::vector<GameMapSprite>& GameMapLayer::getSpriteList() const {
			return this->spriteList;
		}

	}

}
