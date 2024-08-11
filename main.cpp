#include <SDL.h>
#include <iostream>
#include "engine/init.h"

int main(int argc, char* args[]) {
    SDL_Window* window = init(argc, args);
    if (window == nullptr) {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    // Get the window surface
    SDL_Surface* screenSurface = SDL_GetWindowSurface(window);

    // Fill the surface with the desired color (e.g., red)
    SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 0, 0));

    // Update the surface
    SDL_UpdateWindowSurface(window);

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