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
        {
            int prevX = snake[i - 1].x, prevY = snake[i - 1].y;
            int nextX = (i < snakeLength - 1) ? snake[i + 1].x : snake[i].x;
            int nextY = (i < snakeLength - 1) ? snake[i + 1].y : snake[i].y;

            // Determinar el tipo de giro
            if (prevY < snake[i].y && nextX > snake[i].x || nextY < snake[i].y && prevX > snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureDownRight(), NULL, &rect);
            }
            else if (prevY < snake[i].y && nextX < snake[i].x || nextY < snake[i].y && prevX < snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureDownLeft(), NULL, &rect);
            }
            else if (prevY > snake[i].y && nextX > snake[i].x || nextY > snake[i].y && prevX > snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureUpRight(), NULL, &rect);
            }
            else if (prevY > snake[i].y && nextX < snake[i].x || nextY > snake[i].y && prevX < snake[i].x)
            {
                SDL_RenderCopy(renderer, getSnakeTurnTextureUpLeft(), NULL, &rect);
            }
            else
            {
                if (snake[i].x == snake[i - 1].x)
                {
                    SDL_RenderCopy(renderer, snakeBodyTextureVertical, NULL, &rect);
                }
                else
                {
                    SDL_RenderCopy(renderer, snakeBodyTextureHorizontal, NULL, &rect);
                }
            }
        }
    }
}

