
#include <vector>
#include <json/json.h>
#include "r3-tiled-defn.hpp"
#pragma once

namespace r3 {

	namespace tiled {

		namespace JsonPropertyName {

			extern const char* ID;
			extern const char* NAME;
			extern const char* TYPE;
			extern const char* VERSION;
			extern const char* X;
			extern const char* Y;
			extern const char* WIDTH;
			extern const char* HEIGHT;
			extern const char* PROPERTY_LIST;
			extern const char* VALUE;

			namespace Tileset {

				extern const char* COLUMNS;
				extern const char* TILE_COUNT;
				extern const char* TILE_WIDTH;
				extern const char* TILE_HEIGHT;
				extern const char* MARGIN;
				extern const char* SPACING;
				extern const char* IMAGE_PATH;
				extern const char* IMAGE_WIDTH;
				extern const char* IMAGE_HEIGHT;
				extern const char* TILE_LIST;

			}

		}

		namespace JsonPropertyValue {

			namespace FileTypeValue {

				extern const char* TILESET;
				extern const char* MAP;

			}

			namespace CustomPropertyTypeValue {

				extern const char* BOOLEAN;
				extern const char* COLOR;
				extern const char* FLOAT;
				extern const char* FILE;
				extern const char* INTEGER;
				extern const char* OBJECT;
				extern const char* STRING;

			}

		}

		namespace JsonLoaderUtils {

			bool dimensionValueValid(const Json::Value& jsonValue, const char* propertyName);

		}

		namespace JsonCustomPropertyLoader {

			typedef struct Tiled_ValidationResult {
				bool rootValid = true;
				bool nameValid = true;
				bool typeValid = true;
				bool valueValid = true;

				bool isValid() {
					bool result =
						this->rootValid &&
						this->nameValid &&
						this->typeValid &&
						this->valueValid;
					return result;
				}
			} ValidationResult;

			ValidationResult validate(const Json::Value& jsonValue);

			std::string localizePropertyListError(int index);

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult);

			CustomPropertyDefn convertToDefn(const Json::Value& jsonValue);

		}

		namespace JsonTilesetImageLoader {

			typedef struct Tiled_ValidationResult {
				bool imagePathValid = true;
				bool imageWidthValid = true;
				bool imageHeightValid = true;

				bool isValid() {
					bool result =
						this->imagePathValid &&
						this->imageWidthValid &&
						this->imageHeightValid;
					return result;
				}
			} ValidationResult;

			ValidationResult validate(const Json::Value& jsonValue);

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult);

			TilesetImageDefn convertToDefn(const Json::Value& jsonValue);

		}

		namespace JsonTilesetTileLoader {

			typedef struct Tiled_ValidationResult {
				bool rootValid = true;
				bool idValid = true;
				JsonTilesetImageLoader::ValidationResult imageValidationResult;
				std::vector<JsonCustomPropertyLoader::ValidationResult> propertyValidationResultList;

				bool isValid() {
					bool propertyListValid = true;
					for (auto& currPropertyValidationResult : propertyValidationResultList) {
						propertyListValid = propertyListValid && currPropertyValidationResult.isValid();
					}

					bool result =
						this->rootValid &&
						this->idValid &&
						this->imageValidationResult.isValid() &&
						propertyListValid;
					return result;
				}
			} ValidationResult;

			ValidationResult validate(const Json::Value& jsonValue);

			std::string localizeTileListError(int index);

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult);

			TilesetTileDefn convertToDefn(const Json::Value& jsonValue);

		}

		namespace JsonTilesetLoader {


			typedef struct Tiled_ValidationResult {
				bool versionValid = true;
				bool typeValid = true;
				bool nameValid = true;
				bool columnsValid = true;
				bool tileCountValid = true;
				bool tileWidthValid = true;
				bool tileHeightValid = true;
				bool marginValid = true;
				bool spacingValid = true;

				bool tilesetTypeValid = true;

				JsonTilesetImageLoader::ValidationResult imageValidationResult;
				std::vector<JsonTilesetTileLoader::ValidationResult> tileValidationResultList;
				std::vector<JsonCustomPropertyLoader::ValidationResult> propertyValidationResultList;

				bool isValid() {
					bool tileListValid = true;
					for (auto& currTileValidationResult : tileValidationResultList) {
						tileListValid = tileListValid && currTileValidationResult.isValid();
					}

					bool propertyListValid = true;
					for (auto& currPropertyValidationResult : propertyValidationResultList) {
						propertyListValid = propertyListValid && currPropertyValidationResult.isValid();
					}

					bool result =
						this->versionValid &&
						this->typeValid &&
						this->nameValid &&
						this->columnsValid &&
						this->tileCountValid &&
						this->tileWidthValid &&
						this->tileHeightValid &&
						this->marginValid &&
						this->spacingValid &&
						this->tilesetTypeValid &&
						this->imageValidationResult.isValid() &&
						tileListValid &&
						propertyListValid;
					return result;
				}
			} ValidationResult;

			ValidationResult validate(const Json::Value& jsonValue);

			std::vector<std::string> localizeValidationResult(const ValidationResult& validationResult);

			TilesetDefn convertToDefn(const Json::Value& jsonValue);

		}

	}

}
