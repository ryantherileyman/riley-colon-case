
#include "../../main/validation/r3-validation-utils.hpp"
#pragma once

namespace r3 {

	namespace validation {

		namespace IntRangeTests {

			bool testIsInRange_MinOnly(int minValue, int value, bool expectedResult);

			bool testIsInRange_MaxOnly(int maxValue, int value, bool expectedResult);

			bool testIsInRange_MinAndMax(int minValue, int maxValue, int value, bool expectedResult);

		}

	}

}
