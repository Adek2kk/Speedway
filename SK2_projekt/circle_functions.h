#ifndef CIRCLE_FUNCTIONS_H
#define CIRCLE_FUNCTIONS_H

//The header
#include "SDL/SDL.h"
#include <math.h>

//The surfaces
extern SDL_Surface *screen;

#endif
void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);

bool fill_first_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);

Uint32 get_color(int x, int y, SDL_Surface *surface);