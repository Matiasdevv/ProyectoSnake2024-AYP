#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sdl.h"
#include "../settings/structs.h"
#include <SDL2/SDL_ttf.h>

// Dibujar el puntaje
void drawScore(SDL_Renderer *renderer)
{
    // Preparar el texto del puntaje
    char scoreText[20];
    sprintf(scoreText, "Score: %d", Getscore()); // Convierte el puntaje a cadena de texto

    // Renderizar el texto del puntaje a una superficie
    const TTF_Font *font = GetFont();

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, textColor);
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
    SDL_Rect textRect = {GetBorderWidth(), GetBorderWidth() - textSurface->h + 6, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Renderiza el texto

    // Limpiar memoria de superficie y textura
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}