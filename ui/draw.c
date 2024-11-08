#include "../settings/structs.h"
#include "../settings/settings.h"

void drawSnake(SDL_Renderer *renderer, Segment *snake, GameState gamestate)
{
    for (int i = 0; i < GetSnakeLength(&gamestate); i++)
    {
        SDL_Rect rect = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (i == 0)
        { // Cabeza
            // Determinar la textura de la cabeza según la dirección de movimiento
            if (GetSnakeVelY(&gamestate) < 0)
            { // Moviéndose hacia arriba
                SDL_RenderCopy(renderer, snakeTextureUp, NULL, &rect);
            }
            else if (GetSnakeVelY(&gamestate) > 0)
            { // Moviéndose hacia abajo
                SDL_RenderCopy(renderer, snakeTextureDown, NULL, &rect);
            }
            else if (GetSnakeVelX(&gamestate) < 0)
            { // Moviéndose hacia la izquierda
                SDL_RenderCopy(renderer, snakeTextureLeft, NULL, &rect);
            }
            else if (GetSnakeVelX(&gamestate) > 0)
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