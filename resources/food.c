#include "../settings/structs.h"
#include "snake.h"
#include "../ui/sdl.h"
#include <SDL2/SDL.h>

void snakeFoodCollition(Segment snake[], Segment food)
{
    // Detección de colisión entre la serpiente y la comida
    SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};

    if (SDL_HasIntersection(&snakeHead, &foodRect))
    {
        int random_number = (rand() % 31) * GetSegmentSize(); // generar número aleatorio dentro de la cuadrícula
        int random_number2 = (rand() % 17) * GetSegmentSize();

        if (random_number == 0)
        {
            while (random_number == 0)
            {
                random_number = (rand() % 31) * GetSegmentSize(); // seguir generando números hasta que sea distinto de 0
            }
        }

        // Verificar que el número no sea 0 para random_number2
        if (random_number2 == 0)
        {
            while (random_number2 == 0)
            {
                random_number2 = (rand() % 17) * GetSegmentSize(); // seguir generando números hasta que sea distinto de 0
            }
        }

        food.x = random_number; // actualizar la posición x de la comida

        food.y = random_number2; // actualizar la posición y de la comida
        SetSnakeLenght(GetSnakeLenght() + 1);
        SetScore(GetScore() + 1); // Aumenta el puntaje cuando come comida
        printf("cordenada x %d \n", food.x);
        printf("cordenada y %d \n", food.y);
    }
}

void drawFood(SDL_Renderer *renderer, Segment food)
{
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};
    SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);
}

Segment initializeFood()
{
    Segment food;
    food.x = (rand() % 31) * GetSegmentSize();
    food.y = (rand() % 17) * GetSegmentSize();
    food.w = GetSegmentSize();
    food.h = GetSegmentSize();

    if (food.x == 0)
    {
        while (food.x == 0)
        {
            food.x = (rand() % 31) * GetSegmentSize(); // seguir generando números hasta que sea distinto de 0
        }
    }

    // Verificar que el número no sea 0 para random_number2
    if (food.y == 0)
    {
        while (food.y == 0)
        {
            food.y = (rand() % 17) * GetSegmentSize(); // seguir generando números hasta que sea distinto de 0
        }
    }
    printf("cordenada x %d \n", food.x);
    printf("cordenada y %d \n", food.y);

    return food;
}