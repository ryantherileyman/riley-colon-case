
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <r3/tiled/r3-tiled-defn.hpp>
#include <r3/tiled/r3-tiled-JsonLoader.hpp>
#include <r3/colon-case/level-data/r3-colonCase-levelDefn.hpp>
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

			sf::Color convertToSfmlColor(const std::string& colorString);

		}

		namespace JsonGameMapLoader {

			std::vector<GameTileImageDefn> convertToTileImageDefnList(const tiled::MapTilesetDefn& mapTilesetDefn, const tiled::TilesetDefn& tilesetDefn);

			GameMapSpriteDefn convertToSpriteDefn(const tiled::MapLayerObjectDefn& source);

			GameMapLayerDefn convertToLayerDefn(const tiled::MapLayerDefn& source);

			typedef struct ColonCase_LoadGameMapResult {
				std::vector<std::string> errorList;
				GameMapDefn mapDefn;
			} LoadGameMapResult;

			LoadGameMapResult loadFromFile(const char* campaignFolder, const char* filePath);

		}

	}

}
