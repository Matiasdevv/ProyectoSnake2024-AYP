#include <SDL2/SDL_ttf.h> // Asegúrate de que la librería SDL_ttf está incluida

// Declaración de la variable font

#ifndef GLOBAL_H_ /* Include guard */
#define GLOBAL_H_

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 720
#define SEGMENT_SIZE 40
#define BORDER_WIDTH 40
#define MAX_SNAKE_LENGTH 100

extern int menuOption; // Para rastrear la opción seleccionada
extern int onMenu;     // Indica si estamos en el menú

extern int score;

int snakeLength = 2;
int running = 1;
int velX = SEGMENT_SIZE; // Velocidad en X
int velY = 0;            // Velocidad en Y
TTF_Font *font = NULL;   // Esto debe estar en un archivo .c, no en el .h

void loadFont();

#endif