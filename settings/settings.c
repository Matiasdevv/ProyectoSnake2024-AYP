#include <SDL2/SDL_ttf.h>

int SCREEN_WIDTH = 1280;
int SCREEN_HEIGHT = 720;
int SEGMENT_SIZE = 40;
int BORDER_WIDTH = 40;
int MAX_SNAKE_LENGTH = 100;

int menuOption = 0;
int onMenu = 1;
int score = 0;
int snakeLength = 0;
int running = 1;
int velX = 0;
int velY = 0;

TTF_Font *font = NULL; // Inicialización de font

TTF_Font *GetFont()
{
    // Asegúrate de cargar la fuente una vez y verifica que no sea NULL
    font = TTF_OpenFont("../fonts/ComicSansMS3.ttf", 24);
    if (!font)
    {
        printf("Error al cargar la fuente: %s\n", TTF_GetError());
        SDL_Quit();
        SetRunningStatus(0);
        return NULL; // Retorna NULL en caso de error para evitar dereferenciar un puntero inválido
    }
    return font;
}

void SetMenuOption(int menuOption)
{
    menuOption = menuOption;
}

void CloseFont()
{

    TTF_CloseFont(font);
}

int GetScore()
{
    return score;
}
int GetMenuOption()
{
    return menuOption;
}

int GetsnakeLength()
{
    return snakeLength;
}
int GetRunningStatus()
{
    return running;
}
int GetBorderWidth()
{
    return BORDER_WIDTH;
}
int GetSegmentSize()
{
    return SEGMENT_SIZE;
}
int GetBorderHeigth()
{
    return BORDER_WIDTH;
}
void SetRunningStatus(int status)
{
    running = status;
}

int GetSnakeVelY()
{
    return velY;
}
void SetSnakeVelY(int velY)
{
    velY += velY;
}
int GetSnakeVelX()
{
    return velX;
}
void SetSnakeVelX(int velX)
{
    velX += velX;
}

int GetMaxSnakeLength()
{
    return MAX_SNAKE_LENGTH;
};
