
#ifndef DRAW_H /* Include guard */
#define DRAW_H

#include "../settings/structs.h"
#include "../settings/settings.h"

void drawSnake(SDL_Renderer *renderer, Segment *snake, GameState *gamestate);
void drawRanking(SDL_Renderer *renderer, GameState *gameState);
#endif