#ifndef APPDATA_H
#define APPDATA_H

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class appdata {
public:
    static fs::path getDirectory();
    static fs::path getAssetPath(const std::string& assetName);
    static void initializeAssets();
};

#endif // APPDATA_H