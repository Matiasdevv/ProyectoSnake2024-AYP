#include <SDL2/SDL.h>

#ifndef SDL_H_
#define SDL_H_

extern SDL_Color textColor; // Color blanco

extern SDL_Texture *snakeTextureUp, *snakeTextureDown, *snakeTextureLeft, *snakeTextureRight;
extern SDL_Texture *snakeBodyTextureHorizontal, *snakeBodyTextureVertical;
extern SDL_Event event;

extern SDL_Texture *foodTexture;

#endif