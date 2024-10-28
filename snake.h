
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdl.h"
#include "global.h"
#include <SDL2/SDL_ttf.h>

#ifndef SNAKE_H_ /* Include guard */
#define SNAKE_H_

void setSnakeVel(velx, vely);

void initializeSnake();

void drawSnake(SDL_Renderer *renderer, Segment snake[]);

void snakeMovement(SDL_Event event);

void snakeBodyCollition(int snakeLength, Segment snake[]);

void setSnakeLimits(Segment snake[]);

void setSnakeVel(Segment snake[], int velX, int velY);

#endif