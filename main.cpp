#include <SDL.h>
#include <iostream>
#include "engine/init.h"

int main(int argc, char* args[]) {
    if (init(argc, args) != 0) {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_GetWindowFromID(1); // Assuming the window created in init() is the first one
    if (window == nullptr) {
        std::cerr << "Failed to get window! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Main game loop
    SDL_Event e;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Add your game logic here
    }

    // Clean up
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}