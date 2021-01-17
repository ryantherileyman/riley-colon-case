
#include "r3-jsoncpp-JsonValidationUtilsTest.hpp"
#include "../../main/json/r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace JsonValidationUtilsTests {

		bool testRequiredString(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::requiredString(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testOptionalString(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::optionalString(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testRequiredBool(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::requiredBool(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testRequiredInt(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::requiredInt(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testIntInRange(const Json::Value& jsonValue, const char* propertyName, const IntRange& range, bool expectedResult) {
			bool actualResult = JsonValidationUtils::intInRange(jsonValue, propertyName, range);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testRequiredFloat(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::requiredFloat(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testRequiredObject(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::requiredObject(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testRequiredArray(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::requiredArray(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

		bool testOptionalArray(const Json::Value& jsonValue, const char* propertyName, bool expectedResult) {
			bool actualResult = JsonValidationUtils::optionalArray(jsonValue, propertyName);

			bool result = (actualResult == expectedResult);
			return result;
		}

	}

}

