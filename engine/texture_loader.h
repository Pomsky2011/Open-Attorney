#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL.h>
#include <string>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filename);

#endif // TEXTURE_LOADER_H