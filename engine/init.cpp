#include "init.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

GameState* init(int argc, char* args[], const fs::path& executableDir) {
    GameState* state = new GameState();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->window = SDL_CreateWindow("SDL2 Sprite", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state->window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED);
    if (state->renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Load sprite image
    fs::path assetPath = executableDir / "assets" / "sprite.bmp";
    std::cout << "Attempting to load sprite image from: " << assetPath << std::endl;
    SDL_Surface* loadedSurface = SDL_LoadBMP(assetPath.string().c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->spriteTexture = SDL_CreateTextureFromSurface(state->renderer, loadedSurface);
    if (state->spriteTexture == nullptr) {
        std::cerr << "Unable to create texture from surface! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->spriteRect = {(SCREEN_WIDTH - loadedSurface->w) / 2, (SCREEN_HEIGHT - loadedSurface->h) / 2, loadedSurface->w, loadedSurface->h};

    SDL_FreeSurface(loadedSurface);

    return state;
}

void cleanup(GameState* state) {
    SDL_DestroyTexture(state->spriteTexture);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    delete state;
    SDL_Quit();
}