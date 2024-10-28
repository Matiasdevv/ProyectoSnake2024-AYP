#include "structs.h"
#include "sdl.h"
#include "food.h"
#include "global.h"
#include <SDL2/SDL.h>

void snakeFoodCollition(int snakeLength, Segment snake[], Segment food)
{
    // Detección de colisión entre la serpiente y la comida
    SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};

    if (SDL_HasIntersection(&snakeHead, &foodRect))
    {
        int random_number = (rand() % 31) * SEGMENT_SIZE; // generar número aleatorio dentro de la cuadrícula
        int random_number2 = (rand() % 17) * SEGMENT_SIZE;

        if (random_number == 0)
        {
            while (random_number == 0)
            {
                random_number = (rand() % 31) * SEGMENT_SIZE; // seguir generando números hasta que sea distinto de 0
            }
        }

        // Verificar que el número no sea 0 para random_number2
        if (random_number2 == 0)
        {
            while (random_number2 == 0)
            {
                random_number2 = (rand() % 17) * SEGMENT_SIZE; // seguir generando números hasta que sea distinto de 0
            }
        }

        food.x = random_number;  // actualizar la posición x de la comida
        food.y = random_number2; // actualizar la posición y de la comida
        snakeLength++;           // aumentar el tamaño de la serpiente
        score++;                 // Aumenta el puntaje cuando come comida
        printf("cordenada x %d \n", food.x);
        printf("cordenada y %d \n", food.y);
    }
}

void drawFood(SDL_Renderer *renderer, Segment food)
{
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};
    SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);
}

Segment *initializeFood()
{
    Segment food;
    food.x = (rand() % 31) * SEGMENT_SIZE;
    food.y = (rand() % 17) * SEGMENT_SIZE;
    food.w = SEGMENT_SIZE;
    food.h = SEGMENT_SIZE;

    if (food.x == 0)
    {
        while (food.x == 0)
        {
            food.x = (rand() % 31) * SEGMENT_SIZE; // seguir generando números hasta que sea distinto de 0
        }
    }

    // Verificar que el número no sea 0 para random_number2
    if (food.y == 0)
    {
        while (food.y == 0)
        {
            food.y = (rand() % 17) * SEGMENT_SIZE; // seguir generando números hasta que sea distinto de 0
        }
    }
    printf("cordenada x %d \n", food.x);
    printf("cordenada y %d \n", food.y);

    return &food;
}