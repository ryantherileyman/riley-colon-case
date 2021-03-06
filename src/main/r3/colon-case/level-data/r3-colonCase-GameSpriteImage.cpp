
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>

namespace r3 {

	namespace colonCase {

		GameSpriteImage::GameSpriteImage() {
			this->imageId = -1;
		}

		GameSpriteImage::GameSpriteImage(int imageId, const GameTileImageDefn& imageDefn) {
			this->imageId = imageId;
			this->filename = imageDefn.filename;
			this->imageSize = imageDefn.imageSize;
		}

		int GameSpriteImage::getImageId() const {
			return this->imageId;
		}

		const std::string& GameSpriteImage::getFilename() const {
			return this->filename;
		}

		const sf::Vector2i& GameSpriteImage::getImageSize() const {
			return this->imageSize;
		}

	}

}
