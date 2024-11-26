#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../settings/structs.h"
#include "../settings/settings.h"
#include "food.h"
#include "../ui/map.h"
#include "../ui/score.h"

void drawSnake(SDL_Renderer *renderer, Segment *snake, GameState *gamestate)
{
    int snakeLength = GetSnakeLength(gamestate);

    // Mover la serpiente (actualizar posiciones)
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1]; // Mover cada segmento hacia el anterior
    }
    snake[0].x += GetSnakeVelX(gamestate); // Actualizar la posición de la cabeza (x)
    snake[0].y += GetSnakeVelY(gamestate); // Actualizar la posición de la cabeza (y)

    // Renderizar la serpiente (dibujar segmentos)
    for (int i = 0; i < snakeLength; i++)
    {
        SDL_Rect rect = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (i == 0)
        { // Renderizar la cabeza
            if (GetSnakeVelY(gamestate) < 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureUp(), NULL, &rect);
            }
            else if (GetSnakeVelY(gamestate) > 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureDown(), NULL, &rect);
            }
            else if (GetSnakeVelX(gamestate) < 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureLeft(), NULL, &rect);
            }
            else if (GetSnakeVelX(gamestate) > 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureRight(), NULL, &rect);
            }
        }
        else
        {
            int prevX = snake[i - 1].x, prevY = snake[i - 1].y;
            int nextX = (i < snakeLength - 1) ? snake[i + 1].x : snake[i].x;
            int nextY = (i < snakeLength - 1) ? snake[i + 1].y : snake[i].y;

            // Determinar el tipo de giro
            if (prevY < snake[i].y && nextX > snake[i].x || nextY < snake[i].y && prevX > snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureDownRight(), NULL, &rect);
            }
            else if (prevY < snake[i].y && nextX < snake[i].x || nextY < snake[i].y && prevX < snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureDownLeft(), NULL, &rect);
            }
            else if (prevY > snake[i].y && nextX > snake[i].x || nextY > snake[i].y && prevX > snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureUpRight(), NULL, &rect);
            }
            else if (prevY > snake[i].y && nextX < snake[i].x || nextY > snake[i].y && prevX < snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureUpLeft(), NULL, &rect);
            }
            else
            {
                if (snake[i].x == snake[i - 1].x)
                {
                    SDL_RenderCopy(renderer, snakeBodyTextureVertical, NULL, &rect);
                }
                else
                {
                    SDL_RenderCopy(renderer, snakeBodyTextureHorizontal, NULL, &rect);
                }
            }
        }
    }
}

// Función para verificar colisión del cuerpo de la serpiente
void snakeBodyCollition(GameState *gamestate, Segment *snake, SDL_Renderer *renderer)
{
    int snakeLength = GetSnakeLength(gamestate);

    // Verifica si la cabeza colisiona con algún segmento del cuerpo
    for (int i = 1; i < snakeLength; i++)
    {
        SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
        SDL_Rect snakeBodySegment = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (SDL_HasIntersection(&snakeHead, &snakeBodySegment))
        {
            TTF_CloseFont(GetFont(gamestate));
            SDL_DestroyTexture(getSnakeTextureUp(gamestate));
            SDL_DestroyTexture(getSnakeTextureDown(gamestate));
            SDL_DestroyTexture(getSnakeTextureLeft(gamestate));
            SDL_DestroyTexture(getSnakeTextureRight(gamestate));
            SDL_DestroyTexture(getSnakeBodyTextureHorizontal(gamestate));
            SDL_DestroyTexture(getSnakeBodyTextureVertical(gamestate));
            SetMenuStatus(gamestate, 1);
            SetMenuOption(gamestate, 0);
            SaveScore(gamestate, renderer);
            ResetGameState(gamestate);
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

void *initializeSnake(GameState *gamsetate, Segment *snake)
{
    const int MAX_SNAKE_LENGTH = GetMaxSnakeLength(gamsetate);
    const int SCREEN_WIDTH = GetScreenWidth(gamsetate);
    const int SCREEN_HEIGHT = GetScreenHeight(gamsetate);
    // const int BORDER_WIDTH = GetBorderHeight(gamsetate);
    const int SEGMENT_SIZE = GetSegmentSize(gamsetate);
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
}

void initializeMainGame(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, Segment *food, Segment *snake)
{

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
        snakeFoodCollition(gameState, snake, food);     // Verificar colisión con la comida
        snakeBodyCollition(gameState, snake, renderer); // Verificar colisión con el cuerpo
        drawFood(renderer, *food);                      // Dibujar la comida
        drawSnake(renderer, snake, gameState);          // Dibujar la serpiente

        drawMapBorders(renderer, gameState); // Dibujar los bordes
        drawScore(renderer, gameState);
        setSnakeLimits(gameState, snake);

        SDL_RenderPresent(renderer);
        SDL_Delay(GetDelayStatus(gameState));
    }
}
