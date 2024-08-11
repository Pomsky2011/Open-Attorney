#include "appdata.h"
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

fs::path appdata::getDirectory() {
    fs::path appDataPath;
    
    #ifdef __APPLE__
        if (const char* home = std::getenv("HOME")) {
            appDataPath = fs::path(home) / "Library" / "Application Support" / "OpenAttorney";
        }
    #elif defined(_WIN32)
        if (const char* appData = std::getenv("APPDATA")) {
            appDataPath = fs::path(appData) / "OpenAttorney";
        }
    #else
        if (const char* home = std::getenv("HOME")) {
            appDataPath = fs::path(home) / ".config" / "openattorney";
        }
    #endif

    if (appDataPath.empty()) {
        throw std::runtime_error("Could not determine app data directory");
    }

    fs::create_directories(appDataPath);
    return appDataPath;
}

fs::path appdata::getAssetPath(const std::string& assetName) {
    return getDirectory() / "assets" / assetName;
}

void appdata::initializeAssets() {
    fs::path assetDir = getDirectory() / "assets";
    fs::create_directories(assetDir);

    // List of assets to initialize
    std::vector<std::string> assets = {"sprite.bmp"};

    for (const auto& asset : assets) {
        fs::path assetPath = assetDir / asset;
        if (!fs::exists(assetPath)) {
            // Here you would typically copy the asset from your game's installation directory
            // For this example, we'll just create an empty file
            std::ofstream(assetPath.string()).close();
            std::cout << "Created placeholder for asset: " << asset << std::endl;
        }
    }
}