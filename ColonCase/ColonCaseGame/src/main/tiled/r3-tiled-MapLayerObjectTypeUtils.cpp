
#include "r3-tiled-defn.hpp"

namespace r3 {

	namespace tiled {

		namespace MapLayerObjectTypeUtils {

			bool expectsDimensions(MapLayerObjectType objectType) {
				bool result =
					(objectType == MapLayerObjectType::RECTANGLE) ||
					(objectType == MapLayerObjectType::ELLIPSE);
				return result;
			}

		}

	}

}
