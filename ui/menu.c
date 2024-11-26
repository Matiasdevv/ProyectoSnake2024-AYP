#include <SDL2/SDL_ttf.h>
#include "../settings/structs.h"
#include "../settings/settings.h"
#include "score.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void drawMenu(SDL_Renderer *renderer, GameState *gameState)
{
    int SCREEN_WIDTH = GetScreenWidth(gameState);   // Deberías obtener la anchura de la pantalla correctamente
    int SCREEN_HEIGHT = GetScreenHeight(gameState); // Asegúrate de que estos valores sean correctos
    int BORDER_WIDTH = GetBorderWidth(gameState);
    int SEGMENT_SIZE = GetSegmentSize(gameState);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Colores
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0}; // Rojo para la opción seleccionada

    // Fuente
    TTF_Font *font = GetFont(gameState);
    // Saludo
    const char *playerName = GetPlayerName(gameState);                                            // Obtener el nombre del jugador
    char greeting[100];                                                                           // Buffer para el saludo
    snprintf(greeting, sizeof(greeting), "Hola, %s! espero que disfrutes del juego", playerName); // Formar el saludo

    SDL_Surface *greetingSurface = TTF_RenderText_Solid(font, greeting, white);
    SDL_Texture *greetingTexture = SDL_CreateTextureFromSurface(renderer, greetingSurface);
    SDL_Rect greetingRect = {SCREEN_WIDTH / 2 - 300, 50, 600, 50}; // Ajusta las dimensiones y posición según sea necesario
    SDL_RenderCopy(renderer, greetingTexture, NULL, &greetingRect);
    SDL_FreeSurface(greetingSurface);
    SDL_DestroyTexture(greetingTexture);

    // Opción de menú "Jugar"
    SDL_Surface *playSurface = TTF_RenderText_Solid(font, "Jugar", GetMenuOption(gameState) == 0 ? red : white);
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Rect playRect = {SCREEN_WIDTH / 2 - 50, 200, 100, 50};
    SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
    SDL_FreeSurface(playSurface);
    SDL_DestroyTexture(playTexture);

    // Opción de menú "Ranking"
    SDL_Surface *rankingSurface = TTF_RenderText_Solid(font, "Ranking", GetMenuOption(gameState) == 1 ? red : white);
    SDL_Texture *rankingTexture = SDL_CreateTextureFromSurface(renderer, rankingSurface);
    SDL_Rect rankingRect = {SCREEN_WIDTH / 2 - 50, 300, 100, 50};
    SDL_RenderCopy(renderer, rankingTexture, NULL, &rankingRect);
    SDL_FreeSurface(rankingSurface);
    SDL_DestroyTexture(rankingTexture);

    // Opción de menú "Dificultad"
    SDL_Surface *difficultySurface = TTF_RenderText_Solid(font, "Dificultad", GetMenuOption(gameState) == 2 ? red : white);
    SDL_Texture *difficultyTexture = SDL_CreateTextureFromSurface(renderer, difficultySurface);
    SDL_Rect difficultyRect = {SCREEN_WIDTH / 2 - 50, 400, 100, 50};
    SDL_RenderCopy(renderer, difficultyTexture, NULL, &difficultyRect);
    SDL_FreeSurface(difficultySurface);
    SDL_DestroyTexture(difficultyTexture);
    // Opción de menú "Salir"
    SDL_Surface *exitSurface = TTF_RenderText_Solid(font, "Salir", GetMenuOption(gameState) == 3 ? red : white);
    SDL_Texture *exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Rect exitRect = {SCREEN_WIDTH / 2 - 50, 500, 100, 50};
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    SDL_FreeSurface(exitSurface);
    SDL_DestroyTexture(exitTexture);
}

