#include <SDL2/SDL_ttf.h>
#include "global.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SEGMENT_SIZE 40
#define BORDER_WIDTH 40
#define MAX_SNAKE_LENGTH 100

int menuOption = 0; // Para rastrear la opción seleccionada
int onMenu = 1;     // Indica si estamos en el menú

int score = 0;
// TTF_Font *font = NULL;

int snakeLength = 2;
int running = 1;
int velX = SEGMENT_SIZE; // Velocidad en X
int velY = 0;            // Velocidad en Y
TTF_Font *font = NULL;

void loadFont()
{
    // Asegurarse de cargar la fuente una vez y verificar que no sea NULL
    font = TTF_OpenFont("resources/fonts/ComicSansMS3.ttf", 24);
    if (!font)
    {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
}