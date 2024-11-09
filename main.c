#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "settings/settings.h"
#include "settings/structs.h"
#include "resources/food.h"
#include "ui/menu.h"
#include "ui/map.h"
#include "ui/draw.h"
#include "ui/score.h"
#include "resources/snake.h"

int fileExists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    // Inicialización de SDL y SDL_ttf
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return -1;
    }
    if (TTF_Init() == -1)
    {
        printf("Error al inicializar SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return -1;
    }

    // Declarar e inicializar el estado del juego
    GameState gameState;
    InitGameState(&gameState);
    // Aquí empieza el juego después de que se sale del menú
    Segment *snake = initializeSnake(&gameState);
    Segment food = (Segment)initializeFood(&gameState);

    // Cargar la fuente
    if (!GetFont(&gameState))
    {
        printf("No se pudo cargar la fuente\n");
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Crear ventana (ejemplo)
    SDL_Window *window = SDL_CreateWindow(
        "Snake Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        gameState.screenWidth,
        gameState.screenHeight,
        SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

        if (!window)
    {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        CloseFont(&gameState);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    while (GetRunningStatus(&gameState) && GetMenuStatus(&gameState) == 1)
    {
        SDL_RenderClear(renderer);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SetMenuOption(&gameState, 0);
                SetRunningStatus(&gameState, 0);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handleMenuInput(event, &gameState); // Manejar la entrada del menú
            }
        }

        drawMenu(renderer, &gameState); // Dibujar el menú

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    snakeTextureUp = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_up.bmp"));
    snakeTextureDown = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_down.bmp"));
    snakeTextureLeft = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_left.bmp"));
    snakeTextureRight = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_right.bmp"));
    snakeBodyTextureHorizontal = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_body_horizontal.bmp"));
    snakeBodyTextureVertical = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_body_vertical.bmp"));

    snakeTurnTextureUpLeft = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_up_left.bmp"));
    snakeTurnTextureUpRight = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_up_right.bmp"));
    snakeTurnTextureDownRight = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_down_right.bmp"));
    snakeTurnTextureDownLeft = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_down_left.bmp"));

    if (!snakeTextureUp || !snakeTextureDown || !snakeTextureLeft || !snakeTextureRight ||
        !snakeBodyTextureHorizontal || !snakeBodyTextureVertical || !snakeTurnTextureUpLeft ||
        !snakeTurnTextureUpRight || !snakeTurnTextureDownRight || !snakeTurnTextureDownLeft)
    {
        printf("Error al cargar texturas: %s\n", SDL_GetError());
        return 1;
    }

    foodTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprite/food_sprite.bmp"));
    if (!foodTexture)
    {
        printf("Error al cargar la textura de la comida: %s\n", SDL_GetError());
        SetRunningStatus(&gameState, 0);
    }

    while (GetRunningStatus(&gameState) == 1 && GetMenuStatus(&gameState) == 0 && GetMenuOption(&gameState) == 0){
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SetRunningStatus(&gameState, 0);
            }
            if (event.type == SDL_KEYDOWN)
            {
                snakeMovement(event, &gameState);
            }
        }



        setSnakeLimits(&gameState, snake);

        snakeFoodCollition(&gameState,snake, &food);                  // Verificar colisión con la comida
        snakeBodyCollition(&gameState, snake); // Verificar colisión con el cuerpo

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMapBorders(renderer, gameState);               // Dibujar los bordes
        drawSnake(renderer, snake, &gameState); // Dibujar la serpiente
        drawFood(&gameState, renderer, &food);  // Dibujar la comida
        drawScore(renderer, gameState);

        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }


    // Limpiar recursos antes de salir
    CloseFont(&gameState);
    SDL_DestroyTexture(snakeTextureUp);
    SDL_DestroyTexture(snakeTextureDown);
    SDL_DestroyTexture(snakeTextureLeft);
    SDL_DestroyTexture(snakeTextureRight);
    SDL_DestroyTexture(snakeBodyTextureHorizontal);
    SDL_DestroyTexture(snakeBodyTextureVertical);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

//
