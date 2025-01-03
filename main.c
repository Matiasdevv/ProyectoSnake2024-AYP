#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "settings/settings.h"
#include "settings/structs.h"
#include "resources/food.h"
#include "ui/map.h"
#include "ui/score.h"
#include "ui/menu.h"
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

    GameState gameState;
    Player player = (Player){name : "", difficulty : 0, score : 0};
    // Declarar e inicializar el estado del juego
    InitGameState(&gameState, player);

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
        GetScreenWidth(&gameState),
        GetScreenHeight(&gameState),
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

    Segment *snake = malloc(GetMaxSnakeLength(&gameState) * sizeof(Segment));
    Segment *food = malloc(sizeof(Segment));
    // Obtener el nombre del jugador
    EnterName(renderer, &gameState);

    while (GetRunningStatus(&gameState) != 0)
    {
        // Manejo de eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SetRunningStatus(&gameState, 0);
            }
        }

        // Limpiar pantalla
        SDL_RenderClear(renderer);

        // Verificar el estado del menú
        if (GetMenuStatus(&gameState) == 1)
        {
            // Mostrar el menú
            showMenu(event, &gameState, renderer, window);
        }
        if (GetMenuStatus(&gameState) == 0 && GetMenuOption(&gameState) == 0)
        {
            // Mostrar el juego principal
            // Aquí empieza el juego después de que se sale del menú

            LoadTextures(&gameState, renderer);

            initializeSnake(&gameState, snake);
            initializeFood(&gameState, food);
            initializeMainGame(event, &gameState, renderer, food, snake);
        }

        // Actualizar la pantalla
        SDL_RenderPresent(renderer);
    }

    TTF_CloseFont(GetFont(&gameState));
    SDL_DestroyTexture(getSnakeTextureUp(&gameState));
    SDL_DestroyTexture(getSnakeTextureDown(&gameState));
    SDL_DestroyTexture(getSnakeTextureLeft(&gameState));
    SDL_DestroyTexture(getSnakeTextureRight(&gameState));
    SDL_DestroyTexture(getSnakeBodyTextureHorizontal(&gameState));
    SDL_DestroyTexture(getSnakeBodyTextureVertical(&gameState));
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
