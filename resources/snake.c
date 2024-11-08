#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../settings/structs.h"
#include "../settings/settings.h"

SDL_Rect newSnakeHead(Segment *snake)
{
    // Detección de colisión entre la serpiente y la comida
    SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
}
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
            SetRunningStatus(gamestate, 0);
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
            SetSnakeVelX(gamestate, -SEGMENT_SIZE);
        }
        break;
    case SDLK_DOWN:
        if (GetSnakeVelY(gamestate) == 0)
        { // Solo puede ir hacia abajo si no está yendo hacia arriba o abajo

            SetSnakeVelX(gamestate, 0);
            SetSnakeVelX(gamestate, SEGMENT_SIZE);
        }
        break;
    case SDLK_LEFT:
        if (GetSnakeVelX(gamestate) == 0)
        { // Solo puede ir hacia la izquierda si no está yendo hacia la izquierda o derecha

            SetSnakeVelX(gamestate, -SEGMENT_SIZE);
            SetSnakeVelX(gamestate, 0);
        }
        break;
    case SDLK_RIGHT:
        if (GetSnakeVelX(gamestate) == 0)
        { // Solo puede ir hacia la derecha si no está yendo hacia la izquierda o derecha

            SetSnakeVelX(gamestate, SEGMENT_SIZE);
            SetSnakeVelX(gamestate, 0);
        }
        break;
    }
}

Segment *initializeSnake(GameState *gamsetate)
{
    const int MAX_SNAKE_LENGTH = GetMaxSnakeLength(gamsetate);
    const int SCREEN_WIDTH = GetScreenHeight(gamsetate);
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

    // Inicializa el segundo segmento justo detrás
    snake[1].x = snake[0].x - SEGMENT_SIZE;
    snake[1].y = snake[0].y;
    snake[1].w = SEGMENT_SIZE;
    snake[1].h = SEGMENT_SIZE;
    return snake;
}
