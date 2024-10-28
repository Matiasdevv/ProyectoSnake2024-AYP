#include "snake.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdl.h"
#include "global.h"
#include <SDL2/SDL_ttf.h>

#ifndef MENU_H_ /* Include guard */
#define MENU_H_

void drawMenu(SDL_Renderer *renderer, TTF_Font *font);
void handleMenuInput(SDL_Event event);

#endif