#ifndef LOOP_H
#define LOOP_H

#include <SDL.h>

void movement_loop(SDL_Window* window, SDL_Surface* screenSurface, SDL_Rect& rect, Uint32 rectColor, bool& quit);

#endif // LOOP_H