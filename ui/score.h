
#ifndef SCORE_H_ /* Include guard */
#define SCORE_H_
#include <SDL2/SDL.h>
void drawScore(SDL_Renderer *renderer, GameState *gamestate);
void SaveScore(GameState *gamestate,SDL_Renderer *renderer);
void EnterName(SDL_Renderer *renderer, char *name, GameState *gamestate);
void SavePlayerData(char *filename, int score, char name[50]);
#endif