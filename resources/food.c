#include "../settings/structs.h"
#include "../settings/settings.h"
#include "snake.h"
#include <SDL2/SDL.h>

SDL_Rect newFoodRect(Segment food)
{
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};
}

void SetFoodPosition(int x, int y, Segment food)
{
    food.x = x;
    food.y = y;
}
void snakeFoodCollition(GameState *gamestate, Segment *snake, Segment *food)
{
    SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
    ;
    SDL_Rect foodRect = newFoodRect(*food);

    if (SDL_HasIntersection(&snakeHead, &foodRect))
    {
        int random_number = (rand() % 31) * GetSegmentSize(gamestate); // generar número aleatorio dentro de la cuadrícula
        int random_number2 = (rand() % 17) * GetSegmentSize(gamestate);

        if (random_number == 0)
        {
            while (random_number == 0)
            {
                random_number = (rand() % 31) * GetSegmentSize(gamestate); // seguir generando números hasta que sea distinto de 0
            }
        }

        // Verificar que el número no sea 0 para random_number2
        if (random_number2 == 0)
        {
            while (random_number2 == 0)
            {
                random_number2 = (rand() % 17) * GetSegmentSize(gamestate); // seguir generando números hasta que sea distinto de 0
            }
        }

        SetFoodPosition(random_number, random_number2, *food);
        SetSnakeLength(gamestate, GetSnakeLength(gamestate) + 1);
        // UpdateScore(gamestate);
    }
}

void drawFood(SDL_Renderer *renderer, Segment food)
{
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};
    SDL_Texture *foodTexture = getFoodTexture();
    SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);
}

Segment initializeFood(GameState *gamestate)
{
    Segment food;
    food.x = (rand() % 31) * GetSegmentSize(gamestate);
    food.y = (rand() % 17) * GetSegmentSize(gamestate);
    food.w = GetSegmentSize(gamestate);
    food.h = GetSegmentSize(gamestate);

    if (food.x == 0)
    {
        while (food.x == 0)
        {
            food.x = (rand() % 31) * GetSegmentSize(gamestate); // seguir generando números hasta que sea distinto de 0
        }
    }

    // Verificar que el número no sea 0 para random_number2
    if (food.y == 0)
    {
        while (food.y == 0)
        {
            food.y = (rand() % 17) * GetSegmentSize(gamestate); // seguir generando números hasta que sea distinto de 0
        }
    }
    printf("cordenada x %d \n", food.x);
    printf("cordenada y %d \n", food.y);

    return food;
}