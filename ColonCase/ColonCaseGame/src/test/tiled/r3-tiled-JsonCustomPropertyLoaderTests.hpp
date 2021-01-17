
#include <json/json.h>
#pragma once

namespace r3 {

	namespace tiled {

		namespace JsonCustomPropertyLoaderTests {

			bool testValidate_Valid();

			bool testValidate_InvalidRoot();

			bool testValidate_MissingName();
			bool testValidate_InvalidName();

			bool testValidate_MissingType();
			bool testValidate_Type(const Json::Value& typeValue, bool expectedTypeValid);

			bool testValidate_MissingValue();
			bool testValidate_Value(const Json::Value& typeValue, const Json::Value& value, bool expectedValueValid);

			bool testLocalizeValidationResult_Valid();
			bool testLocalizeValidationResult_NameInvalid();
			bool testLocalizeValidationResult_TypeInvalid();
			bool testLocalizeValidationResult_ValueInvalid();

			bool testConvertToDefn_Boolean();
			bool testConvertToDefn_Color();
			bool testConvertToDefn_Float();
			bool testConvertToDefn_File();
			bool testConvertToDefn_Integer();
			bool testConvertToDefn_Object();
			bool testConvertToDefn_String();

		}

	}

}
