#include "sdl.h";
#include "../settings/structs.h";

void drawSnake(SDL_Renderer *renderer, Segment snake[])
{
    for (int i = 0; i < GetSnakeLength(); i++)
    {
        SDL_Rect rect = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (i == 0)
        { // Cabeza
            // Determinar la textura de la cabeza según la dirección de movimiento
            if (GetSnakeVelY() < 0)
            { // Moviéndose hacia arriba
                SDL_RenderCopy(renderer, snakeTextureUp, NULL, &rect);
            }
            else if (GetSnakeVelY() > 0)
            { // Moviéndose hacia abajo
                SDL_RenderCopy(renderer, snakeTextureDown, NULL, &rect);
            }
            else if (GetSnakeVelX() < 0)
            { // Moviéndose hacia la izquierda
                SDL_RenderCopy(renderer, snakeTextureLeft, NULL, &rect);
            }
            else if (GetSnakeVelX() > 0)
            { // Moviéndose hacia la derecha
                SDL_RenderCopy(renderer, snakeTextureRight, NULL, &rect);
            }
        }
        else
        { // Cuerpo
            // Determinar la textura del cuerpo según la dirección del segmento actual
            if (snake[i].x == snake[i - 1].x)
            { // Movimiento vertical
                SDL_RenderCopy(renderer, snakeBodyTextureVertical, NULL, &rect);
            }
            else
            { // Movimiento horizontal
                SDL_RenderCopy(renderer, snakeBodyTextureHorizontal, NULL, &rect);
            }
        }
    }
}