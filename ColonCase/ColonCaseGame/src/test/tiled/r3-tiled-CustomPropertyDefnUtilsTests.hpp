
#include "../../main/tiled/r3-tiled-defn.hpp"
#pragma once

namespace r3 {

	namespace tiled {

		namespace CustomPropertyDefnUtilsTests {

			bool testFind_Success();
			bool testFind_Failure();

			bool testContains_Exists();
			bool testContains_Missing();

			bool testContainsOfType_TypeMatches();
			bool testContainsOfType_TypeMismatch();
			bool testContainsOfType_Missing();

			bool testGetBoolValue_TypeMatches();
			bool testGetBoolValue_TypeMismatch();
			bool testGetBoolValue_Missing();

			bool testGetIntValue_TypeMatches_Int();
			bool testGetIntValue_TypeMatches_Object();
			bool testGetIntValue_TypeMismatch();
			bool testGetIntValue_Missing();

			bool testGetDecimalValue_TypeMatches();
			bool testGetDecimalValue_TypeMismatch();
			bool testGetDecimalValue_Missing();

			bool testGetStringValue_TypeMatches_String();
			bool testGetStringValue_TypeMatches_Color();
			bool testGetStringValue_TypeMatches_File();
			bool testGetStringValue_TypeMismatch();
			bool testGetStringValue_Missing();

		}

	}

}
