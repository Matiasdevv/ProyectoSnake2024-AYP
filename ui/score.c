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