#include "init.h"
#include "texture_loader.h"
#include <iostream>
#include <stdexcept>

GameState* init(int argc, char* args[]) {
    try {
        GameState* state = new GameState();

        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
        }

        state->window = SDL_CreateWindow("Open Attorney", 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         SDL_WINDOWPOS_UNDEFINED, 
                                         SCREEN_WIDTH, 
                                         SCREEN_HEIGHT, 
                                         SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        if (state->window == nullptr) {
            throw std::runtime_error("Window could not be created! SDL_Error: " + std::string(SDL_GetError()));
        }

        state->renderer = SDL_CreateRenderer(state->window, -1, SDL_RENDERER_ACCELERATED);
        if (state->renderer == nullptr) {
            throw std::runtime_error("Renderer could not be created! SDL Error: " + std::string(SDL_GetError()));
        }

        state->spriteTexture = loadTexture(state->renderer, "sprite.bmp");
        if (state->spriteTexture == nullptr) {
            throw std::runtime_error("Failed to load sprite texture!");
        }

        // Get the dimensions of the texture
        int w, h;
        if (SDL_QueryTexture(state->spriteTexture, NULL, NULL, &w, &h) != 0) {
            throw std::runtime_error("Failed to query texture! SDL Error: " + std::string(SDL_GetError()));
        }
        state->spriteRect = {(SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2, w, h};

        // Initialize current window size
        state->currentWidth = SCREEN_WIDTH;
        state->currentHeight = SCREEN_HEIGHT;

        return state;
    } catch (const std::exception& e) {
        std::cerr << "Error in init: " << e.what() << std::endl;
        return nullptr;
    }
}

void cleanup(GameState* state) {
    if (state != nullptr) {
        if (state->spriteTexture != nullptr) {
            SDL_DestroyTexture(state->spriteTexture);
        }
        if (state->renderer != nullptr) {
            SDL_DestroyRenderer(state->renderer);
        }
        if (state->window != nullptr) {
            SDL_DestroyWindow(state->window);
        }
        delete state;
    }
    SDL_Quit();
}