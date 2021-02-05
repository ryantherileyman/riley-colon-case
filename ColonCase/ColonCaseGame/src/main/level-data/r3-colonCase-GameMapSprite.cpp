
#include "r3-colonCase-GameMap.hpp"

namespace r3 {

	namespace colonCase {

		GameMapSprite::GameMapSprite(const GameMapSpriteDefn& spriteDefn) {
			this->tileId = spriteDefn.tileId;
			this->position = spriteDefn.position;
			this->size = spriteDefn.size;
		}

		int GameMapSprite::getTileId() const {
			return this->tileId;
		}

		sf::Vector2f GameMapSprite::getPosition() const {
			return this->position;
		}

		sf::Vector2f GameMapSprite::getSize() const {
			return this->size;
		}

	}

}
