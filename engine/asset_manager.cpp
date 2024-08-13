#include "asset_manager.h"
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <algorithm>

std::string AssetManager::s_binaryPath;
AssetLocator AssetManager::s_locator;
std::vector<AssetHeader> AssetManager::s_assetHeaders;

void AssetManager::initialize(const std::string& binaryPath) {
    s_binaryPath = binaryPath;
    loadAssetLocator();
    loadAssetIndex();
}

std::vector<char> AssetManager::getAsset(const std::string& assetName) {
    auto it = std::find_if(s_assetHeaders.begin(), s_assetHeaders.end(),
        [&assetName](const AssetHeader& header) {
            return std::strncmp(header.name, assetName.c_str(), sizeof(header.name)) == 0;
        });

    if (it == s_assetHeaders.end()) {
        throw std::runtime_error("Asset not found: " + assetName);
    }

    std::ifstream file(s_binaryPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open binary file");
    }

    file.seekg(-static_cast<int>(sizeof(AssetLocator) + s_locator.firstAssetOffset), std::ios::end);
    file.seekg(std::distance(s_assetHeaders.begin(), it) * sizeof(AssetHeader), std::ios::cur);

    std::vector<char> assetData(it->size);
    file.read(assetData.data(), it->size);

    return assetData;
}

void AssetManager::loadAssetLocator() {
    std::ifstream file(s_binaryPath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open binary file");
    }

    file.seekg(-static_cast<int>(sizeof(AssetLocator)), std::ios::end);
    file.read(reinterpret_cast<char*>(&s_locator), sizeof(AssetLocator));

    if (std::strncmp(s_locator.magic, "OAAA", 4) != 0) {
        throw std::runtime_error("Invalid asset locator");
    }
}

void AssetManager::loadAssetIndex() {
    std::ifstream file(s_binaryPath, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open binary file");
    }

    file.seekg(-static_cast<int>(sizeof(AssetLocator) + s_locator.firstAssetOffset), std::ios::end);

    s_assetHeaders.resize(s_locator.assetCount);
    file.read(reinterpret_cast<char*>(s_assetHeaders.data()), sizeof(AssetHeader) * s_locator.assetCount);

    for (const auto& header : s_assetHeaders) {
        if (std::strncmp(header.magic, "OAAA", 4) != 0) {
            throw std::runtime_error("Invalid asset header");
        }
    }
}