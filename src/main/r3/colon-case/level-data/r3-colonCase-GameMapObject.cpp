
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>

namespace r3 {

	namespace colonCase {

		GameMapObject::GameMapObject(const GameMapObjectDefn& objectDefn) {
			this->shape = objectDefn.shape;
			this->objectType = objectDefn.objectType;
			this->position = objectDefn.position;
			this->size = objectDefn.size;
			this->key = objectDefn.key;
		}

		const GameMapObjectShape GameMapObject::getShape() const {
			return this->shape;
		}

		const GameMapObjectType GameMapObject::getObjectType() const {
			return this->objectType;
		}

		const sf::Vector2f& GameMapObject::getPosition() const {
			return this->position;
		}

		const sf::Vector2f& GameMapObject::getSize() const {
			return this->size;
		}

		const std::string& GameMapObject::getKey() const {
			return this->key;
		}

	}

}
