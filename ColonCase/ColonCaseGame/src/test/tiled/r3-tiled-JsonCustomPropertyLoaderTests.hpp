
#include <json/json.h>
#pragma once

namespace r3 {

	namespace tiled {

		namespace JsonCustomPropertyLoaderTests {

			bool testValidateCustomProperty_Valid();

			bool testValidateCustomProperty_InvalidRoot();

			bool testValidateCustomProperty_MissingName();
			bool testValidateCustomProperty_InvalidName();

			bool testValidateCustomProperty_MissingType();
			bool testValidateCustomProperty_Type(const Json::Value& typeValue, bool expectedTypeValid);

			bool testValidateCustomProperty_MissingValue();
			bool testValidateCustomProperty_Value(const Json::Value& typeValue, const Json::Value& value, bool expectedValueValid);

			bool testLocalizeCustomPropertyValidationResult_Valid();
			bool testLocalizeCustomPropertyValidationResult_NameInvalid();
			bool testLocalizeCustomPropertyValidationResult_TypeInvalid();
			bool testLocalizeCustomPropertyValidationResult_ValueInvalid();

			bool testConvertToCustomPropertyDefn_Boolean();
			bool testConvertToCustomPropertyDefn_Color();
			bool testConvertToCustomPropertyDefn_Float();
			bool testConvertToCustomPropertyDefn_File();
			bool testConvertToCustomPropertyDefn_Integer();
			bool testConvertToCustomPropertyDefn_Object();
			bool testConvertToCustomPropertyDefn_String();

		}

	}

}
