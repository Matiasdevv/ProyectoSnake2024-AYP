
#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL.h>

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
    int diffoption;
    int diff;
    int delay;
    int delayoption;
    TTF_Font *font;
    Player player;
} GameState;

extern SDL_Color textColor; // Color blanco
extern SDL_Texture *snakeTextureUp, *snakeTextureDown, *snakeTextureLeft, *snakeTextureRight, *snakeTurnTextureUpLeft, *snakeTurnTextureUpRight, *snakeTurnTextureDownRight, *snakeTurnTextureDownLeft;
extern SDL_Texture *snakeBodyTextureHorizontal, *snakeBodyTextureVertical;
extern SDL_Texture *Edge_up, *Edge_down, *Edge_turn_left_down, *Edge_turn_left_up, *Edge_turn_right_top,*Edge_turn_top_right;
extern SDL_Event event;
extern SDL_Texture *foodTexture;
// Prototipos de funciones para manipular el estado del juego

// Inicialización y carga de recursos
void InitGameState(GameState *gameState, Player Player);
TTF_Font *GetFont(GameState *gameState);
void CloseFont(GameState *gameState);
void LoadTextures(GameState *gamestate, SDL_Renderer *renderer);
void ResetGameState(GameState *gameState);
void setPlayer(GameState *gameState, Player Player);
// Accesores y modificadores
char *GetPlayerName(GameState *gameState);
void SetPlayerName(GameState *gameState, char *name);
int GetScore(GameState *gameState);
void UpdateScore(GameState *gameState);
int GetMenuOption(GameState *gameState);
int GetSnakeLength(GameState *gameState);
void SetSnakeLength(GameState *gameState, int snakelen);
int GetRunningStatus(GameState *gameState);
void SetRunningStatus(GameState *gameState, int status);
void SetMenuOption(GameState *gameState, int option);
void setSnakeLimits(GameState *gamestate, Segment *snake);
void exitGame(GameState *gameState, SDL_Renderer *renderer, SDL_Window *window);
int GetSnakeVelY(GameState *gameState);
void SetSnakeVelY(GameState *gameState, int velY);
int GetSnakeVelX(GameState *gameState);
void SetSnakeVelX(GameState *gameState, int velX);
int GetDiffStatus(GameState *gameState);
int SetDiffStatus(GameState *gameState, int menuoption);
int GetDelayStatus(GameState *gameState);
int SetDelayStatus(GameState *gameState, int delayoption);

int GetBorderWidth(GameState *gameState);

int GetSegmentSize(GameState *gameState);
int GetScreenHeight(GameState *gameState);
int GetScreenWidth(GameState *gameState);
int GetMaxSnakeLength(GameState *gameState);
int GetMenuStatus(GameState *gameState);
int SetMenuStatus(GameState *gameState, int status);
SDL_Texture *getSnakeTextureUp();
SDL_Texture *getSnakeTextureDown();
SDL_Texture *getSnakeTextureLeft();
SDL_Texture *getSnakeTextureRight();
SDL_Texture *getSnakeTurnTextureUpLeft();
SDL_Texture *getSnakeTurnTextureUpRight();
SDL_Texture *getSnakeTurnTextureDownRight();
SDL_Texture *getSnakeTurnTextureDownLeft();
SDL_Texture *getSnakeBodyTextureHorizontal();
SDL_Texture *getSnakeBodyTextureVertical();
SDL_Texture *getFoodTexture();
SDL_Texture *getEdge_up();
SDL_Texture *getEdge_down();
SDL_Texture *getEdge_turn_left_donw();
SDL_Texture *getEdge_turn_left_up();
SDL_Texture *getEdge_turn_right_top();
SDL_Texture *getEdge_turn_top_right();
SDL_Color getTextColor();
#endif // GAME_H