#include "../settings/structs.h"
#include "../settings/settings.h"
#include "../resources/snake.h"
#include "menu.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

void drawMapBorders(SDL_Renderer *renderer, GameState *gamestate)
{
    int SCREEN_WIDTH = GetScreenWidth(gamestate);
    int SCREEN_HEIGHT = GetScreenHeight(gamestate);
    int BORDER_WIDTH = GetBorderWidth(gamestate);
    int SEGMENT_SIZE = GetSegmentSize(gamestate);

    // Dibujar el borde superior con textura
    for (int x = 0; x < SCREEN_WIDTH; x += SEGMENT_SIZE)
    {
        SDL_Rect destRect = {x, 0, SEGMENT_SIZE, BORDER_WIDTH};
        SDL_RenderCopy(renderer, getEdge_down(), NULL, &destRect);
    }

    // Dibujar el borde inferior con textura
    for (int x = 0; x < SCREEN_WIDTH; x += SEGMENT_SIZE)
    {
        SDL_Rect destRect = {x, SCREEN_HEIGHT - BORDER_WIDTH, SEGMENT_SIZE, BORDER_WIDTH};
        SDL_RenderCopy(renderer, getEdge_down(), NULL, &destRect);
    }

    // Dibujar el borde izquierdo con textura
    for (int y = 0; y < SCREEN_HEIGHT; y += SEGMENT_SIZE)
    {
        SDL_Rect destRect = {0, y, BORDER_WIDTH, SEGMENT_SIZE};
        SDL_RenderCopy(renderer, getEdge_up(), NULL, &destRect);
    }

    // Dibujar el borde derecho con textura
    for (int y = 0; y < SCREEN_HEIGHT; y += SEGMENT_SIZE)
    {
        SDL_Rect destRect = {SCREEN_WIDTH - BORDER_WIDTH, y, BORDER_WIDTH, SEGMENT_SIZE};
        SDL_RenderCopy(renderer, getEdge_up(), NULL, &destRect);
    }

    // Dibujar las esquinas con textura
    SDL_Rect cornerRect;

    // Esquina superior izquierda
    cornerRect = (SDL_Rect){0, 0, SEGMENT_SIZE, SEGMENT_SIZE};
    SDL_RenderCopy(renderer, getEdge_turn_top_right() , NULL, &cornerRect);

    // Esquina superior derecha
    cornerRect = (SDL_Rect){SCREEN_WIDTH - SEGMENT_SIZE, 0, SEGMENT_SIZE, SEGMENT_SIZE};
    SDL_RenderCopy(renderer,getEdge_turn_left_donw(), NULL, &cornerRect);

    // Esquina inferior izquierda
    cornerRect = (SDL_Rect){0, SCREEN_HEIGHT - SEGMENT_SIZE, SEGMENT_SIZE, SEGMENT_SIZE};
    SDL_RenderCopy(renderer, getEdge_turn_right_top() , NULL, &cornerRect);

    // Esquina inferior derecha
    cornerRect = (SDL_Rect){SCREEN_WIDTH - SEGMENT_SIZE, SCREEN_HEIGHT - SEGMENT_SIZE, SEGMENT_SIZE, SEGMENT_SIZE};
    SDL_RenderCopy(renderer, getEdge_turn_left_up(), NULL, &cornerRect);
}
