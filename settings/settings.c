#include <SDL2/SDL_ttf.h>
#include "structs.h"
#include "settings.h"

// Inicializa el estado del juego con valores predeterminados
void InitGameState(GameState *gameState)
{
    gameState->screenWidth = 1280;
    gameState->screenHeight = 720;
    gameState->segmentSize = 40;
    gameState->borderWidth = 40;
    gameState->maxSnakeLength = 100;

    gameState->menuOption = 0;
    gameState->onMenu = 1;
    gameState->score = 0;
    gameState->snakeLength = 0;
    gameState->running = 1;
    gameState->velX = 0;
    gameState->velY = 0;
    gameState->font = NULL;
}

// Definición de las variables globales
SDL_Color textColor = {255, 255, 255}; // Color blanco
SDL_Texture *snakeTextureUp, *snakeTextureDown, *snakeTextureLeft, *snakeTextureRight, *snakeTurnTextureUpLeft , *snakeTurnTextureUpRight , *snakeTurnTextureDownRight , *snakeTurnTextureDownLeft ;
SDL_Texture *snakeBodyTextureHorizontal, *snakeBodyTextureVertical;
SDL_Event event;
SDL_Texture *foodTexture;

// Carga la fuente y verifica errores
TTF_Font *GetFont(GameState *gameState)
{
    gameState->font = TTF_OpenFont("fonts/ComicSansMS3.ttf", 24);
    if (!gameState->font)
    {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        SDL_Quit();
        SetRunningStatus(gameState, 0);
        return NULL;
    }
    return gameState->font;
}

void CloseFont(GameState *gameState)
{
    if (gameState->font)
    {
        TTF_CloseFont(gameState->font);
        gameState->font = NULL;
    }
}

// Funciones de acceso y modificación para las variables en GameState

int GetScore(GameState *gameState)
{
    return gameState->score;
}

int GetMenuOption(GameState *gameState)
{
    return gameState->menuOption;
}

int GetSnakeLength(GameState *gameState)
{
    return gameState->snakeLength;
}
int GetBorderWidth(GameState *gameState)
{
    return gameState->borderWidth;
}

int GetRunningStatus(GameState *gameState)
{
    return gameState->running;
}

void SetRunningStatus(GameState *gameState, int status)
{
    gameState->running = status;
}
void SetMenuOption(GameState *gameState, int option)
{
    printf("cambiando %d", option);
    gameState->menuOption = option;
}

int GetSnakeVelY(GameState *gameState)
{
    return gameState->velY;
}

void SetSnakeVelY(GameState *gameState, int velY)
{
    gameState->velY = velY;
}

int GetSnakeVelX(GameState *gameState)
{
    return gameState->velX;
}

void SetSnakeVelX(GameState *gameState, int velX)
{
    gameState->velX = velX;
}

int GetMaxSnakeLength(GameState *gameState)
{
    return gameState->maxSnakeLength;
}
int GetSegmentSize(GameState *gameState)
{
    return gameState->segmentSize;
}
int GetScreenHeight(GameState *gameState)
{
    return gameState->screenHeight;
}
int GetScreenWidth(GameState *gameState)
{
    return gameState->screenWidth;
}
int GetMenuStatus(GameState *gameState)
{
    return gameState->onMenu;
}
int SetMenuStatus(GameState *gameState, int status)
{
     gameState->onMenu = status;
}

void setSnakeLimits(GameState *gamestate, Segment *snake)
{
    const int SCREEN_WIDTH = GetScreenHeight(gamestate);
    const int SCREEN_HEIGHT = GetScreenHeight(gamestate);
    const int BORDER_WIDTH = GetBorderWidth(gamestate);
    const int SEGMENT_SIZE = GetSegmentSize(gamestate);
    if (snake[0].x < BORDER_WIDTH)
    {
        snake[0].x = BORDER_WIDTH;
    }
    else if (snake[0].x >= SCREEN_WIDTH - BORDER_WIDTH)
    {
        snake[0].x = SCREEN_WIDTH - BORDER_WIDTH - SEGMENT_SIZE;
    }
    if (snake[0].y < BORDER_WIDTH)
    {
        snake[0].y = BORDER_WIDTH;
    }
    else if (snake[0].y >= SCREEN_HEIGHT - BORDER_WIDTH)
    {
        snake[0].y = SCREEN_HEIGHT - BORDER_WIDTH - SEGMENT_SIZE;
    }
}
