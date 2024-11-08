#ifndef MENU_H_ /* Include guard */
#define MENU_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void drawMenu(SDL_Renderer *renderer, GameState *gamestate);
void handleMenuInput(SDL_Event event, GameState *gamestate);

#endif