#include "../settings/structs.h"
#include "../settings/settings.h"
#include "../resources/snake.h"
#include "menu.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

void drawMapBorders(SDL_Renderer *renderer, GameState gamestate)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Color verde
    const int SCREEN_WIDTH = GetScreenHeight(&gamestate);
    const int SCREEN_HEIGHT = GetScreenHeight(&gamestate);
    const int BORDER_WIDTH = GetBorderWidth(&gamestate);
    const int SEGMENT_SIZE = GetSegmentSize(&gamestate);
    // Borde superior
    SDL_Rect topBorder = {0, 0, SCREEN_WIDTH, BORDER_WIDTH};
    SDL_RenderFillRect(renderer, &topBorder);

    // Borde inferior
    SDL_Rect bottomBorder = {0, SCREEN_HEIGHT - BORDER_WIDTH, SCREEN_WIDTH, BORDER_WIDTH};
    SDL_RenderFillRect(renderer, &bottomBorder);

    // Borde izquierdo
    SDL_Rect leftBorder = {0, 0, BORDER_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &leftBorder);

    // Borde derecho
    SDL_Rect rightBorder = {SCREEN_WIDTH - BORDER_WIDTH, 0, BORDER_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &rightBorder);
}