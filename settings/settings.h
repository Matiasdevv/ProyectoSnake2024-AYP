#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL2/SDL_ttf.h>

void loadFont(); // Prototipo de la función
void GetFont();  // Prototipo de la función
int GetScore();
int GetMenuOption();
int GetsnakeLength();
int GetRunningStatus();
int GetSnakeVelY();
int GetSnakeVelX();
void SetSnakeVelX(int velX);
void SetSnakeVelY(int velY);
void SetMenuOption(int menuOption);
int GetBorderWidth();
int GetBorderWidth();
int GetScreenHeigth();
int GetScreenHeigth();
int GetSegmentSize();
int GetMaxSnakeLength();
#endif // GLOBAL_H
