#include "texture_loader.h"
#include "appdata.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filename) {
    std::string texturePath = appdata::getAssetPath(filename).string();
    
    if (!fs::exists(texturePath)) {
        throw std::runtime_error("Texture file does not exist at path: " + texturePath);
    }

    SDL_Surface* loadedSurface = SDL_LoadBMP(texturePath.c_str());
    if (loadedSurface == nullptr) {
        throw std::runtime_error("Unable to load image at path: " + texturePath + "! SDL Error: " + SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);

    if (texture == nullptr) {
        throw std::runtime_error("Unable to create texture from surface at path: " + texturePath + "! SDL Error: " + SDL_GetError());
    }

    return texture;
}