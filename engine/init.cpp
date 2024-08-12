#include "init.h"
#include "texture_loader.h"
#include <iostream>

GameState* init(int argc, char* args[]) {
    GameState* state = new GameState();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->window = SDL_CreateWindow("Open Attorney", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (state->window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED);
    if (state->renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->spriteTexture = loadTexture(state->renderer, "sprite.bmp");
    if (state->spriteTexture == nullptr) {
        return nullptr;
    }

    // Get the dimensions of the texture
    int w, h;
    SDL_QueryTexture(state->spriteTexture, NULL, NULL, &w, &h);
    state->spriteRect = {(SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h};

    return state;
}

void cleanup(GameState* state) {
    SDL_DestroyTexture(state->spriteTexture);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    delete state;
    SDL_Quit();
}