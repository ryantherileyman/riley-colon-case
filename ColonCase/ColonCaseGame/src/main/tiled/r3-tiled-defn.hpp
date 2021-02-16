
#include <optional>
#include <string>
#include <vector>
#pragma once

namespace r3 {

	namespace tiled {

		typedef enum class Tiled_CustomPropertyType {
			UNKNOWN,
			BOOLEAN,
			INTEGER,
			FLOAT,
			STRING,
			COLOR,
			OBJECT,
			FILE,
		} CustomPropertyType;

		typedef struct Tiled_CustomPropertyDefn {
			std::string name;
			CustomPropertyType type = CustomPropertyType::UNKNOWN;
			bool boolValue = false;
			int intValue = 0;
			double decimalValue = 0.0;
			std::string stringValue;
		} CustomPropertyDefn;

		namespace CustomPropertyDefnUtils {

			const CustomPropertyDefn& find(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName);

			bool contains(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName);
			bool containsOfType(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName, CustomPropertyType type);

			bool getBoolValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName);
			int getIntValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName);
			double getDecimalValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName);
			const std::string& getStringValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName);

		}

		typedef struct Tiled_TilesetImageDefn {
			std::string imagePath;
			int imageWidth = 0;
			int imageHeight = 0;
		} TilesetImageDefn;

		typedef struct Tiled_TilesetTileDefn {
			int id = 0;
			TilesetImageDefn imageDefn;
			std::vector<CustomPropertyDefn> propertyDefnList;
		} TilesetTileDefn;

		typedef enum class Tiled_TilesetType {
			UNKNOWN,
			IMAGE,
			TILE_LIST,
		} TilesetType;

		typedef struct Tiled_TilesetDefn {
			double version = 0.0;
			TilesetType type = TilesetType::UNKNOWN;
			std::string name;
			int columns = 0;
			int tileCount = 0;
			int tileWidth = 0;
			int tileHeight = 0;
			int margin = 0;
			int spacing = 0;
			TilesetImageDefn imageDefn;
			std::vector<TilesetTileDefn> tileDefnList;
			std::vector<CustomPropertyDefn> propertyDefnList;
		} TilesetDefn;

		typedef enum class Tiled_MapOrientationType {
			UNKNOWN,
			ORTHOGONAL,
			ISOMETRIC,
			STAGGERED,
			HEXAGONAL,
		} MapOrientationType;

		typedef enum class Tiled_MapLayerType {
			UNKNOWN,
			TILE,
			OBJECT,
			GROUP,
		} MapLayerType;

		typedef enum class Tiled_MapLayerObjectType {
			UNKNOWN,
			POINT,
			RECTANGLE,
			ELLIPSE,
			POLYLINE,
			POLYGON,
			TILE,
			TEXT,
		} MapLayerObjectType;

		namespace MapLayerObjectTypeUtils {

			bool expectsDimensions(MapLayerObjectType objectType);

		}

		typedef struct Tiled_MapLayerObjectPointDefn {
			double x = 0.0;
			double y = 0.0;
		} MapLayerObjectPointDefn;

		typedef struct Tiled_MapLayerObjectDefn {
			int id = 0;
			MapLayerObjectPointDefn position;
			double rotationDegrees = 0.0;
			double width = 0;
			double height = 0;
			MapLayerObjectType objectType = MapLayerObjectType::UNKNOWN;
			int tileGid = 0;
			std::vector<MapLayerObjectPointDefn> pointDefnList;
			std::string name;
			std::string type;
			std::vector<CustomPropertyDefn> propertyDefnList;
		} MapLayerObjectDefn;

		typedef struct Tiled_MapLayerDefn {
			int id = 0;
			MapLayerType type = MapLayerType::UNKNOWN;
			std::string name;
			int width = 0;
			int height = 0;
			std::vector<int> data;
			std::vector<MapLayerObjectDefn> objectDefnList;
			std::vector<struct Tiled_MapLayerDefn> layerDefnList;
			std::vector<CustomPropertyDefn> propertyDefnList;
		} MapLayerDefn;

		typedef struct Tiled_MapTilesetDefn {
			int firstGid = 0;
			std::string sourcePath;
		} MapTilesetDefn;

		typedef struct Tiled_MapDefn {
			double version = 0.0;
			MapOrientationType orientation = MapOrientationType::UNKNOWN;
			bool infinite = false;
			int width = 0;
			int height = 0;
			int tileWidth = 0;
			int tileHeight = 0;
			std::string backgroundColor;
			std::vector<MapTilesetDefn> tilesetDefnList;
			std::vector<MapLayerDefn> layerDefnList;
			std::vector<CustomPropertyDefn> propertyDefnList;
		} MapDefn;

	}

}
