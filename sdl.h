#ifndef SDL_H_
#define SDL_H_

SDL_Color textColor = {255, 255, 255}; // Color blanco

SDL_Texture *snakeTextureUp, *snakeTextureDown, *snakeTextureLeft, *snakeTextureRight;
SDL_Texture *snakeBodyTextureHorizontal, *snakeBodyTextureVertical;
SDL_Event event;

SDL_Texture *foodTexture;
#endif