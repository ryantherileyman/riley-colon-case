
#include <filesystem>
#include <regex>
#include <r3/colon-case/level-data/r3-colonCase-JsonGameLoader.hpp>

namespace r3 {

	namespace colonCase {

		namespace GameLoaderUtils {

			const char* CAMPAIGN_ROOT = "resources/campaigns";
			std::regex FOLDER_REGEX("[A-Za-z0-9_\\-]*");

			std::filesystem::path resolveCampaignFolderPath(const char* campaignFolder) {
				std::filesystem::path campaignFolderPath(CAMPAIGN_ROOT);
				campaignFolderPath.append(campaignFolder);

				std::filesystem::path result = campaignFolderPath.lexically_normal();
				return result;
			}

			std::string resolveFilePath(const std::filesystem::path& campaignFolderPath, const char* filePath) {
				std::filesystem::path fullPath(campaignFolderPath);
				fullPath.append(filePath);

				std::string result = fullPath.lexically_normal().string();
				return result;
			}

			bool isValidPath(const char* campaignFolder, const char* filePath) {
				std::filesystem::path campaignFolderPath = resolveCampaignFolderPath(campaignFolder);

				std::string fullPathStr = resolveFilePath(campaignFolderPath, filePath);

				bool result =
					std::regex_match(campaignFolder, FOLDER_REGEX) &&
					(fullPathStr.find(campaignFolderPath.string()) == 0);
				return result;
			}

			std::string buildFullPath(const char* campaignFolder, const char* filePath) {
				std::filesystem::path campaignFolderPath = resolveCampaignFolderPath(campaignFolder);

				std::string result = resolveFilePath(campaignFolderPath, filePath);
				return result;
			}

			std::string resolveRelativeFilePath(const char* baseFilePath, const char* childFilePath) {
				std::filesystem::path originalPath(baseFilePath);
				std::filesystem::path relativePath = originalPath
					.parent_path()
					.append(childFilePath)
					.lexically_normal();

				std::string result = relativePath.string();
				return result;
			}

			std::string localizeInvalidPathError(const char* campaignFolder, const char* filePath) {
				std::ostringstream errorStream;
				errorStream << "The path to file \"" << filePath << "\" in campaign folder \"" << campaignFolder << "\" is not valid.";
				errorStream << "  The campaign folder name may only contain standard characters, and the final path must reside within campaign folder.";

				std::string result = errorStream.str();
				return result;
			}

			sf::Color convertToSfmlColor(const std::string& colorString) {
				sf::Color result;

				int nextComponentIndex = 1;
				if (colorString.size() == 9) {
					result.a = (sf::Uint8)std::stoul(colorString.substr(nextComponentIndex, 2), nullptr, 16);
					nextComponentIndex += 2;
				}

				result.r = (sf::Uint8)std::stoul(colorString.substr(nextComponentIndex, 2), nullptr, 16);
				nextComponentIndex += 2;

				result.g = (sf::Uint8)std::stoul(colorString.substr(nextComponentIndex, 2), nullptr, 16);
				nextComponentIndex += 2;

				result.b = (sf::Uint8)std::stoul(colorString.substr(nextComponentIndex, 2), nullptr, 16);

				return result;
			}

		}

	}

}
