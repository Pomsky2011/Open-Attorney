
#include <SDL.h>
#include <iostream>
#include <limits>
#include "engine/init.h"
#include "script/loop.h"

const int RECT_SIZE = 32;

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
        bool quit = false;
        int red = 0, green = 0, blue = 0;
        SDL_Rect rect = {(SCREEN_WIDTH - RECT_SIZE) / 2, (SCREEN_HEIGHT - RECT_SIZE) / 2, RECT_SIZE, RECT_SIZE};

        while (!quit) {
            std::cout << "Insert Red Value (0-255): ";
            if (!(std::cin >> red)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Using default value 0.\n";
                red = 0;
            }
            std::cout << "Insert Green Value (0-255): ";
            if (!(std::cin >> green)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Using default value 0.\n";
                green = 0;
            }
            std::cout << "Insert Blue Value (0-255): ";
            if (!(std::cin >> blue)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Using default value 0.\n";
                blue = 0;
            }

            // Ensure values are within valid range
            red = std::max(0, std::min(255, red));
            green = std::max(0, std::min(255, green));
            blue = std::max(0, std::min(255, blue));

            // Create color
            Uint32 rectColor = SDL_MapRGB(screenSurface->format, red, green, blue);

            std::cout << "Use arrow keys to move the rectangle. Press 'q' to quit or enter new color values." << std::endl;

            movement_loop(window, screenSurface, rect, rectColor, quit);
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
