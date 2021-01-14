
#include "r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace JsonValidationUtils {

		bool requiredString(const Json::Value& jsonValue, const char* propertyName) {
			bool result =
				jsonValue.isMember(propertyName) &&
				jsonValue[propertyName].isString();
			return result;
		}

		bool optionalString(const Json::Value& jsonValue, const char* propertyName) {
			bool result = true;
			if (jsonValue.isMember(propertyName)) {
				result = jsonValue[propertyName].isString();
			}
			return result;
		}

		bool requiredBool(const Json::Value& jsonValue, const char* propertyName) {
			bool result =
				jsonValue.isMember(propertyName) &&
				jsonValue[propertyName].isBool();
			return result;
		}

		bool requiredInt(const Json::Value& jsonValue, const char* propertyName) {
			bool result =
				jsonValue.isMember(propertyName) &&
				jsonValue[propertyName].isInt();
			return result;
		}

		bool requiredFloat(const Json::Value& jsonValue, const char* propertyName) {
			bool result =
				jsonValue.isMember(propertyName) &&
				jsonValue[propertyName].isDouble();
			return result;
		}

		bool requiredObject(const Json::Value& jsonValue, const char* propertyName) {
			bool result =
				jsonValue.isMember(propertyName) &&
				jsonValue[propertyName].isObject();
			return result;
		}

		bool requiredArray(const Json::Value& jsonValue, const char* propertyName) {
			bool result =
				jsonValue.isMember(propertyName) &&
				jsonValue[propertyName].isArray();
			return result;
		}

	}

}
