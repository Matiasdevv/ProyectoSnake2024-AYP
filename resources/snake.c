#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../settings/structs.h"

// Función para verificar colisión del cuerpo de la serpiente
void snakeBodyCollition(Segment snake[])
{
    int snakeLength = GetSnakeLength();

    // Verifica si la cabeza colisiona con algún segmento del cuerpo
    for (int i = 1; i < snakeLength; i++)
    {
        SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
        SDL_Rect snakeBodySegment = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (SDL_HasIntersection(&snakeHead, &snakeBodySegment))
        {
            SetRunningStatus(0);
        }
    }
}

void setSnakeVel(Segment snake[])
{
    int snakeLength = GetSnakeLength();
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    // snake[0].x += velX;
    // snake[0].y += velY;
}

void setSnakeLimits(Segment snake[])
{
    const SCREEN_WIDTH = GetScreenHeight();
    const SCREEN_HEIGHT = GetScreenHeight();
    const BORDER_WIDTH = GetBorderHeight();
    const SEGMENT_SIZE = GetSegmentSize();
    if (snake[0].x < BORDER_WIDTH)
    {
        snake[0].x = BORDER_WIDTH;
    }
    else if (snake[0].x >= SCREEN_WIDTH - BORDER_WIDTH)
    {
        snake[0].x = SCREEN_WIDTH - BORDER_WIDTH - SEGMENT_SIZE;
    }
    if (snake[0].y < BORDER_WIDTH)
    {
        snake[0].y = BORDER_WIDTH;
    }
    else if (snake[0].y >= SCREEN_HEIGHT - BORDER_WIDTH)
    {
        snake[0].y = SCREEN_HEIGHT - BORDER_WIDTH - SEGMENT_SIZE;
    }
}

void snakeMovement(SDL_Event event)
{
    const SEGMENT_SIZE = GetSegmentSize();
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        if (GetVelY() == 0)
        { // Solo puede ir hacia arriba si no está yendo hacia arriba o abajo
            SetVelX(0);
            SetVelY(-SEGMENT_SIZE);
        }
        break;
    case SDLK_DOWN:
        if (GetVelY() == 0)
        { // Solo puede ir hacia abajo si no está yendo hacia arriba o abajo
            SetVelX(0);
            SetVelY(SEGMENT_SIZE);
        }
        break;
    case SDLK_LEFT:
        if (GetVelX() == 0)
        { // Solo puede ir hacia la izquierda si no está yendo hacia la izquierda o derecha
            SetVelX(-SEGMENT_SIZE);

            SetVelY(0);
        }
        break;
    case SDLK_RIGHT:
        if (GetVelX() == 0)
        { // Solo puede ir hacia la derecha si no está yendo hacia la izquierda o derecha
            SetVelX(SEGMENT_SIZE);
            SetVelY(0);
        }
        break;
    }
}

Segment *initializeSnake()
{
    const MAX_SNAKE_LENGTH = GetMaxSnakeLength();
    const SCREEN_WIDTH = GetScreenHeight();
    const SCREEN_HEIGHT = GetScreenHeight();
    const BORDER_WIDTH = GetBorderHeight();
    const SEGMENT_SIZE = GetSegmentSize();
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
