#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <string>
#include <vector>
#include <cstdint>

struct AssetLocator {
    char magic[4];  // 'OAAA'
    uint32_t assetCount;
    uint32_t firstAssetOffset;
};

struct AssetHeader {
    char magic[4];  // 'OAAA'
    uint32_t size;
    char name[32];
};

class AssetManager {
public:
    static void initialize(const std::string& binaryPath = "main");
    static std::vector<char> getAsset(const std::string& assetName);

private:
    static void loadAssetLocator();
    static void loadAssetIndex();

    static std::string s_binaryPath;
    static AssetLocator s_locator;
    static std::vector<AssetHeader> s_assetHeaders;
};

#endif // ASSET_MANAGER_H