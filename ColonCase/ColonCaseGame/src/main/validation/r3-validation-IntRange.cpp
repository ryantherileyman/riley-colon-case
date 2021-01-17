
#include "r3-validation-utils.hpp"

namespace r3 {

	namespace validation {

		IntRange IntRange::createMin(int min) {
			IntRange result;
			result.checkMinFlag = true;
			result.min = min;
			return result;
		}

		IntRange IntRange::createMax(int max) {
			IntRange result;
			result.checkMaxFlag = true;
			result.max = max;
			return result;
		}

		IntRange IntRange::create(int min, int max) {
			IntRange result;
			result.checkMinFlag = true;
			result.min = min;
			result.checkMaxFlag = true;
			result.max = max;
			return result;
		}

		bool IntRange::isInRange(int value) const {
			bool result = true;

			if (this->checkMinFlag) {
				result = result && (value >= this->min);
			}

			if (this->checkMaxFlag) {
				result = result && (value <= this->max);
			}

			return result;
		}

	}

}
