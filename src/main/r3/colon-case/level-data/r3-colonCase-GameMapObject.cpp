
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>
#include <r3/sfml/geometry/r3-sfml-Ellipse.hpp>

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

		bool GameMapObject::contains(const sf::Vector2f& point) const {
			bool result = false;

			if (this->shape == GameMapObjectShape::RECTANGLE) {
				result =
					(point.x >= this->position.x) &&
					(point.y >= this->position.y) &&
					(point.x <= (this->position.x + this->size.x)) &&
					(point.y <= (this->position.y + this->size.y));
			}
			else if (this->shape == GameMapObjectShape::ELLIPSE) {
				sf::Vector2f ellipseRadius(this->size.x / 2.0f, this->size.y / 2.0f);
				sf::Vector2f ellipseCenter(this->position.x + ellipseRadius.x, this->position.y + ellipseRadius.y);

				r3::sfml::FloatEllipse ellipseRegion(ellipseCenter, ellipseRadius);
				result = ellipseRegion.contains(point);
			}

			return result;
		}

	}

}
