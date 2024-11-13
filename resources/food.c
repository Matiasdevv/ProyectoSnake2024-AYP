#include "../settings/structs.h"
#include "../settings/settings.h"
#include "snake.h"
#include <SDL2/SDL.h>


void SetFoodPosition(int x, int y, Segment *food)
{
    food->x = x;
    food->y = y;
}
void snakeFoodCollition(GameState *gamestate, Segment *snake, Segment *food)
{
    
    SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
    SDL_Rect foodRect = {food->x, food->y, food->w, food->h};

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

        SetFoodPosition(random_number, random_number2, food);
        SetSnakeLength(gamestate, 1);
        UpdateScore(gamestate);
    }
}

void drawFood(SDL_Renderer *renderer, Segment food)
{
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};
    SDL_Texture *foodTexture = getFoodTexture();
    SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);
}

Segment *initializeFood(GameState *gamestate)
{
    Segment *food = malloc(sizeof(Segment));
    if (food == NULL)
    {
        // Manejo de error si la memoria no se puede asignar
        fprintf(stderr, "Error al asignar memoria para la serpiente.\n");
        exit(1);
    }

    int randNumber = (rand() % 31) * GetSegmentSize(gamestate);
    int randNumber2 = (rand() % 17) * GetSegmentSize(gamestate);
    food->w = GetSegmentSize(gamestate);
    food->h = GetSegmentSize(gamestate);


    while (randNumber == 0)
    {
        randNumber = (rand() % 31) * GetSegmentSize(gamestate); // seguir generando números hasta que sea distinto de 0
    }


    // Verificar que el número no sea 0 para random_number2

    while (randNumber2 == 0)
    {
       randNumber2 = (rand() % 17) * GetSegmentSize(gamestate) ; // seguir generando números hasta que sea distinto de 0
    }

    SetFoodPosition(randNumber, randNumber2, food);

    printf("cordenada x %d \n", food->x);
    printf("cordenada y %d \n", food->y);

    return food;
}