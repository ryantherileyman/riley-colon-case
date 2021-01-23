
#include <assert.h>
#include <stdio.h>
#include "r3-validation-test.hpp"

using namespace r3::validation;

int main() {
	assert(IntRangeTests::testIsInRange_MinOnly(0, 1, true));
	assert(IntRangeTests::testIsInRange_MinOnly(0, 0, true));
	assert(IntRangeTests::testIsInRange_MinOnly(0, -1, false));

	assert(IntRangeTests::testIsInRange_MaxOnly(0, -1, true));
	assert(IntRangeTests::testIsInRange_MaxOnly(0, 0, true));
	assert(IntRangeTests::testIsInRange_MaxOnly(0, 1, false));

	assert(IntRangeTests::testIsInRange_MinAndMax(3, 5, 2, false));
	assert(IntRangeTests::testIsInRange_MinAndMax(3, 5, 3, true));
	assert(IntRangeTests::testIsInRange_MinAndMax(3, 5, 5, true));
	assert(IntRangeTests::testIsInRange_MinAndMax(3, 5, 6, false));

	printf("All tests passed!\n");
	return 0;
}
