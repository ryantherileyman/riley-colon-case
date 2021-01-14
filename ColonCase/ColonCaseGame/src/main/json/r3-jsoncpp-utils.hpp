
#include "json/json.h"
#pragma once

namespace r3 {

	namespace JsonValidationUtils {

		bool requiredString(const Json::Value& jsonValue, const char* propertyName);
		bool optionalString(const Json::Value& jsonValue, const char* propertyName);

		bool requiredBool(const Json::Value& jsonValue, const char* propertyName);

		bool requiredInt(const Json::Value& jsonValue, const char* propertyName);

		bool requiredFloat(const Json::Value& jsonValue, const char* propertyName);

		bool requiredObject(const Json::Value& jsonValue, const char* propertyName);

		bool requiredArray(const Json::Value& jsonValue, const char* propertyName);

	}

}
