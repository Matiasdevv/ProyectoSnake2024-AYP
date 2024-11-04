#include "sdl.h";
#include "../settings/structs.h";

#ifndef DRAW_H /* Include guard */
#define DRAW_H

void drawSnake(SDL_Renderer *renderer, Segment snake[]);

#endif