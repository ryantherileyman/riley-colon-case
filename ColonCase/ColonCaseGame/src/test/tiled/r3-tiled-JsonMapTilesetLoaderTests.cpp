
#include "r3-tiled-JsonMapLoaderTests.hpp"
#include "../../main/tiled/r3-tiled-JsonLoader.hpp"

namespace r3 {

	namespace tiled {

		namespace JsonMapTilesetLoaderTests {

			Json::Value createValidMapTilesetJsonValue() {
				Json::Value result;
				result[JsonPropertyName::Map::FIRST_GID] = 1;
				result[JsonPropertyName::Map::SOURCE_PATH] = "tilesets/floors.json";
				return result;
			}

			bool testValidate_Valid() {
				Json::Value jsonValue = createValidMapTilesetJsonValue();

				JsonMapTilesetLoader::ValidationResult validationResult = JsonMapTilesetLoader::validate(jsonValue);

				bool result = validationResult.isValid();
				return result;
			}

			bool testValidate_InvalidRoot() {
				return false; // TODO
			}

			bool testValidate_MissingFirstGid() {
				return false; // TODO
			}

			bool testValidate_FirstGid(const Json::Value& firstGidValue, bool expectedFirstGidValid) {
				return false; // TODO
			}

			bool testValidate_MissingSourcePath() {
				return false; // TODO
			}

			bool testValidate_SourcePath(const Json::Value& sourcePathValue, bool expectedSourcePathValid) {
				return false; // TODO
			}

			bool testLocalizeTilesetListError() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_Valid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_FirstGidInvalid() {
				return false; // TODO
			}

			bool testLocalizeValidationResult_SourcePathInvalid() {
				return false; // TODO
			}

			bool testConvertToDefn() {
				return false; // TODO
			}

		}

	}

}
