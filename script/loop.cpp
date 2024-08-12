// In loop.cpp
#include "loop.h"
#include "../engine/init.h"
#include <algorithm>

void movement_loop(GameState* state, bool& quit) {
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

        // Move sprite based on key states
        if (moveUp) {
            state->spriteRect.y = std::max(0, state->spriteRect.y - 2);
        }
        if (moveDown) {
            state->spriteRect.y = std::min(SCREEN_HEIGHT - state->spriteRect.h, state->spriteRect.y + 2);
        }
        if (moveLeft) {
            state->spriteRect.x = std::max(0, state->spriteRect.x - 2);
        }
        if (moveRight) {
            state->spriteRect.x = std::min(SCREEN_WIDTH - state->spriteRect.w, state->spriteRect.x + 2);
        }

        // Clear screen
        SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 255);
        SDL_RenderClear(state->renderer);

        // Render sprite
        SDL_RenderCopy(state->renderer, state->spriteTexture, NULL, &(state->spriteRect));

        // Update screen
        SDL_RenderPresent(state->renderer);

        // Small delay to control frame rate (approximately 60 FPS)
        SDL_Delay(16);
    }
}
