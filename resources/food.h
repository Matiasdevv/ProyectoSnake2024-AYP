#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#ifndef FOOD_H_ /* Include guard */
#define FOOD_H_

void snakeFoodCollition(GameState *gamestate, Segment *snake, Segment *food);
void SetFoodPosition(int x, int y, Segment food);
void drawFood(SDL_Renderer *renderer, Segment food);

void *initializeFood(GameState *gamestate, Segment *food);

#endif