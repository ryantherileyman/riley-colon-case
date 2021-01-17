
#include "../../main/validation/r3-validation-utils.hpp"

namespace r3 {

	namespace validation {

		namespace IntRangeTests {

			bool testIsInRange_MinOnly(int minValue, int value, bool expectedResult) {
				IntRange range = IntRange::createMin(minValue);
				bool actualResult = range.isInRange(value);

				bool result = (actualResult == expectedResult);
				return result;
			}

			bool testIsInRange_MaxOnly(int maxValue, int value, bool expectedResult) {
				IntRange range = IntRange::createMax(maxValue);
				bool actualResult = range.isInRange(value);

				bool result = (actualResult == expectedResult);
				return result;
			}

			bool testIsInRange_MinAndMax(int minValue, int maxValue, int value, bool expectedResult) {
				IntRange range = IntRange::create(minValue, maxValue);
				bool actualResult = range.isInRange(value);

				bool result = (actualResult == expectedResult);
				return result;
			}

		}

	}

}
