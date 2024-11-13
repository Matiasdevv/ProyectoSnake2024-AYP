#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../settings/structs.h"
#include "../settings/settings.h"
#include "food.h"
#include "../ui/map.h"
#include "../ui/score.h"
#include "../ui/draw.h"


// Función para verificar colisión del cuerpo de la serpiente
void snakeBodyCollition(GameState *gamestate, Segment *snake)
{
    int snakeLength = GetSnakeLength(gamestate);

    // Verifica si la cabeza colisiona con algún segmento del cuerpo
    for (int i = 1; i < snakeLength; i++)
    {
        SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
        SDL_Rect snakeBodySegment = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (SDL_HasIntersection(&snakeHead, &snakeBodySegment))
        {
            SetMenuStatus(gamestate,1);
            SetMenuOption(gamestate,0);
            InitGameState(gamestate);
        }
    }
}

void snakeMovement(SDL_Event event, GameState *gamestate)
{
    const int SEGMENT_SIZE = GetSegmentSize(gamestate);
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        if (GetSnakeVelY(gamestate) == 0)
        { // Solo puede ir hacia arriba si no está yendo hacia arriba o abajo
            SetSnakeVelX(gamestate, 0);
            SetSnakeVelY(gamestate, -SEGMENT_SIZE);
        }
        break;
    case SDLK_DOWN:
        if (GetSnakeVelY(gamestate) == 0)
        { // Solo puede ir hacia abajo si no está yendo hacia arriba o abajo

            SetSnakeVelX(gamestate, 0);
            SetSnakeVelY(gamestate, SEGMENT_SIZE);
        }
        break;
    case SDLK_LEFT:
        if (GetSnakeVelX(gamestate) <= 0)
        { // Solo puede ir hacia la izquierda si no está yendo hacia la izquierda o derecha
            SetSnakeVelX(gamestate, -SEGMENT_SIZE);
            SetSnakeVelY(gamestate, 0);
        }
        break;
    case SDLK_RIGHT:
        if (GetSnakeVelX(gamestate) >= 0)
        { // Solo puede ir hacia la derecha si no está yendo hacia la izquierda o derecha
            SetSnakeVelX(gamestate, SEGMENT_SIZE);
            SetSnakeVelY(gamestate, 0);
        }
        break;
    }
}

Segment *initializeSnake(GameState *gamsetate)
{
    const int MAX_SNAKE_LENGTH = GetMaxSnakeLength(gamsetate);
    const int SCREEN_WIDTH = GetScreenWidth(gamsetate);
    const int SCREEN_HEIGHT = GetScreenHeight(gamsetate);
    // const int BORDER_WIDTH = GetBorderHeight(gamsetate);
    const int SEGMENT_SIZE = GetSegmentSize(gamsetate);
    Segment *snake = malloc(MAX_SNAKE_LENGTH * sizeof(Segment));
    if (snake == NULL)
    {
        // Manejo de error si la memoria no se puede asignar
        fprintf(stderr, "Error al asignar memoria para la serpiente.\n");
        exit(1);
    }
    snake[0].x = SCREEN_WIDTH / 2; // Inicializa en el centro de la pantalla
    snake[0].y = SCREEN_HEIGHT / 2;
    snake[0].w = SEGMENT_SIZE;
    snake[0].h = SEGMENT_SIZE;

    return snake;
}


void initializeMainGame(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, Segment *food, Segment *snake ){

    while (GetRunningStatus(gameState) == 1 && GetMenuStatus(gameState) == 0 && GetMenuOption(gameState) == 0)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SetRunningStatus(gameState, 0);
            }
            if (event.type == SDL_KEYDOWN)
            {
                snakeMovement(event, gameState);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        snakeFoodCollition(gameState, snake, food); // Verificar colisión con la comida
        snakeBodyCollition(gameState, snake);        // Verificar colisión con el cuerpo

        drawFood(renderer, food);           // Dibujar la comida
        drawSnake(renderer, snake, gameState); // Dibujar la serpiente

        drawMapBorders(renderer,gameState); // Dibujar los bordes
        drawScore(renderer, gameState);
        setSnakeLimits(gameState, snake);

        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
}
