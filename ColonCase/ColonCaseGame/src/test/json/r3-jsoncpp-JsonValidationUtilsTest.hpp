
#include <json/json.h>
#include "../../main/validation/r3-validation-utils.hpp"

using namespace r3::validation;

namespace r3 {

	namespace JsonValidationUtilsTests {

		bool testRequiredString(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);
		bool testOptionalString(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);

		bool testRequiredBool(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);

		bool testRequiredInt(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);
		bool testIntInRange(const Json::Value& jsonValue, const char* propertyName, const IntRange& range, bool expectedResult);

		bool testRequiredFloat(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);

		bool testRequiredObject(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);

		bool testRequiredArray(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);
		bool testOptionalArray(const Json::Value& jsonValue, const char* propertyName, bool expectedResult);

	}

}
