#include "../settings/structs.h"
#include "../resources/snake.h"
#include "../ui/menu.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../ui/sdl.h"
#include <SDL2/SDL_ttf.h>

void drawMapBorders(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Color verde
    const SCREEN_WIDTH = GetScreenHeight();
    const SCREEN_HEIGHT = GetScreenHeight();
    const BORDER_WIDTH = GetBorderHeight();
    const SEGMENT_SIZE = GetSegmentSize();
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