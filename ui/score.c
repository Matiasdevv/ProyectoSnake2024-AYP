#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../settings/structs.h"
#include "../settings/settings.h"
#include <SDL2/SDL_ttf.h>

// Dibujar el puntaje
void drawScore(SDL_Renderer *renderer, GameState *gamestate)
{
    int score = GetScore(gamestate);
    // Preparar el texto del puntaje
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score); // Convierte el puntaje a cadena de texto

    // Renderizar el texto del puntaje a una superficie
    TTF_Font *font = GetFont(gamestate);
    if (!font)
    {
        printf("roto");
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid((TTF_Font *)font, scoreText, getTextColor());
    if (!textSurface)
    {
        printf("Error al crear la superficie del texto: %s\n", TTF_GetError());
        return;
    }

    // Crear textura a partir de la superficie del texto
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        printf("Error al crear la textura del texto: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Posicionar el puntaje en pantalla
    SDL_Rect textRect = {GetBorderWidth(gamestate), GetBorderWidth(gamestate) - textSurface->h + 6, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Renderiza el texto

    // Limpiar memoria de superficie y textura
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

// Función para capturar el nombre
void EnterName(SDL_Renderer *renderer, char *name, GameState *gamestate)
{
    int SCREEN_WIDTH = GetScreenWidth(gamestate);   // Obtener anchura de la pantalla
    int SCREEN_HEIGHT = GetScreenHeight(gamestate); // Obtener altura de la pantalla
    int maxLen = 50;

    SDL_Event event;
    int done = 0;
    int index = 0;

    SDL_Color textColor = {255, 255, 255, 255};                                // Color blanco
    SDL_Rect inputRect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 200, 100}; // Posición del texto ingresado

    // Variable para el texto del título
    char title[50] = "Por favor, ingrese su nombre "; // Texto para la parte superior de la pantalla

    // Posición del texto superior
    SDL_Rect titleRect = {SCREEN_WIDTH / 2 - 200, 50, 400, 50}; // Ancho y alto iniciales

    while (!done)
    {
        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro
        SDL_RenderClear(renderer);

        // Renderizar el texto superior
        SDL_Surface *titleSurface = TTF_RenderText_Blended(GetFont(gamestate), title, textColor);
        if (titleSurface)
        {
            SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
            if (titleTexture)
            {
                titleRect.w = titleSurface->w; // Ajustar ancho al texto
                titleRect.h = titleSurface->h; // Ajustar alto al texto
                SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
                SDL_DestroyTexture(titleTexture);
            }
            SDL_FreeSurface(titleSurface);
        }

        // Renderizar el texto ingresado
        SDL_Surface *inputSurface = TTF_RenderText_Blended(GetFont(gamestate), name, textColor);
        if (inputSurface)
        {
            SDL_Texture *inputTexture = SDL_CreateTextureFromSurface(renderer, inputSurface);
            if (inputTexture)
            {
                inputRect.w = inputSurface->w; // Ajustar ancho al texto
                inputRect.h = inputSurface->h; // Ajustar alto al texto
                SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);
                SDL_DestroyTexture(inputTexture);
            }
            SDL_FreeSurface(inputSurface);
        }

        SDL_RenderPresent(renderer);

        // Manejar eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = 1; // Salir si se cierra la ventana
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    done = 1; // Salir cuando presionan Enter
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && index > 0)
                {
                    name[--index] = '\0'; // Eliminar último caracter
                }
                else if (index < maxLen - 1)
                {
                    char key = event.key.keysym.sym;
                    if (key >= 32 && key <= 126)
                    { // Solo caracteres imprimibles
                        name[index++] = key;
                        name[index] = '\0';
                    }
                }
            }
        }
    }
}

void SavePlayerData(char *filename, int score, char name[])
{
    FILE *file = fopen(filename, "a"); // Abre el archivo en modo agregar
    if (file)
    {
        fprintf(file, "%s, %d, NORMAL\n", name, score);
        fclose(file);
    }
    else
    {
        printf("Error: No se pudo guardar el puntaje.\n");
    }
}

void SaveScore(GameState *gamestate, SDL_Renderer *renderer)
{

    char playerName[50];

    // Obtén el puntaje actual
    int score = GetScore(gamestate);

    // Captura el nombre del usuario
    EnterName(renderer, playerName, gamestate);

    // Guardar en un archivo
    SavePlayerData("data/scores.txt", score, playerName);
}