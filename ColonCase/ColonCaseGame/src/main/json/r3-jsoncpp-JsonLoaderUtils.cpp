
#include <fstream>
#include "r3-jsoncpp-utils.hpp"

namespace r3 {

	namespace JsonLoaderUtils {

		Json::CharReaderBuilder createStrictCharReaderBuilder() {
			Json::Value features;
			Json::CharReaderBuilder::strictMode(&features);

			Json::CharReaderBuilder result;
			for (auto currFeature = features.begin(); currFeature != features.end(); ++currFeature) {
				auto key = currFeature.name();
				auto& value = features[key];

				result[key] = value;
			}

			return result;
		}

		LoadJsonDataResult loadFromJsonFile(const char* filePath) {
			Json::CharReaderBuilder readerBuilder = createStrictCharReaderBuilder();

			std::ifstream inputStream(filePath);

			LoadJsonDataResult result;
			Json::parseFromStream(readerBuilder, inputStream, &result.jsonValue, &result.parseErrorString);
			
			return result;
		}

	}

}
