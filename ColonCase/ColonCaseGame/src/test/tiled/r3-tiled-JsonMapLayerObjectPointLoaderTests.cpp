
#include "r3-tiled-JsonMapLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapLayerObjectPointLoaderTests {

			Json::Value createValidMapLayerObjectPointJsonValue() {
				Json::Value result;
				result[JsonPropertyName::X] = 20;
				result[JsonPropertyName::Y] = 40.5;
				return result;
			}

			bool testValidate_Valid() {
				Json::Value jsonValue = createValidMapLayerObjectPointJsonValue();

				JsonMapLayerObjectPointLoader::ValidationResult validationResult = JsonMapLayerObjectPointLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidRoot() {
				Json::Value jsonValue = "I'm not an object";

				JsonMapLayerObjectPointLoader::ValidationResult validationResult = JsonMapLayerObjectPointLoader::validate(jsonValue);

				bool result =
					!validationResult.rootValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_MissingX() {
				Json::Value jsonValue = createValidMapLayerObjectPointJsonValue();
				jsonValue.removeMember(JsonPropertyName::X);

				JsonMapLayerObjectPointLoader::ValidationResult validationResult = JsonMapLayerObjectPointLoader::validate(jsonValue);

				bool result =
					!validationResult.xValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_X(const Json::Value& xValue, bool expectedXValid) {
				Json::Value jsonValue = createValidMapLayerObjectPointJsonValue();
				jsonValue[JsonPropertyName::X] = xValue;

				JsonMapLayerObjectPointLoader::ValidationResult validationResult = JsonMapLayerObjectPointLoader::validate(jsonValue);

				bool result = (validationResult.xValid == expectedXValid);
				return result;
			}

			bool testValidate_MissingY() {
				Json::Value jsonValue = createValidMapLayerObjectPointJsonValue();
				jsonValue.removeMember(JsonPropertyName::Y);

				JsonMapLayerObjectPointLoader::ValidationResult validationResult = JsonMapLayerObjectPointLoader::validate(jsonValue);

				bool result =
					!validationResult.yValid &&
					!validationResult.isValid();
				return result;
			}

			bool testValidate_Y(const Json::Value& yValue, bool expectedYValid) {
				Json::Value jsonValue = createValidMapLayerObjectPointJsonValue();
				jsonValue[JsonPropertyName::Y] = yValue;

				JsonMapLayerObjectPointLoader::ValidationResult validationResult = JsonMapLayerObjectPointLoader::validate(jsonValue);

				bool result = (validationResult.yValid == expectedYValid);
				return result;
			}

			bool testLocalizePointListError() {
				std::string errorMessage = JsonMapLayerObjectPointLoader::localizePointListError(3, "polygon");

				bool result = (errorMessage.find("Entry 3 within the \"polygon\" array is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_Valid() {
				JsonMapLayerObjectPointLoader::ValidationResult validationResult;

				std::vector<std::string> errorList = JsonMapLayerObjectPointLoader::localizeValidationResult(validationResult);

				bool result = errorList.empty();
				return result;
			}

			bool testLocalizeValidationResult_XInvalid() {
				JsonMapLayerObjectPointLoader::ValidationResult validationResult;
				validationResult.xValid = false;

				std::vector<std::string> errorList = JsonMapLayerObjectPointLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"x\" value is invalid") != std::string::npos);
				return result;
			}

			bool testLocalizeValidationResult_YInvalid() {
				JsonMapLayerObjectPointLoader::ValidationResult validationResult;
				validationResult.yValid = false;

				std::vector<std::string> errorList = JsonMapLayerObjectPointLoader::localizeValidationResult(validationResult);

				bool result =
					(errorList.size() == 1) &&
					(errorList.at(0).find("The \"y\" value is invalid") != std::string::npos);
				return result;
			}

			bool testConvertToDefn() {
				Json::Value jsonValue = createValidMapLayerObjectPointJsonValue();

				MapLayerObjectPointDefn defn = JsonMapLayerObjectPointLoader::convertToDefn(jsonValue);

				bool result =
					(defn.x == jsonValue[JsonPropertyName::X].asDouble()) &&
					(defn.y == jsonValue[JsonPropertyName::Y].asDouble());
				return result;
			}

		}

	}

}
