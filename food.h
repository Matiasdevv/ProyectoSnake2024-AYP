#include "structs.h"
#include <SDL2/SDL_ttf.h>
#ifndef FOOD_H_ /* Include guard */
#define FOOD_H_

void snakeFoodCollition();

void drawFood(SDL_Renderer *renderer, Segment food);

Segment *initializeFood();

#endif // FOO_H_