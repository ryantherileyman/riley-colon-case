
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

		namespace JsonCustomPropertyLoader {

			typedef struct Tiled_LoadCustomPropertyValidationResult {
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
			} LoadCustomPropertyValidationResult;

			LoadCustomPropertyValidationResult validateCustomProperty(const Json::Value& jsonValue);

			std::vector<std::string> localizeCustomPropertyValidationResult(const LoadCustomPropertyValidationResult& validationResult);

			CustomPropertyDefn convertToCustomPropertyDefn(const Json::Value& jsonValue);

		}

		namespace JsonTilesetLoader {

			typedef struct Tiled_LoadTilesetImageValidationResult {
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
			} LoadTilesetImageValidationResult;

			typedef struct Tiled_LoadTilesetTileValidationResult {
				bool rootValid = true;
				bool idValid = true;
				LoadTilesetImageValidationResult imageValidationResult;
				std::vector<JsonCustomPropertyLoader::LoadCustomPropertyValidationResult> propertyValidationResultList;

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
			} LoadTilesetTileValidationResult;

			typedef struct Tiled_LoadTilesetValidationResult {
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

				LoadTilesetImageValidationResult imageValidationResult;
				std::vector<LoadTilesetTileValidationResult> tileValidationResultList;
				std::vector<JsonCustomPropertyLoader::LoadCustomPropertyValidationResult> propertyValidationResultList;

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
			} LoadTilesetValidationResult;

			LoadTilesetImageValidationResult validateTilesetImage(const Json::Value& jsonValue);

			LoadTilesetTileValidationResult validateTilesetTile(const Json::Value& jsonValue);

			LoadTilesetValidationResult validateTileset(const Json::Value& jsonValue);

			TilesetImageDefn convertToTilesetImageDefn(const Json::Value& jsonValue);

			TilesetTileDefn convertToTilesetTileDefn(const Json::Value& jsonValue);

			TilesetDefn convertToTilesetDefn(const Json::Value& jsonValue);

		}

	}

}
