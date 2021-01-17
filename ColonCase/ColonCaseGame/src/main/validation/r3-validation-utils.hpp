
#pragma once

namespace r3 {

	namespace validation {

		class IntRange {

		private:
			bool checkMinFlag = false;
			int min = 0;
			bool checkMaxFlag = false;
			int max = 0;

		public:
			static IntRange createMin(int min);
			static IntRange createMax(int max);
			static IntRange create(int min, int max);

		public:
			bool isInRange(int value) const;

		};

	}

}
