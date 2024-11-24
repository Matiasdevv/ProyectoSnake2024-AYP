#ifndef MENU_H_ /* Include guard */
#define MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void drawMenu(SDL_Renderer *renderer, GameState *gamestate);
void handleMenuInput(SDL_Event event, GameState *gamestate, SDL_Renderer *renderer, SDL_Window *window);
void showMenu(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, SDL_Window *window);
void drawDifficultyMenu(SDL_Renderer *renderer, GameState *gameState);
void handleDifficultyInput(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, SDL_Window *window);
void drawRanking(SDL_Renderer *renderer, GameState *gameState);
void handleRankingInput(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, SDL_Window *window);
#endif