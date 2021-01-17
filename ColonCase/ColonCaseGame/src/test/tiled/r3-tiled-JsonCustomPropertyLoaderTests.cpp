
#include <json/json.h>
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"
#include "r3-tiled-JsonCustomPropertyLoaderTests.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonCustomPropertyLoaderTests {

			Json::Value createValidJsonValue() {
				Json::Value result;
				result[JsonPropertyName::NAME] = "someProperty";
				result[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
				result[JsonPropertyName::VALUE] = "testStringValue";
				return result;
			}

			bool testValidateCustomProperty_Valid() {
				Json::Value jsonValue = createValidJsonValue();

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidateCustomProperty_InvalidRoot() {
				Json::Value jsonValue = "must be an object";

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result =
					!validationResult.rootValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidateCustomProperty_MissingName() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue.removeMember(JsonPropertyName::NAME);

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result =
					!validationResult.nameValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidateCustomProperty_InvalidName() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::NAME] = 3;

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result =
					!validationResult.nameValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidateCustomProperty_MissingType() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue.removeMember(JsonPropertyName::TYPE);

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result =
					!validationResult.typeValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidateCustomProperty_Type(const Json::Value& typeValue, bool expectedTypeValid) {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = typeValue;

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result = (validationResult.typeValid == expectedTypeValid);
				return result;
			}

			bool testValidateCustomProperty_MissingValue() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue.removeMember(JsonPropertyName::VALUE);

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result =
					!validationResult.valueValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidateCustomProperty_Value(const Json::Value& typeValue, const Json::Value& value, bool expectedValueValid) {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = typeValue;
				jsonValue[JsonPropertyName::VALUE] = value;

				JsonCustomPropertyLoader::LoadCustomPropertyValidationResult validationResult = JsonCustomPropertyLoader::validateCustomProperty(jsonValue);

				bool result = (validationResult.valueValid == expectedValueValid);
				return result;
			}

			bool testConvertToCustomPropertyDefn_Boolean() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::BOOLEAN;
				jsonValue[JsonPropertyName::VALUE] = true;

				CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToCustomPropertyDefn(jsonValue);

				bool result =
					(defn.name.compare("someProperty") == 0) &&
					(defn.type == CustomPropertyType::BOOLEAN) &&
					(defn.boolValue);
				return result;
			}

			bool testConvertToCustomPropertyDefn_Color() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::COLOR;
				jsonValue[JsonPropertyName::VALUE] = "#ffc06060";

				CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToCustomPropertyDefn(jsonValue);

				bool result =
					(defn.name.compare("someProperty") == 0) &&
					(defn.type == CustomPropertyType::COLOR) &&
					(defn.stringValue.compare("#ffc06060") == 0);
				return result;
			}

			bool testConvertToCustomPropertyDefn_Float() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::FLOAT;
				jsonValue[JsonPropertyName::VALUE] = 3.6;

				CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToCustomPropertyDefn(jsonValue);

				bool result =
					(defn.name.compare("someProperty") == 0) &&
					(defn.type == CustomPropertyType::FLOAT) &&
					(defn.decimalValue == jsonValue[JsonPropertyName::VALUE].asFloat());
				return result;
			}

			bool testConvertToCustomPropertyDefn_File() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::FILE;
				jsonValue[JsonPropertyName::VALUE] = "../path/image.png";

				CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToCustomPropertyDefn(jsonValue);

				bool result =
					(defn.name.compare("someProperty") == 0) &&
					(defn.type == CustomPropertyType::FILE) &&
					(defn.stringValue.compare("../path/image.png") == 0);
				return result;
			}

			bool testConvertToCustomPropertyDefn_Integer() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::INTEGER;
				jsonValue[JsonPropertyName::VALUE] = 3;

				CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToCustomPropertyDefn(jsonValue);

				bool result =
					(defn.name.compare("someProperty") == 0) &&
					(defn.type == CustomPropertyType::INTEGER) &&
					(defn.intValue == 3);
				return result;
			}

			bool testConvertToCustomPropertyDefn_Object() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::OBJECT;
				jsonValue[JsonPropertyName::VALUE] = 3;

				CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToCustomPropertyDefn(jsonValue);

				bool result =
					(defn.name.compare("someProperty") == 0) &&
					(defn.type == CustomPropertyType::OBJECT) &&
					(defn.intValue == 3);
				return result;
			}

			bool testConvertToCustomPropertyDefn_String() {
				Json::Value jsonValue = createValidJsonValue();
				jsonValue[JsonPropertyName::TYPE] = JsonPropertyValue::CustomPropertyTypeValue::STRING;
				jsonValue[JsonPropertyName::VALUE] = "some value";

				CustomPropertyDefn defn = JsonCustomPropertyLoader::convertToCustomPropertyDefn(jsonValue);

				bool result =
					(defn.name.compare("someProperty") == 0) &&
					(defn.type == CustomPropertyType::STRING) &&
					(defn.stringValue.compare("some value") == 0);
				return result;
			}

		}

	}

}
