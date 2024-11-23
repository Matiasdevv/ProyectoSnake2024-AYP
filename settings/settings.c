#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

#include "structs.h"
#include "settings.h"

// Inicializa el estado del juego con valores predeterminados
void InitGameState(GameState *gameState)
{
    gameState->screenWidth = 1280;
    gameState->screenHeight = 720;
    gameState->segmentSize = 40;
    gameState->borderWidth = 40;
    gameState->maxSnakeLength = 300;

    gameState->menuOption = 0;
    gameState->onMenu = 1;
    gameState->score = 0;
    gameState->snakeLength = 2;
    gameState->running = 1;
    gameState->velX = 40;
    gameState->velY = 0;
    gameState->font = NULL;
    gameState-> diffoption = 1;
    gameState -> diff = 1;
    gameState-> delay=200;
    gameState->delayoption;
}

// Definición de las variables globales
SDL_Color textColor = {255, 255, 255}; // Color blanco
SDL_Texture *snakeTextureUp, *snakeTextureDown, *snakeTextureLeft, *snakeTextureRight, *snakeTurnTextureUpLeft, *snakeTurnTextureUpRight, *snakeTurnTextureDownRight, *snakeTurnTextureDownLeft;
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
void UpdateScore(GameState *gameState)
{
    gameState->score++;
}

int GetMenuOption(GameState *gameState)
{
    return gameState->menuOption;
}
int GetDelayStatus(GameState *gameState)
{
    return gameState->delay;
}
int SetDelayStatus(GameState *gameState, int delayoption)
{
    gameState->delay= delayoption;
}

int GetSnakeLength(GameState *gameState)
{
    return gameState->snakeLength;
}
void SetSnakeLength(GameState *gameState, int snakelen)
{
    gameState->snakeLength += snakelen;
}
int GetBorderWidth(GameState *gameState)
{
    return gameState->borderWidth;
}

int GetRunningStatus(GameState *gameState)
{
    return gameState->running;
}

int GetDiffStatus(GameState *gameState)
{
    return gameState->diff;
}

int SetDiffStatus (GameState *gameState, int diffoption)
{
    gameState-> diff = diffoption;
}

void SetRunningStatus(GameState *gameState, int status)
{
    gameState->running = status;
}
void SetMenuOption(GameState *gameState, int option)
{
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
    int SCREEN_WIDTH = GetScreenWidth(gamestate);
    int SCREEN_HEIGHT = GetScreenHeight(gamestate);
    int BORDER_WIDTH = GetBorderWidth(gamestate);
    int SEGMENT_SIZE = GetSegmentSize(gamestate);
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
// Getters para las texturas
SDL_Texture *getSnakeTextureUp()
{
    return snakeTextureUp;
}

SDL_Texture *getSnakeTextureDown()
{
    return snakeTextureDown;
}

SDL_Texture *getSnakeTextureLeft()
{
    return snakeTextureLeft;
}

SDL_Texture *getSnakeTextureRight()
{
    return snakeTextureRight;
}

SDL_Texture *getSnakeTurnTextureUpLeft()
{
    return snakeTurnTextureUpLeft;
}

SDL_Texture *getSnakeTurnTextureUpRight()
{
    return snakeTurnTextureUpRight;
}

SDL_Texture *getSnakeTurnTextureDownRight()
{
    return snakeTurnTextureDownRight;
}

SDL_Texture *getSnakeTurnTextureDownLeft()
{
    return snakeTurnTextureDownLeft;
}

SDL_Texture *getSnakeBodyTextureHorizontal()
{
    return snakeBodyTextureHorizontal;
}

SDL_Texture *getSnakeBodyTextureVertical()
{
    return snakeBodyTextureVertical;
}

SDL_Texture *getFoodTexture()
{
    return foodTexture;
}

// Getter para el color del texto
SDL_Color getTextColor()
{
    return textColor;
}


void exitGame(GameState *gameState, SDL_Renderer *renderer,SDL_Window *window){
    // Limpiar recursos antes de salir
    CloseFont(gameState);
    SDL_DestroyTexture(getSnakeTextureUp());
    SDL_DestroyTexture(getSnakeTextureDown());
    SDL_DestroyTexture(getSnakeTextureLeft());
    SDL_DestroyTexture(getSnakeTextureRight());
    SDL_DestroyTexture(getSnakeBodyTextureHorizontal());
    SDL_DestroyTexture(getSnakeBodyTextureVertical());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}
void LoadTextures(GameState *gamestate, SDL_Renderer *renderer)
{
    snakeTextureUp = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_up.bmp"));
    if (!snakeTextureUp)
    {
        printf("Error al cargar la textura snake_head_up: %s\n", SDL_GetError());
        SetRunningStatus(gamestate, 0);
    }

    snakeTextureDown = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_down.bmp"));
    if (!snakeTextureDown)
    {
        printf("Error al cargar la textura snake_head_down: %s\n", SDL_GetError());
        SetRunningStatus(gamestate, 0);
    }

    snakeTextureLeft = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_left.bmp"));
    if (!snakeTextureLeft)
    {
        printf("Error al cargar la textura snake_head_left: %s\n", SDL_GetError());
        SetRunningStatus(gamestate, 0);
    }

    snakeTextureRight = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_head_right.bmp"));
    if (!snakeTextureRight)
    {
        printf("Error al cargar la textura snake_head_right: %s\n", SDL_GetError());
        SetRunningStatus(gamestate, 0);
    }

    snakeBodyTextureHorizontal = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_body_horizontal.bmp"));
    if (!snakeBodyTextureHorizontal)
    {
        printf("Error al cargar la textura snake_body_horizontal: %s\n", SDL_GetError());
        SetRunningStatus(gamestate, 0);
    }

    snakeBodyTextureVertical = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/snake_body_vertical.bmp"));
    if (!snakeBodyTextureVertical)
    {
        printf("Error al cargar la textura snake_body_vertical: %s\n", SDL_GetError());
        SetRunningStatus(gamestate, 0);
    }

     snakeTurnTextureUpLeft = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_up_left.bmp"));
     if (!snakeTurnTextureUpLeft) {
         printf("Error al cargar la textura Turn_up_left: %s\n", SDL_GetError());
         SetRunningStatus(gamestate,0);
     }

     snakeTurnTextureUpRight = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_up_right.bmp"));
     if (!snakeTurnTextureUpRight) {
         printf("Error al cargar la textura Turn_up_right: %s\n", SDL_GetError());
         SetRunningStatus(gamestate,0);
     }

     snakeTurnTextureDownRight = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_down_right.bmp"));
     if (!snakeTurnTextureDownRight) {
         printf("Error al cargar la textura Turn_down_right: %s\n", SDL_GetError());
         SetRunningStatus(gamestate,0);
     }

     snakeTurnTextureDownLeft = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/Turn_down_left.bmp"));
     if (!snakeTurnTextureDownLeft) {
         printf("Error al cargar la textura Turn_down_left: %s\n", SDL_GetError());
         SetRunningStatus(gamestate,0);
     }

    foodTexture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP("sprites/food_sprite.bmp"));
    if (!foodTexture)
    {
        printf("Error al cargar la textura de la comida: %s\n", SDL_GetError());
        SetRunningStatus(gamestate, 0);
    }
}