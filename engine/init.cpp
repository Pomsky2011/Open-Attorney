#include "init.h"
#include <iostream>

GameState* init(int argc, char* args[]) {
    GameState* state = new GameState();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->window = SDL_CreateWindow("Open Attorney", 
                                     SDL_WINDOWPOS_UNDEFINED, 
                                     SDL_WINDOWPOS_UNDEFINED, 
                                     SCREEN_WIDTH, 
                                     SCREEN_HEIGHT, 
                                     SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (state->window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED);
    if (state->renderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Initialize current window size
    state->currentWidth = SCREEN_WIDTH;
    state->currentHeight = SCREEN_HEIGHT;

    return state;
}

void cleanup(GameState* state) {
    SDL_DestroyTexture(state->spriteTexture);
    SDL_DestroyTexture(state->backgroundTexture);
    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);
    delete state;
    SDL_Quit();
}