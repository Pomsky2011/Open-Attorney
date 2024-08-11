#include "loop.h"
#include "../engine/init.h"
#include <algorithm>

const int RECT_SIZE = 32;  // Add this line

void movement_loop(SDL_Window* window, SDL_Surface* screenSurface, SDL_Rect& rect, Uint32 rectColor, bool& quit) {
    SDL_Event e;
    bool colorLoop = true;
    bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;

    while (colorLoop && !quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
                colorLoop = false;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        moveUp = true;
                        break;
                    case SDLK_DOWN:
                        moveDown = true;
                        break;
                    case SDLK_LEFT:
                        moveLeft = true;
                        break;
                    case SDLK_RIGHT:
                        moveRight = true;
                        break;
                    case SDLK_q:
                        colorLoop = false;
                        break;
                }
            } else if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        moveUp = false;
                        break;
                    case SDLK_DOWN:
                        moveDown = false;
                        break;
                    case SDLK_LEFT:
                        moveLeft = false;
                        break;
                    case SDLK_RIGHT:
                        moveRight = false;
                        break;
                }
            }
        }

        // Move rectangle based on key states
        if (moveUp) {
            rect.y = std::max(0, rect.y - 2);
        }
        if (moveDown) {
            rect.y = std::min(SCREEN_HEIGHT - RECT_SIZE, rect.y + 2);
        }
        if (moveLeft) {
            rect.x = std::max(0, rect.x - 2);
        }
        if (moveRight) {
            rect.x = std::min(SCREEN_WIDTH - RECT_SIZE, rect.x + 2);
        }

        // Clear the screen
        SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 255, 255));

        // Draw the colored rectangle
        SDL_FillRect(screenSurface, &rect, rectColor);

        // Update the surface
        SDL_UpdateWindowSurface(window);

        // Small delay to control frame rate (approximately 60 FPS)
        SDL_Delay(16);
    }
}