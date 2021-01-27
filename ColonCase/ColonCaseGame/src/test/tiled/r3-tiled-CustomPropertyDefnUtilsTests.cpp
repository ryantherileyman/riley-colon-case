
#include <stdexcept>
#include <math.h>
#include "r3-tiled-CustomPropertyDefnUtilsTests.hpp"

namespace r3 {

	namespace tiled {

		namespace CustomPropertyDefnUtilsTests {

			CustomPropertyDefn createBoolPropertyDefn() {
				CustomPropertyDefn result;
				result.name = "boolProperty";
				result.type = CustomPropertyType::BOOLEAN;
				result.boolValue = true;
				return result;
			}

			CustomPropertyDefn createIntPropertyDefn() {
				CustomPropertyDefn result;
				result.name = "intProperty";
				result.type = CustomPropertyType::INTEGER;
				result.intValue = 42;
				return result;
			}

			CustomPropertyDefn createFloatPropertyDefn() {
				CustomPropertyDefn result;
				result.name = "floatProperty";
				result.type = CustomPropertyType::FLOAT;
				result.decimalValue = 1.23;
				return result;
			}

			CustomPropertyDefn createStringPropertyDefn() {
				CustomPropertyDefn result;
				result.name = "stringProperty";
				result.type = CustomPropertyType::STRING;
				result.stringValue = "something";
				return result;
			}

			CustomPropertyDefn createColorPropertyDefn() {
				CustomPropertyDefn result;
				result.name = "colorProperty";
				result.type = CustomPropertyType::COLOR;
				result.stringValue = "#ff806040";
				return result;
			}

			CustomPropertyDefn createObjectPropertyDefn() {
				CustomPropertyDefn result;
				result.name = "objectProperty";
				result.type = CustomPropertyType::OBJECT;
				result.intValue = 1;
				return result;
			}

			CustomPropertyDefn createFilePropertyDefn() {
				CustomPropertyDefn result;
				result.name = "fileProperty";
				result.type = CustomPropertyType::FILE;
				result.stringValue = "../file.json";
				return result;
			}

			std::vector<CustomPropertyDefn> createPropertyDefnList() {
				std::vector<CustomPropertyDefn> result;
				result.push_back(createBoolPropertyDefn());
				result.push_back(createIntPropertyDefn());
				result.push_back(createFloatPropertyDefn());
				result.push_back(createStringPropertyDefn());
				result.push_back(createColorPropertyDefn());
				result.push_back(createObjectPropertyDefn());
				result.push_back(createFilePropertyDefn());
				return result;
			}

			bool testFind_Success() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				const CustomPropertyDefn& propertyDefn = CustomPropertyDefnUtils::find(propertyDefnList, "intProperty");
				
				bool result = (propertyDefn.type == CustomPropertyType::INTEGER);
				return result;
			}

			bool testFind_Failure() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::find(propertyDefnList, "missingProperty");
					return false;
				}
				catch ( const std::invalid_argument& ) {
					return true;
				}
			}

			bool testContains_Exists() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				bool result = CustomPropertyDefnUtils::contains(propertyDefnList, "colorProperty");
				return result;
			}

			bool testContains_Missing() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				bool result = !CustomPropertyDefnUtils::contains(propertyDefnList, "notThere");
				return result;
			}

			bool testContainsOfType_TypeMatches() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				bool result = CustomPropertyDefnUtils::containsOfType(propertyDefnList, "stringProperty", CustomPropertyType::STRING);
				return result;
			}

			bool testContainsOfType_TypeMismatch() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				bool result = !CustomPropertyDefnUtils::containsOfType(propertyDefnList, "fileProperty", CustomPropertyType::STRING);
				return result;
			}

			bool testContainsOfType_Missing() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				bool result = !CustomPropertyDefnUtils::containsOfType(propertyDefnList, "nopers", CustomPropertyType::STRING);
				return result;
			}

			bool testGetBoolValue_TypeMatches() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				bool boolValue = CustomPropertyDefnUtils::getBoolValue(propertyDefnList, "boolProperty");
				
				bool result = (boolValue == true);
				return result;
			}

			bool testGetBoolValue_TypeMismatch() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getBoolValue(propertyDefnList, "stringProperty");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

			bool testGetBoolValue_Missing() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getBoolValue(propertyDefnList, "missing");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

			bool testGetIntValue_TypeMatches_Int() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				int intValue = CustomPropertyDefnUtils::getIntValue(propertyDefnList, "intProperty");

				bool result = (intValue == 42);
				return result;
			}

			bool testGetIntValue_TypeMatches_Object() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				int intValue = CustomPropertyDefnUtils::getIntValue(propertyDefnList, "objectProperty");

				bool result = (intValue == 1);
				return result;
			}

			bool testGetIntValue_TypeMismatch() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getIntValue(propertyDefnList, "stringProperty");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

			bool testGetIntValue_Missing() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getIntValue(propertyDefnList, "missing");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

			bool testGetDecimalValue_TypeMatches() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				double decimalValue = CustomPropertyDefnUtils::getDecimalValue(propertyDefnList, "floatProperty");
				long roundedValue = lround(decimalValue * 100);

				bool result = (roundedValue == 123);
				return result;
			}

			bool testGetDecimalValue_TypeMismatch() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getDecimalValue(propertyDefnList, "stringProperty");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

			bool testGetDecimalValue_Missing() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getDecimalValue(propertyDefnList, "missing");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

			bool testGetStringValue_TypeMatches_String() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				const std::string stringValue = CustomPropertyDefnUtils::getStringValue(propertyDefnList, "stringProperty");

				bool result = (stringValue.compare("something") == 0);
				return result;
			}

			bool testGetStringValue_TypeMatches_Color() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				const std::string stringValue = CustomPropertyDefnUtils::getStringValue(propertyDefnList, "colorProperty");

				bool result = (stringValue.compare("#ff806040") == 0);
				return result;
			}

			bool testGetStringValue_TypeMatches_File() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				const std::string stringValue = CustomPropertyDefnUtils::getStringValue(propertyDefnList, "fileProperty");

				bool result = (stringValue.compare("../file.json") == 0);
				return result;
			}

			bool testGetStringValue_TypeMismatch() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getStringValue(propertyDefnList, "boolProperty");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

			bool testGetStringValue_Missing() {
				std::vector<CustomPropertyDefn> propertyDefnList = createPropertyDefnList();

				try {
					CustomPropertyDefnUtils::getStringValue(propertyDefnList, "missing");
					return false;
				}
				catch (const std::invalid_argument&) {
					return true;
				}
			}

		}

	}

}
