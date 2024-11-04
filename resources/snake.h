#ifndef SNAKE_H_ /* Include guard */
#define SNAKE_H_
#include "../settings/structs.h"
#include <SDL2/SDL.h>

Segment *initializeSnake();

void drawSnake(SDL_Renderer *renderer, Segment snake[]);

void snakeMovement(SDL_Event event);

void snakeBodyCollition(Segment snake[]);

void setSnakeLimits(Segment snake[]);

void setSnakeVel(Segment snake[]);

#endif