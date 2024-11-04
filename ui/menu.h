
#include <SDL2/SDL.h>

#include <SDL2/SDL_ttf.h>

#ifndef MENU_H_ /* Include guard */
#define MENU_H_

void drawMenu(SDL_Renderer *renderer);
void handleMenuInput(SDL_Event event);

#endif