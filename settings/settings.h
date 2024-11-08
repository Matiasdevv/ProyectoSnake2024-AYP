
#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL_ttf.h>
#include "structs.h"

// Estructura que contiene el estado completo del juego
typedef struct
{
    int screenWidth;
    int screenHeight;
    int segmentSize;
    int borderWidth;
    int maxSnakeLength;

    int menuOption;
    int onMenu;
    int score;
    int snakeLength;
    int running;
    int velX;
    int velY;

    TTF_Font *font;
} GameState;

extern SDL_Color textColor; // Color blanco
extern SDL_Texture *snakeTextureUp, *snakeTextureDown, *snakeTextureLeft, *snakeTextureRight;
extern SDL_Texture *snakeBodyTextureHorizontal, *snakeBodyTextureVertical;
extern SDL_Event event;
extern SDL_Texture *foodTexture;
// Prototipos de funciones para manipular el estado del juego

// Inicialización y carga de recursos
void InitGameState(GameState *gameState);
TTF_Font *GetFont(GameState *gameState);
void CloseFont(GameState *gameState);

// Accesores y modificadores
int GetScore(GameState *gameState);
int GetMenuOption(GameState *gameState);
int GetSnakeLength(GameState *gameState);
int GetRunningStatus(GameState *gameState);
void SetRunningStatus(GameState *gameState, int status);
void SetMenuOption(GameState *gameState, int option);
void setSnakeLimits(GameState *gamestate, Segment *snake);

int GetSnakeVelY(GameState *gameState);
void SetSnakeVelY(GameState *gameState, int velY);
int GetSnakeVelX(GameState *gameState);
void SetSnakeVelX(GameState *gameState, int velX);

int GetBorderWidth(GameState *gameState);

int GetSegmentSize(GameState *gameState);
int GetScreenHeight(GameState *gameState);
int GetMaxSnakeLength(GameState *gameState);

#endif // GAME_H