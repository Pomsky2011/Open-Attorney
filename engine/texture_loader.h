#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include <SDL.h>
#include <string>

SDL_Texture* loadTexture(SDL_Renderer* renderer, const std::string& filename);
SDL_Texture* loadScaledTexture(SDL_Renderer* renderer, const std::string& filename, int targetWidth, int targetHeight);

#endif // TEXTURE_LOADER_H