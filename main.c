#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structs.h"
#include "global.h"
#include "sdl.h"

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

int main()
{
    srand(time(NULL));
    Segment *snake = (Segment *)initializeSnake();
    Segment *food = (Segment *)initializeFood();

    // Inicializar SDL y TTF
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0)
    {
        printf("Error al inicializar SDL o TTF: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("Snake Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    while (onMenu)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                onMenu = 0;
                running = 0;
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handleMenuInput(event); // Manejar la entrada del menú
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMenu(renderer); // Dibujar el menú

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    // Aquí empieza el juego después de que se sale del menú

    snakeTextureUp = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("resources/sprite/snake_head_up.bmp"));
    snakeTextureDown = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("resources/sprite/snake_head_down.bmp"));
    snakeTextureLeft = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("resources/sprite/snake_head_left.bmp"));
    snakeTextureRight = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("resources/sprite/snake_head_right.bmp"));

    snakeBodyTextureHorizontal = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("resources/sprite/snake_body_horizontal.bmp"));
    snakeBodyTextureVertical = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("resources/sprite/snake_body_vertical.bmp"));

    if (!snakeTextureUp || !snakeTextureDown || !snakeTextureLeft || !snakeTextureRight ||
        !snakeBodyTextureHorizontal || !snakeBodyTextureVertical)
    {
        printf("Error al cargar texturas: %s\n", SDL_GetError());
        return 1;
    }

    foodTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("resources/sprite/food_sprite.bmp"));
    if (!foodTexture)
    {
        printf("Error al cargar la textura de la comida: %s\n", SDL_GetError());
        running = 0;
    }

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN)
            {
                snakeMovement(event);
            }
        }

        setSnakeVel(snake, velX, velY);

        setSnakeLimits(snake);

        snakeFoodCollition(snake, food); // Verificar colisión con la comida
        snakeBodyCollition(snake);       // Verificar colisión con el cuerpo

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMapBorders(renderer); // Dibujar los bordes
        drawSnake(renderer);      // Dibujar la serpiente
        drawFood(renderer);       // Dibujar la comida
        drawScore(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
    TTF_CloseFont(font);
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

    return 0;
}