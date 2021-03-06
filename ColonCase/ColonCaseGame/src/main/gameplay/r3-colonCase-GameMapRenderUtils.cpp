
#include <algorithm>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "r3-colonCase-gameplay.hpp"

namespace r3 {

	namespace colonCase {

		namespace GameMapRenderUtils {

			sf::Vector2f resolveViewSize(const sf::Vector2u& targetSize, int pixelsPerTile) {
				sf::Vector2f result;
				result.x = (float)targetSize.x / (float)pixelsPerTile;
				result.y = (float)targetSize.y / (float)pixelsPerTile;
				return result;
			}

			sf::IntRect resolveVisibleTileRect(const sf::View& view, const sf::Vector2i& mapSize) {
				float viewLeft = view.getCenter().x - view.getSize().x * 0.5f;
				float viewTop = view.getCenter().y - view.getSize().y * 0.5f;

				int viewWidth = (int)ceilf(view.getSize().x + 1);
				int viewHeight = (int)ceilf(view.getSize().y + 1);

				sf::IntRect result;

				result.left = std::clamp((int)floorf(viewLeft), 0, mapSize.x - 1);
				result.top = std::clamp((int)floorf(viewTop), 0, mapSize.y - 1);

				int right = std::clamp(result.left + viewWidth, 0, mapSize.x - 1);
				int bottom = std::clamp(result.top + viewHeight, 0, mapSize.y - 1);

				result.width = right - result.left + 1;
				result.height = bottom - result.top + 1;

				return result;
			}

		}

	}

}
