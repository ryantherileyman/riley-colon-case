
#include <vector>
#include <unordered_map>
#include "r3-colonCase-levelDefn.hpp"
#include "../tiled/r3-tiled-defn.hpp"
#include "../tiled/r3-tiled-JsonLoader.hpp"
#pragma once

namespace r3 {

	namespace colonCase {

		namespace LayerPropertyName {

			extern const char* RENDER_FLAG;
			extern const char* COLLISION_FLAG;

		}

		namespace GameLoaderUtils {

			bool isValidPath(const char* campaignFolder, const char* filePath);

			std::string buildFullPath(const char* campaignFolder, const char* filePath);

			std::string resolveRelativeFilePath(const char* baseFilePath, const char* childFilePath);

			std::string localizeInvalidPathError(const char* campaignFolder, const char* filePath);

		}

		namespace JsonGameMapLoader {

			GameMapSpriteDefn convertToSpriteDefn(const tiled::MapLayerObjectDefn& source);

			GameMapLayerDefn convertToLayerDefn(const tiled::MapLayerDefn& source);

			typedef struct ColonCase_LoadTiledMapResult {
				std::vector<std::string> errorList;
				tiled::MapDefn mapDefn;
				std::unordered_map<std::string, tiled::TilesetDefn> tilesetDefnMap;
			} LoadTiledMapResult;

			LoadTiledMapResult loadFromFile(const char* campaignFolder, const char* filePath);

			typedef struct ColonCase_LoadGameMapResult {
				std::vector<std::string> errorList;
				GameMapDefn mapDefn;
			} LoadGameMapResult;

			// TODO LoadGameMapResult altLoadFromFile(const char* campaignFolder, const char* filePath);

			// GameMapDefn convertTiledMapDefn(const LoadTiledMapResult& source);

		}

	}

}
