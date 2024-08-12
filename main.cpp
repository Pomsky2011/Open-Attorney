#include <SDL.h>
#include <iostream>
#include "engine/init.h"
#include "engine/texture_loader.h"
#include "script/loop.h"
#include "engine/appdata.h"

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

int main(int argc, char* args[]) {
    try {
        // Initialize AppData and copy assets if necessary
        appdata::initializeAssets();

        GameState* state = init(argc, args);
        if (state == nullptr) {
            throw std::runtime_error("Failed to initialize game state!");
        }

        // Load textures
        state->spriteTexture = loadTexture(state->renderer, "sprite.bmp");
        if (state->spriteTexture == nullptr) {
            throw std::runtime_error("Failed to load sprite texture!");
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