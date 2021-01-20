
#include <json/json.h>
#include "../validation/r3-validation-utils.hpp"
#include "../json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonPropertyName {

			const char* ID = "id";
			const char* NAME = "name";
			const char* TYPE = "type";
			const char* VERSION = "version";
			const char* X = "x";
			const char* Y = "y";
			const char* WIDTH = "width";
			const char* HEIGHT = "height";
			const char* PROPERTY_LIST = "properties";
			const char* VALUE = "value";

			namespace Tileset {

				const char* COLUMNS = "columns";
				const char* TILE_COUNT = "tilecount";
				const char* TILE_WIDTH = "tilewidth";
				const char* TILE_HEIGHT = "tileheight";
				const char* MARGIN = "margin";
				const char* SPACING = "spacing";
				const char* IMAGE_PATH = "image";
				const char* IMAGE_WIDTH = "imagewidth";
				const char* IMAGE_HEIGHT = "imageheight";
				const char* TILE_LIST = "tiles";

			}

			namespace Map {

				const char* ORIENTATION = "orientation";
				const char* INFINITE = "infinite";
				const char* LAYER_LIST = "layers";

				const char* DATA = "data";
				const char* OBJECT_LIST = "objects";
				const char* TILESET_LIST = "tilesets";

				const char* POINT_FLAG = "point";
				const char* ELLIPSE_FLAG = "ellipse";
				const char* ROTATION = "rotation";
				const char* POLYLINE = "polyline";
				const char* POLYGON = "polygon";
				const char* TILE_GID = "gid";

			}

		}

		namespace JsonPropertyValue {

			namespace FileTypeValue {

				const char* TILESET = "tileset";
				const char* MAP = "map";

			}

			namespace CustomPropertyTypeValue {

				const char* BOOLEAN = "bool";
				const char* COLOR = "color";
				const char* FLOAT = "float";
				const char* FILE = "file";
				const char* INTEGER = "int";
				const char* OBJECT = "object";
				const char* STRING = "string";

			}

		}

		namespace JsonLoaderUtils {

			bool dimensionValueValid(const Json::Value& jsonValue, const char* propertyName) {
				bool result =
					JsonValidationUtils::requiredInt(jsonValue, propertyName) &&
					JsonValidationUtils::intInRange(jsonValue, propertyName, r3::validation::IntRange::createMin(1));
				return result;
			}

		}

	}

}
