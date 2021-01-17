
#include <json/json.h>
#include "../validation/r3-validation-utils.hpp"
#pragma once

namespace r3 {

	namespace JsonLoaderUtils {

		Json::CharReaderBuilder createStrictCharReaderBuilder();

		typedef struct Json_LoadJsonDataResult {
			Json::Value jsonValue;
			std::string parseErrorString;
		} LoadJsonDataResult;

		LoadJsonDataResult loadFromJsonFile(const char* filePath);

	}

	namespace JsonValidationUtils {

		bool requiredString(const Json::Value& jsonValue, const char* propertyName);
		bool optionalString(const Json::Value& jsonValue, const char* propertyName);

		bool requiredBool(const Json::Value& jsonValue, const char* propertyName);

		bool requiredInt(const Json::Value& jsonValue, const char* propertyName);
		bool intInRange(const Json::Value& jsonValue, const char* propertyName, const r3::validation::IntRange& range);

		bool requiredFloat(const Json::Value& jsonValue, const char* propertyName);

		bool requiredObject(const Json::Value& jsonValue, const char* propertyName);

		bool requiredArray(const Json::Value& jsonValue, const char* propertyName);
		bool optionalArray(const Json::Value& jsonValue, const char* propertyName);

	}

}
