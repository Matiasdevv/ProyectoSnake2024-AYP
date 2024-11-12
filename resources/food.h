#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#ifndef FOOD_H_ /* Include guard */
#define FOOD_H_

void snakeFoodCollition(GameState *gamestate, Segment *snake, Segment *food);
SDL_Rect newFoodRect(Segment food);
void SetFoodPosition(int x, int y, Segment food);
void drawFood(SDL_Renderer *renderer, Segment *food);

Segment initializeFood(GameState *gamestate);

#endif