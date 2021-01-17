
#include <assert.h>
#include <sstream>
#include <json/json.h>
#include "../../main/json/r3-jsoncpp-utils.hpp"
#include "r3-jsoncpp-JsonLoaderUtilsTests.hpp"
#include "r3-jsoncpp-JsonValidationUtilsTest.hpp"

Json::Value createJsonValue(const std::string& jsonString) {
	std::stringstream stream(jsonString);

	Json::Value result;
	std::string parseErrors;

	Json::CharReaderBuilder builder = r3::JsonLoaderUtils::createStrictCharReaderBuilder();
	Json::parseFromStream(builder, stream, &result, &parseErrors);

	assert(parseErrors.length() == 0);

	return result;
}

void runJsonLoaderUtilsTests() {
	assert(r3::JsonLoaderUtilsTests::testLoadFromJsonFile_InvalidFile());
	assert(r3::JsonLoaderUtilsTests::testLoadFromJsonFile_ValidFile());
}

void runJsonValidationUtilsTests() {
	std::string jsonString = "{ "
		"\"someBool\": true, "
		"\"someInt\": 5, "
		"\"someFloat\": 2.78, "
		"\"someString\": \"testString\", "
		"\"someObject\": { \"nestedString\": \"testedNest\" }, "
		"\"someArray\": [ 3, 5, 2 ] "
		"}";
	const Json::Value jsonValue = createJsonValue(jsonString);

	assert(r3::JsonValidationUtilsTests::testRequiredString(jsonValue, "someString", true));
	assert(r3::JsonValidationUtilsTests::testRequiredString(jsonValue, "missingString", false));
	assert(r3::JsonValidationUtilsTests::testRequiredString(jsonValue, "nestedString", false));
	assert(r3::JsonValidationUtilsTests::testRequiredString(jsonValue["someObject"], "nestedString", true));
	assert(r3::JsonValidationUtilsTests::testRequiredString(jsonValue, "someBool", false));

	assert(r3::JsonValidationUtilsTests::testOptionalString(jsonValue, "someString", true));
	assert(r3::JsonValidationUtilsTests::testOptionalString(jsonValue, "missingString", true));
	assert(r3::JsonValidationUtilsTests::testOptionalString(jsonValue, "someBool", false));

	assert(r3::JsonValidationUtilsTests::testRequiredBool(jsonValue, "someBool", true));
	assert(r3::JsonValidationUtilsTests::testRequiredBool(jsonValue, "missingBool", false));
	assert(r3::JsonValidationUtilsTests::testRequiredBool(jsonValue, "someString", false));

	assert(r3::JsonValidationUtilsTests::testRequiredInt(jsonValue, "someInt", true));
	assert(r3::JsonValidationUtilsTests::testRequiredInt(jsonValue, "missingInt", false));
	assert(r3::JsonValidationUtilsTests::testRequiredInt(jsonValue, "someBool", false));

	assert(r3::JsonValidationUtilsTests::testIntInRange(jsonValue, "someInt", IntRange::createMax(5), true));
	assert(r3::JsonValidationUtilsTests::testIntInRange(jsonValue, "someInt", IntRange::createMax(4), false));
	assert(r3::JsonValidationUtilsTests::testIntInRange(jsonValue, "missingInt", IntRange::createMax(5), true));

	assert(r3::JsonValidationUtilsTests::testRequiredFloat(jsonValue, "someFloat", true));
	assert(r3::JsonValidationUtilsTests::testRequiredFloat(jsonValue, "missingFloat", false));
	assert(r3::JsonValidationUtilsTests::testRequiredFloat(jsonValue, "someBool", false));

	assert(r3::JsonValidationUtilsTests::testRequiredObject(jsonValue, "someObject", true));
	assert(r3::JsonValidationUtilsTests::testRequiredObject(jsonValue, "missingObject", false));
	assert(r3::JsonValidationUtilsTests::testRequiredObject(jsonValue, "someArray", false));

	assert(r3::JsonValidationUtilsTests::testRequiredArray(jsonValue, "someArray", true));
	assert(r3::JsonValidationUtilsTests::testRequiredArray(jsonValue, "missingArray", false));
	assert(r3::JsonValidationUtilsTests::testRequiredArray(jsonValue, "someObject", false));

	assert(r3::JsonValidationUtilsTests::testOptionalArray(jsonValue, "someArray", true));
	assert(r3::JsonValidationUtilsTests::testOptionalArray(jsonValue, "missingArray", true));
	assert(r3::JsonValidationUtilsTests::testOptionalArray(jsonValue, "someObject", false));
}

int main() {
	runJsonLoaderUtilsTests();
	runJsonValidationUtilsTests();

	printf("All tests passed!\n");
	return 0;
}
