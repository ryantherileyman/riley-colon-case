
#include <r3/colon-case/level-data/r3-colonCase-JsonDictionaryLoader.hpp>

namespace r3 {

	namespace colonCase {

		namespace JsonDictionaryLoader {

			ValidationResult validate(const Json::Value& jsonValue) {
				ValidationResult result;

				result.rootValid = jsonValue.isObject();

				if (result.rootValid) {
					for (const auto& currMemberName : jsonValue.getMemberNames()) {
						bool currMemberValid =
							jsonValue[currMemberName].isString() ||
							jsonValue[currMemberName].isArray();

						if (jsonValue[currMemberName].isArray()) {
							for (const auto& currArrayValue : jsonValue[currMemberName]) {
								currMemberValid = currMemberValid && currArrayValue.isString();
							}
						}

						if (!currMemberValid) {
							result.propertyInvalidList.push_back(currMemberName);
						}
					}
				}

				return result;
			}

			std::unordered_map<std::string, std::vector<std::string>> convertToDictionary(const Json::Value& jsonValue) {
				std::unordered_map<std::string, std::vector<std::string>> result;
				for (const auto& currMemberName : jsonValue.getMemberNames()) {
					std::vector<std::string> currStringList;

					if (jsonValue[currMemberName].isString()) {
						currStringList.push_back(jsonValue[currMemberName].asString());
					}
					else if (jsonValue[currMemberName].isArray()) {
						for (const auto& currArrayValue : jsonValue[currMemberName]) {
							currStringList.push_back(currArrayValue.asString());
						}
					}

					result.insert(std::make_pair(currMemberName, currStringList));
				}
				return result;
			}

		}

	}

}
