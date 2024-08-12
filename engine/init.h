#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include "appdata.h"
#include "texture_loader.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct GameState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* spriteTexture;
    SDL_Rect spriteRect;
    int currentWidth;
    int currentHeight;
};

GameState* init(int argc, char* args[]);
void cleanup(GameState* state);

#endif // INIT_H