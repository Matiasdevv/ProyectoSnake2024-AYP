#include <SDL2/SDL_ttf.h>
#include "../settings/structs.h"
#include "../settings/settings.h"
#include "score.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void drawMenu(SDL_Renderer *renderer, GameState *gameState)
{
    int SCREEN_WIDTH = GetScreenWidth(gameState);   // Deberías obtener la anchura de la pantalla correctamente
    int SCREEN_HEIGHT = GetScreenHeight(gameState); // Asegúrate de que estos valores sean correctos
    int BORDER_WIDTH = GetBorderWidth(gameState);
    int SEGMENT_SIZE = GetSegmentSize(gameState);

    // Colores
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0}; // Rojo para la opción seleccionada

    // Fuente
    TTF_Font *font = GetFont(gameState);

    // Opción de menú "Jugar"
    SDL_Surface *playSurface = TTF_RenderText_Solid(font, "Jugar", GetMenuOption(gameState) == 0 ? red : white);
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Rect playRect = {SCREEN_WIDTH / 2 - 50, 200, 100, 50};
    SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
    SDL_FreeSurface(playSurface);
    SDL_DestroyTexture(playTexture);

    // Opción de menú "Ranking"
    SDL_Surface *rankingSurface = TTF_RenderText_Solid(font, "Ranking", GetMenuOption(gameState) == 1 ? red : white);
    SDL_Texture *rankingTexture = SDL_CreateTextureFromSurface(renderer, rankingSurface);
    SDL_Rect rankingRect = {SCREEN_WIDTH / 2 - 50, 300, 100, 50};
    SDL_RenderCopy(renderer, rankingTexture, NULL, &rankingRect);
    SDL_FreeSurface(rankingSurface);
    SDL_DestroyTexture(rankingTexture);

    // Opción de menú "Dificultad"
    SDL_Surface *difficultySurface = TTF_RenderText_Solid(font, "Dificultad", GetMenuOption(gameState) == 2 ? red : white);
    SDL_Texture *difficultyTexture = SDL_CreateTextureFromSurface(renderer, difficultySurface);
    SDL_Rect difficultyRect = {SCREEN_WIDTH / 2 - 50, 400, 100, 50};
    SDL_RenderCopy(renderer, difficultyTexture, NULL, &difficultyRect);
    SDL_FreeSurface(difficultySurface);
    SDL_DestroyTexture(difficultyTexture);
}

void handleMenuInput(SDL_Event event, GameState *gameState)
{
    int menuOption = GetMenuOption(gameState); // Obtener la opción del menú actual
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        // Decrementar la opción seleccionada (si no es menor que 0, en cuyo caso va a la opción 2)
        menuOption--;
        if (menuOption < 0)
        {
            menuOption = 2; // Opción "Dificultad" (última opción)
        }
        SetMenuOption(gameState, menuOption); // Actualizar el estado global
        break;
    case SDLK_DOWN:
        // Incrementar la opción seleccionada (si no es mayor que 2, en cuyo caso va a la opción 0)
        menuOption++;
        if (menuOption > 2)
        {
            menuOption = 0; // Opción "Jugar" (primera opción)
        }
        SetMenuOption(gameState, menuOption); // Actualizar el estado global
        break;
    case SDLK_RETURN:
        // Manejar las opciones seleccionadas
        if (menuOption == 0)
        {
            printf("Arrancando juego principal...\n");
            SetMenuOption(gameState, menuOption); // Actualizar el estado global
            SetMenuStatus(gameState, 0);
            // Implementar la lógica para iniciar el juego
        }
        else if (menuOption == 1)
        {
            printf("Mostrando ranking...\n");
            SetMenuOption(gameState, menuOption); // Actualizar el estado global
            SetMenuStatus(gameState, 0);
            // Implementar la lógica para mostrar el ranking
        }
        else if (menuOption == 2)
        {
            printf("Seleccionando dificultad...\n");
            // Implementar la lógica para cambiar la dificultad
            SetMenuOption(gameState, menuOption); // Actualizar el estado global
            SetMenuStatus(gameState, 0);
        }
        break;
    }
}
