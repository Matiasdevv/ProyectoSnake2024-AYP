#include "../settings/structs.h"
#include "../settings/settings.h"

void drawSnake(SDL_Renderer *renderer, Segment *snake, GameState *gamestate)
{
    int snakeLength = GetSnakeLength(gamestate);

    // Mover la serpiente (actualizar posiciones)
    for (int i = snakeLength - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1]; // Mover cada segmento hacia el anterior
    }
    snake[0].x += GetSnakeVelX(gamestate); // Actualizar la posición de la cabeza (x)
    snake[0].y += GetSnakeVelY(gamestate); // Actualizar la posición de la cabeza (y)

    // Renderizar la serpiente (dibujar segmentos)
    for (int i = 0; i < snakeLength; i++)
    {
        SDL_Rect rect = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (i == 0)
        { // Renderizar la cabeza
            if (GetSnakeVelY(gamestate) < 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureUp(), NULL, &rect);
            }
            else if (GetSnakeVelY(gamestate) > 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureDown(), NULL, &rect);
            }
            else if (GetSnakeVelX(gamestate) < 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureLeft(), NULL, &rect);
            }
            else if (GetSnakeVelX(gamestate) > 0)
            {
                SDL_RenderCopy(renderer, getSnakeTextureRight(), NULL, &rect);
            }
        }
        else
        { // Renderizar el cuerpo
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
