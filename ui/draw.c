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

void drawRanking(SDL_Renderer *renderer, GameState *gameState)
{
    int SCREEN_WIDTH = GetScreenWidth(gameState);   // Obtener la anchura de la pantalla
    int SCREEN_HEIGHT = GetScreenHeight(gameState); // Obtener la altura de la pantalla
    int BORDER_WIDTH = GetBorderWidth(gameState);   // Obtener el ancho del borde
    int SEGMENT_SIZE = GetSegmentSize(gameState);   // Obtener el tamaño del segmento

    FILE *file = fopen("data/scores.txt", "r"); // Abrir el archivo en modo de lectura

    // Verificar si el archivo se abrió correctamente
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    Player player;
    int xOffset[3];                         // Array para las posiciones horizontales de las 3 columnas
    xOffset[0] = SCREEN_WIDTH / 4 - 50;     // Columna 1: Nombre (centro de la primera columna)
    xOffset[1] = SCREEN_WIDTH / 2 - 50;     // Columna 2: Puntuación (centro de la segunda columna)
    xOffset[2] = 3 * SCREEN_WIDTH / 4 - 50; // Columna 3: Dificultad (centro de la tercera columna)

    int yOffset = 150;  // Desplazamiento inicial en el eje Y
    int rowHeight = 50; // Distancia vertical entre filas (ajustable)

    int rowCounter = 0; // Contador de filas
    // Definir los colores
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0}; // Rojo para la opción seleccionada

    // Fuente
    TTF_Font *font = GetFont(gameState);

    // **Dibujar la opción "Volver" (última opción de menú)**
    SDL_Surface *rankingSurface = TTF_RenderText_Solid(font, "RANKING", red);
    SDL_Texture *rankingTexture = SDL_CreateTextureFromSurface(renderer, rankingSurface);
    SDL_Rect rankingRect = {SCREEN_WIDTH / 2 - rankingSurface->w / 2, 50, rankingSurface->w, rankingSurface->h};
    SDL_RenderCopy(renderer, rankingTexture, NULL, &rankingRect);
    SDL_FreeSurface(rankingSurface);
    SDL_DestroyTexture(rankingTexture);

    // **Dibujar el nombre del jugador en la primera columna**
    SDL_Surface *nameSurface = TTF_RenderText_Solid(font, "Nombre", white);
    SDL_Texture *nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
    SDL_Rect nameRect = {xOffset[0], 100, nameSurface->w, nameSurface->h};
    SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);
    SDL_FreeSurface(nameSurface);
    SDL_DestroyTexture(nameTexture);

    // **Dibujar la puntuación del jugador en la segunda columna**

    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, "Puntuacion", white);
    SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
    SDL_Rect scoreRect = {xOffset[1], 100, scoreSurface->w, scoreSurface->h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
    SDL_FreeSurface(scoreSurface);
    SDL_DestroyTexture(scoreTexture);

    // **Dibujar la dificultad del jugador en la tercera columna**
    SDL_Surface *difficultySurface = TTF_RenderText_Solid(font, "Dificultad", white);
    SDL_Texture *difficultyTexture = SDL_CreateTextureFromSurface(renderer, difficultySurface);
    SDL_Rect difficultyRect = {xOffset[2], 100, difficultySurface->w, difficultySurface->h};
    SDL_RenderCopy(renderer, difficultyTexture, NULL, &difficultyRect);
    SDL_FreeSurface(difficultySurface);
    SDL_DestroyTexture(difficultyTexture);

  char line[256]; // Buffer para almacenar cada línea del archivo
while (fgets(line, sizeof(line), file) != NULL) {

    if (sscanf(line, "%49[^,], %d, %49[^\n]", player.name, &player.score, player.difficulty) == 3) {
        
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Fondo negro para cada texto

        // **Dibujar el nombre del jugador en la primera columna**
        SDL_Surface *nameSurface = TTF_RenderText_Solid(font, player.name, white);
        SDL_Texture *nameTexture = SDL_CreateTextureFromSurface(renderer, nameSurface);
        SDL_Rect nameRect = {xOffset[0], yOffset + rowHeight * rowCounter, nameSurface->w, nameSurface->h};
        SDL_RenderCopy(renderer, nameTexture, NULL, &nameRect);
        SDL_FreeSurface(nameSurface);
        SDL_DestroyTexture(nameTexture);

        // **Dibujar la puntuación del jugador en la segunda columna**
        char scoreText[50];
        sprintf(scoreText, "%d", player.score); // Convertir el score a texto

        SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText, white);
        SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer, scoreSurface);
        SDL_Rect scoreRect = {xOffset[1], yOffset + rowHeight * rowCounter, scoreSurface->w, scoreSurface->h};
        SDL_RenderCopy(renderer, scoreTexture, NULL, &scoreRect);
        SDL_FreeSurface(scoreSurface);
        SDL_DestroyTexture(scoreTexture);

        // **Dibujar la dificultad del jugador en la tercera columna**
        SDL_Surface *difficultySurface = TTF_RenderText_Solid(font, player.difficulty, white);
        SDL_Texture *difficultyTexture = SDL_CreateTextureFromSurface(renderer, difficultySurface);
        SDL_Rect difficultyRect = {xOffset[2], yOffset + rowHeight * rowCounter, difficultySurface->w, difficultySurface->h};
        SDL_RenderCopy(renderer, difficultyTexture, NULL, &difficultyRect);
        SDL_FreeSurface(difficultySurface);
        SDL_DestroyTexture(difficultyTexture);

        // Incrementar el contador de filas
        rowCounter++;

        // Si llegamos al final de la fila, reiniciamos el contador y desplazamos a la siguiente fila
        if (rowCounter >= 5) { // Ajusta 5 al número máximo de jugadores por fila
            rowCounter = 0;           // Reiniciar el contador de filas
            yOffset += rowHeight * 5; // Aumentar el desplazamiento Y para la siguiente fila
        }

        // Si ya tenemos suficiente espacio en pantalla, detenemos el bucle (limitamos el número de jugadores a mostrar)
        if (yOffset + rowHeight * (rowCounter + 1) > SCREEN_HEIGHT - 100) {
            break; // Evitar dibujar fuera de la pantalla
        }
    } else {
        // Si no se pudieron leer correctamente los tres elementos, muestra un mensaje de error
        printf("Error al leer los datos de la línea: %s\n", line);
    }
}







    // **Dibujar la opción "Volver" (última opción de menú)**
    SDL_Surface *exitSurface = TTF_RenderText_Solid(font, "Volver", white);
    SDL_Texture *exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Rect exitRect = {SCREEN_WIDTH / 2 - exitSurface->w / 2, SCREEN_HEIGHT - 100, exitSurface->w, exitSurface->h};
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    SDL_FreeSurface(exitSurface);
    SDL_DestroyTexture(exitTexture);

    // Cerrar el archivo
    fclose(file);
}
