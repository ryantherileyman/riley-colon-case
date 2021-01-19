
#include <json/json.h>
#pragma once

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerObjectPointLoaderTests {

			bool testValidate_Valid();

			bool testValidate_InvalidRoot();

			bool testValidate_MissingX();
			bool testValidate_X(const Json::Value& xValue, bool expectedXValid);

			bool testValidate_MissingY();
			bool testValidate_Y(const Json::Value& yValue, bool expectedYValid);

			bool testLocalizePointListError();

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_XInvalid();
			bool testLocalizeValidationResult_YInvalid();

			bool testConvertToDefn();

		}

	}

}
