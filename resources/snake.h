#ifndef SNAKE_H_ /* Include guard */
#define SNAKE_H_
#include "../settings/structs.h"
#include <SDL2/SDL.h>

Segment *initializeSnake(GameState *gameState);
void snakeMovement(SDL_Event event, GameState *gameState);
void snakeBodyCollition(GameState *gamestate, Segment *snake);

#endif