void handleMenuInput(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, SDL_Window *window)
{
    int menuOption = GetMenuOption(gameState); // Obtener la opción del menú actual
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        // Decrementar la opción seleccionada (si no es menor que 0, en cuyo caso va a la opción 2)
        menuOption--;
        if (menuOption < 0)
        {
            menuOption = 3; // Opción "Dificultad" (última opción)
        }
        SetMenuOption(gameState, menuOption); // Actualizar el estado global
        break;
    case SDLK_DOWN:
        // Incrementar la opción seleccionada (si no es mayor que 2, en cuyo caso va a la opción 0)
        menuOption++;
        if (menuOption > 3)
        {
            menuOption = 0; // Opción "Jugar" (primera opción)
        }
        SetMenuOption(gameState, menuOption); // Actualizar el estado global
        break;
    case SDLK_RETURN:
        // Manejar las opciones seleccionadas
        if (menuOption == 0)
        {

            SetMenuOption(gameState, menuOption); // Actualizar el estado global
            SetMenuStatus(gameState, 0);
        }
        else if (menuOption == 1)
        {

            SetMenuOption(gameState, menuOption); // Actualizar el estado global
            SetMenuStatus(gameState, 2);
        }
        else if (menuOption == 2)
        {

            // Implementar la lógica para cambiar la dificultad
            SetMenuOption(gameState, menuOption); // Actualizar el estado global
            SetMenuStatus(gameState, 3);
        }
        else if (menuOption == 3)
        {

            // Implementar la lógica para cambiar la dificultad
            SetMenuOption(gameState, menuOption); // Actualizar el estado global
            SetMenuStatus(gameState, 4);
            exitGame(gameState, renderer, window);
        }
        break;
    }
}

void drawDifficultyMenu(SDL_Renderer *renderer, GameState *gameState)
{
    int SCREEN_WIDTH = GetScreenWidth(gameState);
    int SCREEN_HEIGHT = GetScreenHeight(gameState);
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0}; // Rojo para la opción seleccionada
    TTF_Font *font = GetFont(gameState);

    // Dificultad "Fácil"
    SDL_Surface *easySurface = TTF_RenderText_Solid(font, "Facil", GetMenuOption(gameState) == 0 ? red : white);
    SDL_Texture *easyTexture = SDL_CreateTextureFromSurface(renderer, easySurface);
    SDL_Rect easyRect = {SCREEN_WIDTH / 2 - 50, 200, 100, 50};
    SDL_RenderCopy(renderer, easyTexture, NULL, &easyRect);
    SDL_FreeSurface(easySurface);
    SDL_DestroyTexture(easyTexture);

    // Dificultad "Normal"
    SDL_Surface *normalSurface = TTF_RenderText_Solid(font, "Normal", GetMenuOption(gameState) == 1 ? red : white);
    SDL_Texture *normalTexture = SDL_CreateTextureFromSurface(renderer, normalSurface);
    SDL_Rect normalRect = {SCREEN_WIDTH / 2 - 50, 300, 100, 50};
    SDL_RenderCopy(renderer, normalTexture, NULL, &normalRect);
    SDL_FreeSurface(normalSurface);
    SDL_DestroyTexture(normalTexture);

    // Dificultad "Difícil"
    SDL_Surface *hardSurface = TTF_RenderText_Solid(font, "Dificil", GetMenuOption(gameState) == 2 ? red : white);
    SDL_Texture *hardTexture = SDL_CreateTextureFromSurface(renderer, hardSurface);
    SDL_Rect hardRect = {SCREEN_WIDTH / 2 - 50, 400, 100, 50};
    SDL_RenderCopy(renderer, hardTexture, NULL, &hardRect);
    SDL_FreeSurface(hardSurface);
    SDL_DestroyTexture(hardTexture);
}

