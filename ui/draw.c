#include "../settings/structs.h"
#include "../settings/settings.h"

void drawSnake(SDL_Renderer *renderer, Segment *snake, GameState *gamestate)
{
    for (int i = 0; i < GetSnakeLength(gamestate); i++)
    {
        SDL_Rect rect = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};
        for (int i = GetSnakeLength(gamestate) - 1; i > 0; i--)
        {
            snake[i] = snake[i - 1];
        }

        snake[0].x += GetSnakeVelX(gamestate);
        snake[0].y += GetSnakeVelY(gamestate);

        if (i == 0)
        { // Cabeza
            // Determinar la textura de la cabeza según la dirección de movimiento
            if (GetSnakeVelY(gamestate) < 0)
            { // Moviéndose hacia arriba
                SDL_RenderCopy(renderer, getSnakeTextureUp(), NULL, &rect);
            }
            else if (GetSnakeVelY(gamestate) > 0)
            { // Moviéndose hacia abajo
                SDL_RenderCopy(renderer, getSnakeTextureDown(), NULL, &rect);
            }
            else if (GetSnakeVelX(gamestate) < 0)
            { // Moviéndose hacia la izquierda
                SDL_RenderCopy(renderer, getSnakeTextureLeft(), NULL, &rect);
            }
            else if (GetSnakeVelX(gamestate) > 0)
            { // Moviéndose hacia la derecha
                SDL_RenderCopy(renderer, getSnakeTextureRight(), NULL, &rect);
            }
        }
        else
        { // Cuerpo
            // Determinar la textura del cuerpo según la dirección del segmento actual
            if (snake[i].x == snake[i - 1].x)
            { // Movimiento vertical
                SDL_RenderCopy(renderer, getSnakeBodyTextureVertical(), NULL, &rect);
            }
            else
            { // Movimiento horizontal
                SDL_RenderCopy(renderer, getSnakeBodyTextureHorizontal(), NULL, &rect);
            }
        }
    }
}