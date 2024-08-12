#include "loop.h"
#include "../engine/init.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

void movement_loop(GameState* state, bool& quit) {
    try {
        SDL_Event e;
        bool moveUp = false, moveDown = false, moveLeft = false, moveRight = false;

        while (!quit) {
            while (SDL_PollEvent(&e) != 0) {
                if (e.type == SDL_QUIT) {
                    quit = true;
                } else if (e.type == SDL_KEYDOWN) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP: moveUp = true; break;
                        case SDLK_DOWN: moveDown = true; break;
                        case SDLK_LEFT: moveLeft = true; break;
                        case SDLK_RIGHT: moveRight = true; break;
                    }
                } else if (e.type == SDL_KEYUP) {
                    switch (e.key.keysym.sym) {
                        case SDLK_UP: moveUp = false; break;
                        case SDLK_DOWN: moveDown = false; break;
                        case SDLK_LEFT: moveLeft = false; break;
                        case SDLK_RIGHT: moveRight = false; break;
                    }
                } else if (e.type == SDL_WINDOWEVENT) {
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
                        state->currentWidth = e.window.data1;
                        state->currentHeight = e.window.data2;
                        std::cout << "Window resized to " << state->currentWidth << "x" << state->currentHeight << std::endl;
                    }
                }
            }

            // Calculate the 4:3 gameplay area dimensions
            float gameplayAspectRatio = 4.0f / 3.0f;
            int gameplayWidth, gameplayHeight;
            if ((float)state->currentWidth / state->currentHeight > gameplayAspectRatio) {
                gameplayHeight = state->currentHeight;
                gameplayWidth = (int)(gameplayHeight * gameplayAspectRatio);
            } else {
                gameplayWidth = state->currentWidth;
                gameplayHeight = (int)(gameplayWidth / gameplayAspectRatio);
            }

            // Calculate the offset to center the gameplay area
            int offsetX = (state->currentWidth - gameplayWidth) / 2;
            int offsetY = (state->currentHeight - gameplayHeight) / 2;

            // Calculate scaling factor
            float scale = (float)gameplayWidth / SCREEN_WIDTH;

            // Calculate scaled sprite dimensions
            int scaledSpriteSize = (int)(state->spriteRect.w * scale);

            // Move sprite based on key states
            float moveSpeed = 2.0f * scale;
            if (moveUp) state->spriteRect.y = std::max(0, state->spriteRect.y - (int)moveSpeed);
            if (moveDown) state->spriteRect.y = std::min(SCREEN_HEIGHT - state->spriteRect.h, state->spriteRect.y + (int)moveSpeed);
            if (moveLeft) state->spriteRect.x = std::max(0, state->spriteRect.x - (int)moveSpeed);
            if (moveRight) state->spriteRect.x = std::min(SCREEN_WIDTH - state->spriteRect.w, state->spriteRect.x + (int)moveSpeed);

            // Clear screen
            if (SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 255) < 0) {
                throw std::runtime_error("SDL_SetRenderDrawColor failed: " + std::string(SDL_GetError()));
            }
            if (SDL_RenderClear(state->renderer) < 0) {
                throw std::runtime_error("SDL_RenderClear failed: " + std::string(SDL_GetError()));
            }

            // Render the background to fill the entire window
            SDL_Rect backgroundRect = {0, 0, state->currentWidth, state->currentHeight};
            if (SDL_RenderCopy(state->renderer, state->backgroundTexture, NULL, &backgroundRect) < 0) {
                throw std::runtime_error("SDL_RenderCopy failed for background: " + std::string(SDL_GetError()));
            }

            // Draw the white gameplay area
            SDL_Rect gameplayArea = {offsetX, offsetY, gameplayWidth, gameplayHeight};
            if (SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 255) < 0) {
                throw std::runtime_error("SDL_SetRenderDrawColor failed: " + std::string(SDL_GetError()));
            }
            if (SDL_RenderFillRect(state->renderer, &gameplayArea) < 0) {
                throw std::runtime_error("SDL_RenderFillRect failed: " + std::string(SDL_GetError()));
            }

            // Create a destination rectangle that scales the sprite
            SDL_Rect destRect;
            destRect.w = scaledSpriteSize;
            destRect.h = scaledSpriteSize;
            destRect.x = offsetX + (int)(state->spriteRect.x * scale);
            destRect.y = offsetY + (int)(state->spriteRect.y * scale);

            // Render scaled sprite
            if (SDL_RenderCopy(state->renderer, state->spriteTexture, NULL, &destRect) < 0) {
                throw std::runtime_error("SDL_RenderCopy failed for sprite: " + std::string(SDL_GetError()));
            }

            // Update screen
            SDL_RenderPresent(state->renderer);

            // Small delay to control frame rate (approximately 60 FPS)
            SDL_Delay(16);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error in movement_loop: " << e.what() << std::endl;
        quit = true;
    } catch (...) {
        std::cerr << "Unknown error in movement_loop" << std::endl;
        quit = true;
    }
}