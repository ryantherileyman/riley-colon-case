
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>

namespace r3 {

	namespace colonCase {

		GameSpriteTile::GameSpriteTile() {
			this->tileId = -1;
			this->imageId = -1;
		}

		GameSpriteTile::GameSpriteTile(int imageId, const GameTileImageDefn& imageDefn) {
			this->tileId = imageDefn.tileId;
			this->imageId = imageId;
			this->textureRect = imageDefn.textureRect;
		}

		int GameSpriteTile::getTileId() const {
			return this->tileId;
		}

		int GameSpriteTile::getImageId() const {
			return this->imageId;
		}

		const sf::IntRect& GameSpriteTile::getTextureRect() const {
			return this->textureRect;
		}

	}

}