void handleDifficultyInput(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, SDL_Window *window)
{
    int menuOption = GetMenuOption(gameState); // Obtener la opción del menú actual
    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        // Decrementar la opción seleccionada
        menuOption--;
        if (menuOption < 0)
        {
            menuOption = 2; // Opción "Difícil" (última opción)
        }
        SetMenuOption(gameState, menuOption); // Actualizar el estado global
        break;
    case SDLK_DOWN:
        // Incrementar la opción seleccionada
        menuOption++;
        if (menuOption > 2)
        {
            menuOption = 0; // Opción "Fácil" (primera opción)
        }
        SetMenuOption(gameState, menuOption); // Actualizar el estado global
        break;
    case SDLK_RETURN:
        // Manejar las opciones seleccionadas
        if (menuOption == 0)
        {

            SetDiffStatus(gameState, menuOption); // Guardar dificultad "facil"
            SetDelayStatus(gameState, 300);
            SetMenuStatus(gameState, 1); // Cambiar el estado del menú
        }
        else if (menuOption == 1)
        {

            SetDiffStatus(gameState, menuOption); // Guardar dificultad "normal"
            SetDelayStatus(gameState, 200);
            SetMenuStatus(gameState, 1); // Cambiar el estado del menú
        }
        else if (menuOption == 2)
        {

            SetDiffStatus(gameState, menuOption); // Guardar dificultad "dificil"
            SetDelayStatus(gameState, 100);
            SetMenuStatus(gameState, 1); // Cambiar el estado del menú
        }
        break;
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
    while (fgets(line, sizeof(line), file) != NULL)
    {

        if (sscanf(line, "%49[^,], %d, %49[^\n]", player.name, &player.score, player.difficulty) == 3)
        {

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
            if (rowCounter >= 5)
            {                             // Ajusta 5 al número máximo de jugadores por fila
                rowCounter = 0;           // Reiniciar el contador de filas
                yOffset += rowHeight * 5; // Aumentar el desplazamiento Y para la siguiente fila
            }

            // Si ya tenemos suficiente espacio en pantalla, detenemos el bucle (limitamos el número de jugadores a mostrar)
            if (yOffset + rowHeight * (rowCounter + 1) > SCREEN_HEIGHT - 100)
            {
                break; // Evitar dibujar fuera de la pantalla
            }
        }
        else
        {
            // Si no se pudieron leer correctamente los tres elementos, muestra un mensaje de error
            printf("Error al leer los datos de la línea: %s\n", line);
        }
    }

    // **Dibujar la nota de "Presionar para volver"**
    SDL_Surface *exitSurface = TTF_RenderText_Solid(font, "Presionar enter para volver", white);
    SDL_Texture *exitTexture = SDL_CreateTextureFromSurface(renderer, exitSurface);
    SDL_Rect exitRect = {SCREEN_WIDTH / 2 - exitSurface->w / 2, SCREEN_HEIGHT - 100, exitSurface->w, exitSurface->h};
    SDL_RenderCopy(renderer, exitTexture, NULL, &exitRect);
    SDL_FreeSurface(exitSurface);
    SDL_DestroyTexture(exitTexture);

    // Cerrar el archivo
    fclose(file);
}

void handleRankingInput(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, SDL_Window *window)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_RETURN: // Si presionamos Enter en el botón "Volver"

        // Cambiar el estado del menú para volver al menú principal
        SetMenuStatus(gameState, 1); // Volver al menú principal
        break;

    case SDLK_ESCAPE: // Si presionamos Escape, también volvemos al menú principal

        // Cambiar el estado del menú para volver al menú principal
        SetMenuStatus(gameState, 1); // Volver al menú principal
        break;

    case SDL_QUIT:
        // Si el usuario cierra la ventana, salir del juego
        SetRunningStatus(gameState, 0);
        break;
    }
}

void showMenu(SDL_Event event, GameState *gameState, SDL_Renderer *renderer, SDL_Window *window)
{

    // Mostrar el menú principal
    while (GetRunningStatus(gameState) == 1 && GetMenuStatus(gameState) == 1)
    {
        SDL_RenderClear(renderer);

        // Manejar los eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SetMenuOption(gameState, 0);
                SetRunningStatus(gameState, 0);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handleMenuInput(event, gameState, renderer, window); // Manejar la entrada del menú
            }
        }

        drawMenu(renderer, gameState); // Dibujar el menú principal

        SDL_RenderPresent(renderer);
    }

    // Mostrar el menú de dificultad
    while (GetRunningStatus(gameState) == 1 && GetMenuStatus(gameState) == 3)
    {
        SDL_RenderClear(renderer);

        // Manejar los eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SetMenuOption(gameState, 0);
                SetRunningStatus(gameState, 0);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handleDifficultyInput(event, gameState, renderer, window); // Manejar la entrada de dificultad
            }
        }

        drawDifficultyMenu(renderer, gameState); // Dibujar el menú de dificultad

        SDL_RenderPresent(renderer);
    }

    // Mostrar el ranking
    while (GetRunningStatus(gameState) == 1 && GetMenuStatus(gameState) == 2)
    {
        SDL_RenderClear(renderer);

        // Manejar los eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SetMenuOption(gameState, 0);
                SetRunningStatus(gameState, 0);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                handleRankingInput(event, gameState, renderer, window); // Manejar la entrada de ranking
            }
        }

        drawRanking(renderer, gameState); // Dibujar el ranking

        SDL_RenderPresent(renderer);
    }
}
