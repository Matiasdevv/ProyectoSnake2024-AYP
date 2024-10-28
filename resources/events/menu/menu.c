#include "score.h"
#include "menu.h"
#include "snake.h"
#include "structs.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdl.h"
#include "global.h"
#include <SDL2/SDL_ttf.h>

void drawMenu(SDL_Renderer *renderer, TTF_Font *font)
{
    // Colores
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0};

    // Opción de menú "Jugar"
    SDL_Surface *playSurface = TTF_RenderText_Solid(font, "Jugar", menuOption == 0 ? red : white);
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Rect playRect = {SCREEN_WIDTH / 2 - 50, 200, 100, 50};
    SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
    SDL_FreeSurface(playSurface);
    SDL_DestroyTexture(playTexture);

    // Opción de menú "Ranking"
    SDL_Surface *rankingSurface = TTF_RenderText_Solid(font, "Ranking", menuOption == 1 ? red : white);
    SDL_Texture *rankingTexture = SDL_CreateTextureFromSurface(renderer, rankingSurface);
    SDL_Rect rankingRect = {SCREEN_WIDTH / 2 - 50, 300, 100, 50};
    SDL_RenderCopy(renderer, rankingTexture, NULL, &rankingRect);
    SDL_FreeSurface(rankingSurface);
    SDL_DestroyTexture(rankingTexture);

    // Opción de menú "Dificultad"
    SDL_Surface *difficultySurface = TTF_RenderText_Solid(font, "Dificultad", menuOption == 2 ? red : white);
    SDL_Texture *difficultyTexture = SDL_CreateTextureFromSurface(renderer, difficultySurface);
    SDL_Rect difficultyRect = {SCREEN_WIDTH / 2 - 50, 400, 100, 50};
    SDL_RenderCopy(renderer, difficultyTexture, NULL, &difficultyRect);
    SDL_FreeSurface(difficultySurface);
    SDL_DestroyTexture(difficultyTexture);
}

void handleMenuInput(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        menuOption--;
        if (menuOption < 0)
        {
            menuOption = 2; // Volver a la última opción
        }
        break;
    case SDLK_DOWN:
        menuOption++;
        if (menuOption > 2)
        {
            menuOption = 0; // Volver a la primera opción
        }
        break;
    case SDLK_RETURN:
        if (menuOption == 0)
        {
            // Opción "Jugar"
            onMenu = 0; // Salimos del menú y empezamos el juego
        }
        else if (menuOption == 1)
        {
            // Opción "Ranking"
            // Aquí puedes implementar la lógica para mostrar el ranking
            printf("Mostrando ranking...\n");
        }
        else if (menuOption == 2)
        {
            // Opción "Dificultad"
            // Aquí puedes implementar la lógica para cambiar la dificultad
            printf("Seleccionando dificultad...\n");
        }
        break;
    }
}
