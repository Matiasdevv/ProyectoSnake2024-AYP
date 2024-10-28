#include "snake.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdl.h"
#include "global.h"
#include <SDL2/SDL_ttf.h>

#ifndef MAP_H_ /* Include guard */
#define MAP_H_

void drawMapBorders(SDL_Renderer *renderer);
#endif