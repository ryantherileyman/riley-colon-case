
#pragma once

namespace r3 {

	namespace colonCase {

		namespace JsonGameMapLoaderTests {

			bool testConvertToSpriteDefn_Success();
			bool testConvertToSpriteDefn_InvalidType();

			bool testConvertToLayerDefn_Tiles();
			bool testConvertToLayerDefn_Sprites();
			bool testConvertToLayerDefn_RenderFlag();
			bool testConvertToLayerDefn_CollisionFlag();

		}

	}

}
