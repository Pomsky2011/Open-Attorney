#include <SDL.h>
#include <iostream>
#include "engine/init.h"

int main(int argc, char* args[]) {
    try {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("SDL could not initialize! SDL_Error: " + std::string(SDL_GetError()));
        }

        SDL_Window* window = init(argc, args);
        if (window == nullptr) {
            throw std::runtime_error("Failed to initialize window!");
        }

        // Get the window surface
        SDL_Surface* screenSurface = SDL_GetWindowSurface(window);
        if (screenSurface == nullptr) {
            throw std::runtime_error("Failed to get window surface! SDL_Error: " + std::string(SDL_GetError()));
        }

        // Fill the surface with the desired color (e.g., red)
        if (SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 0, 0)) != 0) {
            throw std::runtime_error("Failed to fill rect! SDL_Error: " + std::string(SDL_GetError()));
        }

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
                // Handle other events here
            }

            // Add your game logic here
        }

        // Clean up
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        SDL_Quit();
        return 1;
    }
}