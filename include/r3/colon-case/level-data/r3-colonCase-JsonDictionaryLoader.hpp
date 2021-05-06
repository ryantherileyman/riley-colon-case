
#include <string>
#include <unordered_map>
#include <vector>
#include <json/json.h>

namespace r3 {

	namespace colonCase {

		namespace JsonDictionaryLoader {

			typedef struct ColonCase_ValidationResult {
				bool rootValid = true;
				std::vector<std::string> propertyInvalidList;

				bool isValid() {
					bool result =
						rootValid &&
						propertyInvalidList.empty();
					return result;
				}
			} ValidationResult;

			ValidationResult validate(const Json::Value& jsonValue);

			std::unordered_map<std::string, std::vector<std::string>> convertToDictionary(const Json::Value& jsonValue);

		}

	}

}
