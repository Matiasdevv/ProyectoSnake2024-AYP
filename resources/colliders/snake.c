#include "structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "sdl.h"

// Función para verificar colisión del cuerpo de la serpiente
void snakeBodyCollition(int snakeLength, Segment snake[])
{
    // Verifica si la cabeza colisiona con algún segmento del cuerpo
    for (int i = 1; i < snakeLength; i++)
    {
        SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
        SDL_Rect snakeBodySegment = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (SDL_HasIntersection(&snakeHead, &snakeBodySegment))
        {
            running = 0; // Termina el juego si hay colisión
        }
    }
}

void setSnakeVel(Segment snake[], int velX, int velY)
{
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }

    snake[0].x += velX;
    snake[0].y += velY;
}

void setSnakeLimits(Segment snake[])
{
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
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        if (velY == 0)
        { // Solo puede ir hacia arriba si no está yendo hacia arriba o abajo
            velX = 0;
            velY = -SEGMENT_SIZE;
        }
        break;
    case SDLK_DOWN:
        if (velY == 0)
        { // Solo puede ir hacia abajo si no está yendo hacia arriba o abajo
            velX = 0;
            velY = SEGMENT_SIZE;
        }
        break;
    case SDLK_LEFT:
        if (velX == 0)
        { // Solo puede ir hacia la izquierda si no está yendo hacia la izquierda o derecha
            velX = -SEGMENT_SIZE;
            velY = 0;
        }
        break;
    case SDLK_RIGHT:
        if (velX == 0)
        { // Solo puede ir hacia la derecha si no está yendo hacia la izquierda o derecha
            velX = SEGMENT_SIZE;
            velY = 0;
        }
        break;
    }
}

void drawSnake(SDL_Renderer *renderer, Segment snake[])
{
    for (int i = 0; i < snakeLength; i++)
    {
        SDL_Rect rect = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (i == 0)
        { // Cabeza
            // Determinar la textura de la cabeza según la dirección de movimiento
            if (velY < 0)
            { // Moviéndose hacia arriba
                SDL_RenderCopy(renderer, snakeTextureUp, NULL, &rect);
            }
            else if (velY > 0)
            { // Moviéndose hacia abajo
                SDL_RenderCopy(renderer, snakeTextureDown, NULL, &rect);
            }
            else if (velX < 0)
            { // Moviéndose hacia la izquierda
                SDL_RenderCopy(renderer, snakeTextureLeft, NULL, &rect);
            }
            else if (velX > 0)
            { // Moviéndose hacia la derecha
                SDL_RenderCopy(renderer, snakeTextureRight, NULL, &rect);
            }
        }
        else
        { // Cuerpo
            // Determinar la textura del cuerpo según la dirección del segmento actual
            if (snake[i].x == snake[i - 1].x)
            { // Movimiento vertical
                SDL_RenderCopy(renderer, snakeBodyTextureVertical, NULL, &rect);
            }
            else
            { // Movimiento horizontal
                SDL_RenderCopy(renderer, snakeBodyTextureHorizontal, NULL, &rect);
            }
        }
    }
}

Segment *initializeSnake()
{
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

void setSnakeVel(velx, vely)
{
}