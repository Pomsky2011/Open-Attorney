#include "texture_loader.h"
#include "appdata.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filename) {
    std::string texturePath = appdata::getAssetPath(filename).string();
    
    if (!fs::exists(texturePath)) {
        std::cerr << "Texture file does not exist at path: " << texturePath << std::endl;
        return nullptr;
    }

    SDL_Surface* loadedSurface = SDL_LoadBMP(texturePath.c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image at path: " << texturePath << "! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from surface at path: " << texturePath << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    SDL_FreeSurface(loadedSurface);
    return texture;
}

SDL_Texture* loadScaledTexture(SDL_Renderer* renderer, const std::string& filename, int targetWidth, int targetHeight) {
    SDL_Texture* originalTexture = loadTexture(renderer, filename);
    if (originalTexture == nullptr) {
        return nullptr;
    }

    SDL_Texture* scaledTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, targetWidth, targetHeight);
    if (scaledTexture == nullptr) {
        std::cerr << "Unable to create scaled texture! SDL Error: " << SDL_GetError() << std::endl;
        SDL_DestroyTexture(originalTexture);
        return nullptr;
    }

    SDL_SetRenderTarget(renderer, scaledTexture);
    SDL_RenderCopy(renderer, originalTexture, NULL, NULL);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_DestroyTexture(originalTexture);
    return scaledTexture;
}