
#include <assert.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <json/json.h>
#include <r3/colon-case/level-data/r3-colonCase-JsonDictionaryLoader.hpp>

using namespace r3::colonCase;

Json::Value createValidJsonValue() {
	Json::Value result;
	result["singleLine"] = "Test string";
	result["multiLine"] = Json::arrayValue;
	result["multiLine"].append("String 1");
	result["multiLine"].append("String 2");

	return result;
}

bool testValidate_Valid_Empty() {
	Json::Value emptyJsonValue = Json::objectValue;

	JsonDictionaryLoader::ValidationResult validationResult = JsonDictionaryLoader::validate(emptyJsonValue);

	bool result =
		validationResult.isValid() &&
		validationResult.rootValid &&
		validationResult.propertyInvalidList.empty();
	return result;
}

bool testValidate_Valid_NotEmpty() {
	Json::Value dictionaryValue = createValidJsonValue();

	JsonDictionaryLoader::ValidationResult validationResult = JsonDictionaryLoader::validate(dictionaryValue);

	bool result =
		validationResult.isValid() &&
		validationResult.rootValid &&
		validationResult.propertyInvalidList.empty();
	return result;
}

bool testValidate_Invalid_RootNotObject(Json::Value& jsonValue) {
	JsonDictionaryLoader::ValidationResult validationResult = JsonDictionaryLoader::validate(jsonValue);

	bool result =
		!validationResult.isValid() &&
		!validationResult.rootValid &&
		validationResult.propertyInvalidList.empty();
	return result;
}

bool testValidate_Invalid_BadSingleLine(Json::Value& singleJsonValue) {
	Json::Value dictionaryValue = createValidJsonValue();
	dictionaryValue["singleLine"] = singleJsonValue;

	JsonDictionaryLoader::ValidationResult validationResult = JsonDictionaryLoader::validate(dictionaryValue);

	bool result =
		!validationResult.isValid() &&
		validationResult.rootValid &&
		(validationResult.propertyInvalidList.size() == 1) &&
		(validationResult.propertyInvalidList.at(0).compare("singleLine") == 0);
	return result;
}

bool testValidate_Invalid_BadMultiLine(Json::Value& multiJsonValue) {
	Json::Value dictionaryValue = createValidJsonValue();
	dictionaryValue["multiLine"][0] = multiJsonValue;

	JsonDictionaryLoader::ValidationResult validationResult = JsonDictionaryLoader::validate(dictionaryValue);

	bool result =
		!validationResult.isValid() &&
		validationResult.rootValid &&
		(validationResult.propertyInvalidList.size() == 1) &&
		(validationResult.propertyInvalidList.at(0).compare("multiLine") == 0);
	return result;
}

bool testConvertToDictionary_Empty() {
	Json::Value emptyJsonValue = Json::objectValue;

	std::unordered_map<std::string, std::vector<std::string>> dictionary = JsonDictionaryLoader::convertToDictionary(emptyJsonValue);

	bool result = dictionary.empty();
	return result;
}

bool testConvertToDictionary_NotEmpty() {
	Json::Value dictionaryValue = createValidJsonValue();

	std::unordered_map<std::string, std::vector<std::string>> dictionary = JsonDictionaryLoader::convertToDictionary(dictionaryValue);

	bool result =
		(dictionary.size() == 2) &&
		(dictionary.at("singleLine").size() == 1) &&
		(dictionary.at("singleLine").at(0).compare("Test string") == 0) &&
		(dictionary.at("multiLine").size() == 2) &&
		(dictionary.at("multiLine").at(0).compare("String 1") == 0) &&
		(dictionary.at("multiLine").at(1).compare("String 2") == 0);
	return result;
}

int main() {
	Json::Value emptyArrayValue = Json::arrayValue;

	assert(testValidate_Valid_Empty());
	assert(testValidate_Valid_NotEmpty());

	assert(testValidate_Invalid_RootNotObject(Json::Value("string")));
	assert(testValidate_Invalid_RootNotObject(Json::Value(3)));
	assert(testValidate_Invalid_RootNotObject(Json::Value(1.5f)));
	assert(testValidate_Invalid_RootNotObject(emptyArrayValue));

	assert(testValidate_Invalid_BadSingleLine(Json::Value(3)));
	assert(testValidate_Invalid_BadSingleLine(Json::Value(1.5f)));

	assert(testValidate_Invalid_BadMultiLine(Json::Value(3)));
	assert(testValidate_Invalid_BadMultiLine(Json::Value(1.5f)));
	assert(testValidate_Invalid_BadMultiLine(emptyArrayValue));

	assert(testConvertToDictionary_Empty());
	assert(testConvertToDictionary_NotEmpty());

	std::cout << "All tests passed!\n";
	return 0;
}
