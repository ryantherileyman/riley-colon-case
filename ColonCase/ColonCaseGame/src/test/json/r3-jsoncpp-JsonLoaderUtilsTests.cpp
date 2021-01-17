
#include "../../main/json/r3-jsoncpp-utils.hpp"
#include "r3-jsoncpp-JsonLoaderUtilsTests.hpp"

namespace r3 {

	namespace JsonLoaderUtilsTests {

		bool testLoadFromJsonFile_InvalidFile() {
			r3::JsonLoaderUtils::LoadJsonDataResult jsonDataResult = JsonLoaderUtils::loadFromJsonFile("resources/invalid.json");
			bool result = (jsonDataResult.parseErrorString.length() > 0);
			return result;
		}

		bool testLoadFromJsonFile_ValidFile() {
			r3::JsonLoaderUtils::LoadJsonDataResult jsonDataResult = JsonLoaderUtils::loadFromJsonFile("resources/valid.json");
			bool result =
				(jsonDataResult.parseErrorString.length() == 0) &&
				!jsonDataResult.jsonValue["weWontGetHere"].asBool();
			return result;
		}

	}

}
