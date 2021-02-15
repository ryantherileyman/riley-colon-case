
#pragma once

namespace r3 {

	namespace colonCase {

		namespace GameMapTests {

			bool testGetLayerCount();
			bool testGetLayerType();
			bool testGetTileIdPtr_InvalidLayerType();
			bool testGetTileIdPtr_InvalidPosition();
			bool testGetTileIdPtr();
			bool testGetTileImageFilename();
			bool testGetTileTextureRect();
			bool testGetSpriteRenderDetailsList_InvalidLayerType();
			bool testGetSpriteRenderDetailsList_None();
			bool testGetSpriteRenderDetailsList_Partial();
			bool testGetPositionOccupied_InvalidPosition();
			bool testGetPositionOccupied_NotOccupied();
			bool testGetPositionOccupied_Occupied();

		}

	}

}
