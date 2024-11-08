#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "settings/settings.h"
#include "settings/structs.h"
#include "resources/food.h"
#include "ui/menu.h"
#include "ui/map.h"
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

    if (!window)
    {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        CloseFont(&gameState);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    // Bucle principal del juego
    while (GetRunningStatus(&gameState))
    {
        // Lógica del juego aquí
        // Puedes usar y modificar el estado del juego a través de funciones que aceptan gameState como parámetro
        // Ejemplo: aumentar la puntuación
        gameState.score += 1;

        // Actualización de la pantalla
        SDL_Delay(1000 / 60); // Control de velocidad del juego (60 FPS)
    }

    // Limpiar recursos antes de salir
    CloseFont(&gameState);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}

//
