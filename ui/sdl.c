#include <SDL2/SDL.h>
SDL_Color textColor = {255, 255, 255}; // Color blanco

SDL_Texture *snakeTextureUp, *snakeTextureDown, *snakeTextureLeft, *snakeTextureRight;
SDL_Texture *snakeBodyTextureHorizontal, *snakeBodyTextureVertical;
SDL_Event event;

SDL_Texture *foodTexture;