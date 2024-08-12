#include <SDL.h>
#include <iostream>
#include "engine/init.h"
#include "engine/texture_loader.h"
#include "script/loop.h"
#include "engine/appdata.h"
#include <vector>

SDL_Texture* loadBackgroundTexture(SDL_Renderer* renderer) {
    SDL_Texture* backgroundTexture = loadScaledTexture(renderer, "background.bmp", SCREEN_WIDTH, SCREEN_HEIGHT);
    if (backgroundTexture == nullptr) {
        std::cout << "Background texture not found. Creating a black placeholder." << std::endl;
        backgroundTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 1, 1);
        if (backgroundTexture == nullptr) {
            std::cerr << "Failed to create placeholder texture: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        uint32_t black = 0;
        SDL_UpdateTexture(backgroundTexture, NULL, &black, sizeof(uint32_t));
    }
    return backgroundTexture;
}

SDL_Texture* loadSpriteTexture(SDL_Renderer* renderer) {
    SDL_Texture* spriteTexture = loadTexture(renderer, "sprite.bmp");
    if (spriteTexture == nullptr) {
        std::cout << "Sprite texture not found. Creating a black 32x32 placeholder." << std::endl;
        spriteTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, 32, 32);
        if (spriteTexture == nullptr) {
            std::cerr << "Failed to create placeholder sprite texture: " << SDL_GetError() << std::endl;
            return nullptr;
        }
        std::vector<uint32_t> pixels(32 * 32, 0);  // 32x32 black pixels
        SDL_UpdateTexture(spriteTexture, NULL, pixels.data(), 32 * sizeof(uint32_t));
    }
    return spriteTexture;
}

int main(int argc, char* args[]) {
    try {
        // Initialize AppData and copy assets if necessary
        appdata::initializeAssets();

        GameState* state = init(argc, args);
        if (state == nullptr) {
            throw std::runtime_error("Failed to initialize game state!");
        }

        // Load textures
        state->spriteTexture = loadSpriteTexture(state->renderer);
        if (state->spriteTexture == nullptr) {
            throw std::runtime_error("Failed to load or create sprite texture!");
        }

        state->backgroundTexture = loadBackgroundTexture(state->renderer);
        if (state->backgroundTexture == nullptr) {
            throw std::runtime_error("Failed to load or create background texture!");
        }

        // Get the dimensions of the sprite texture
        int w, h;
        SDL_QueryTexture(state->spriteTexture, NULL, NULL, &w, &h);
        state->spriteRect = {(SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h};

        bool quit = false;
        movement_loop(state, quit);

        cleanup(state);

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}