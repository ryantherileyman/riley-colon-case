
#pragma once

namespace r3 {

	namespace colonCase {

		namespace GameMapTests {

			bool testGetLayerCount();
			bool testGetLayerType();
			bool testGetTileIdPtr_InvalidLayerType();
			bool testGetTileIdPtr_InvalidPosition();
			bool testGetTileIdPtr();
			bool testGetSpriteRenderDetailsList_InvalidLayerType();
			bool testGetSpriteRenderDetailsList_None();
			bool testGetSpriteRenderDetailsList_Partial();

		}

	}

}
