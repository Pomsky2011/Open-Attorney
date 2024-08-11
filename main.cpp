#include <SDL.h>
#include <iostream>
#include <limits>
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

        // Main game loop
        SDL_Event e;
        bool quit = false;
        int red = 0, green = 0, blue = 0;

        while (!quit) {
            // Handle events
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
            }

            // Get color input
            std::cout << "Insert Red Value (0-255): ";
            std::cin >> red;
            std::cout << "Insert Green Value (0-255): ";
            std::cin >> green;
            std::cout << "Insert Blue Value (0-255): ";
            std::cin >> blue;

            // Clear input buffer
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Ensure values are within valid range
            red = std::max(0, std::min(255, red));
            green = std::max(0, std::min(255, green));
            blue = std::max(0, std::min(255, blue));

            // Fill the surface with the desired color
            if (SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, red, green, blue)) != 0) {
                throw std::runtime_error("Failed to fill rect! SDL_Error: " + std::string(SDL_GetError()));
            }

            // Update the surface
            SDL_UpdateWindowSurface(window);
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