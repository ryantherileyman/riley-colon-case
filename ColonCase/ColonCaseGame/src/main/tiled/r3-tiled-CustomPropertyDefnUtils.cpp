
#include <stdexcept>
#include "r3-tiled-defn.hpp"

namespace r3 {

	namespace tiled {

		namespace CustomPropertyDefnUtils {

			const CustomPropertyDefn* findOptional(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName) {
				const CustomPropertyDefn* result = nullptr;

				for (const auto& currPropertyDefn : propertyDefnList) {
					if (propertyName.compare(currPropertyDefn.name) == 0) {
						result = &currPropertyDefn;
						break;
					}
				}

				return result;
			}

			const CustomPropertyDefn& find(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName) {
				const CustomPropertyDefn* propertyDefnPtr = findOptional(propertyDefnList, propertyName);

				if (propertyDefnPtr == nullptr) {
					throw std::invalid_argument("Property " + propertyName + " not found");
				}

				const CustomPropertyDefn& result = *propertyDefnPtr;
				return result;
			}

			bool contains(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName) {
				bool result = (findOptional(propertyDefnList, propertyName) != nullptr);
				return result;
			}

			bool containsOfType(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName, CustomPropertyType type) {
				const CustomPropertyDefn* propertyDefnPtr = findOptional(propertyDefnList, propertyName);

				bool result =
					(propertyDefnPtr != nullptr) &&
					(propertyDefnPtr->type == type);
				return result;
			}

			bool getBoolValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName) {
				const CustomPropertyDefn& propertyDefn = find(propertyDefnList, propertyName);

				if (propertyDefn.type != CustomPropertyType::BOOLEAN) {
					throw std::invalid_argument("Property " + propertyName + " is not a bool type");
				}

				bool result = propertyDefn.boolValue;
				return result;
			}

			int getIntValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName) {
				const CustomPropertyDefn& propertyDefn = find(propertyDefnList, propertyName);

				if (
					(propertyDefn.type != CustomPropertyType::INTEGER) &&
					(propertyDefn.type != CustomPropertyType::OBJECT)
				) {
					throw std::invalid_argument("Property " + propertyName + " is not an int or object type");
				}

				int result = propertyDefn.intValue;
				return result;
			}

			double getDecimalValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName) {
				const CustomPropertyDefn& propertyDefn = find(propertyDefnList, propertyName);

				if (propertyDefn.type != CustomPropertyType::FLOAT) {
					throw std::invalid_argument("Property " + propertyName + " is not an float type");
				}

				double result = propertyDefn.decimalValue;
				return result;
			}

			const std::string& getStringValue(const std::vector<CustomPropertyDefn>& propertyDefnList, const std::string& propertyName) {
				const CustomPropertyDefn& propertyDefn = find(propertyDefnList, propertyName);

				if (
					(propertyDefn.type != CustomPropertyType::STRING) &&
					(propertyDefn.type != CustomPropertyType::COLOR) &&
					(propertyDefn.type != CustomPropertyType::FILE)
				) {
					throw std::invalid_argument("Property " + propertyName + " is not a string, color, or file type");
				}

				const std::string& result = propertyDefn.stringValue;
				return result;
			}

		}

	}

}
