#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../settings/structs.h"
#include "../settings/settings.h"
#include <SDL2/SDL_ttf.h>

// Dibujar el puntaje
void drawScore(SDL_Renderer *renderer, GameState *gamestate)
{
    int score = GetScore(gamestate);
    // Preparar el texto del puntaje
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score); // Convierte el puntaje a cadena de texto

    // Renderizar el texto del puntaje a una superficie
    TTF_Font *font = GetFont(gamestate);
    if (!font)
    {
        printf("error al crear puntaje");
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid((TTF_Font *)font, scoreText, getTextColor());
    if (!textSurface)
    {
        printf("Error al crear la superficie del texto: %s\n", TTF_GetError());
        return;
    }

    // Crear textura a partir de la superficie del texto
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture)
    {
        printf("Error al crear la textura del texto: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    // Posicionar el puntaje en pantalla
    SDL_Rect textRect = {GetBorderWidth(gamestate), GetBorderWidth(gamestate) - textSurface->h, textSurface->w, textSurface->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect); // Renderiza el texto

    // Limpiar memoria de superficie y textura
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

// Función para capturar el nombre
void EnterName(SDL_Renderer *renderer, GameState *gamestate)
{
    int SCREEN_WIDTH = GetScreenWidth(gamestate);
    int SCREEN_HEIGHT = GetScreenHeight(gamestate);
    int maxLen = sizeof(gamestate->player.name) - 1;

    SDL_Event event;
    int done = 0;
    int index = 0;

    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Rect inputRect = {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, 200, 100};

    char title[50] = "Por favor, ingrese su nombre";
    SDL_Rect titleRect = {SCREEN_WIDTH / 2 - 200, 50, 400, 50};

    char *name = gamestate->player.name;
    name[0] = '\0'; // Asegurar que el nombre comience vacío

    while (!done)
    {
        // Limpiar la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Renderizar el texto superior
        SDL_Surface *titleSurface = TTF_RenderText_Blended(GetFont(gamestate), title, textColor);
        if (titleSurface)
        {
            SDL_Texture *titleTexture = SDL_CreateTextureFromSurface(renderer, titleSurface);
            if (titleTexture)
            {
                titleRect.w = titleSurface->w;
                titleRect.h = titleSurface->h;
                SDL_RenderCopy(renderer, titleTexture, NULL, &titleRect);
                SDL_DestroyTexture(titleTexture);
            }
            SDL_FreeSurface(titleSurface);
        }

        // Renderizar el texto ingresado
        SDL_Surface *inputSurface = TTF_RenderText_Blended(GetFont(gamestate), name, textColor);
        if (inputSurface)
        {
            SDL_Texture *inputTexture = SDL_CreateTextureFromSurface(renderer, inputSurface);
            if (inputTexture)
            {
                inputRect.w = inputSurface->w;
                inputRect.h = inputSurface->h;
                SDL_RenderCopy(renderer, inputTexture, NULL, &inputRect);
                SDL_DestroyTexture(inputTexture);
            }
            SDL_FreeSurface(inputSurface);
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(200);

        // Manejar eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done = 1;
                SetRunningStatus(gamestate, 0);
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    done = 1;
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE && index > 0)
                {
                    name[--index] = '\0';
                }
                else if (index < maxLen)
                {
                    SDL_Keycode key = event.key.keysym.sym;
                    SDL_Keymod mod = SDL_GetModState();

                    // Excluir la coma (,) de las teclas válidas
                    if (key == SDLK_COMMA)
                    {
                        continue; // Ignorar la coma
                    }

                    // Solo procesar teclas alfabéticas y numéricas
                    if (key >= SDLK_a && key <= SDLK_z)
                    {
                        // Si Shift o Caps Lock están activados, convertir a mayúscula
                        if ((mod & KMOD_SHIFT) || (mod & KMOD_CAPS))
                        {
                            name[index++] = key - ('a' - 'A');
                        }
                        else
                        {
                            name[index++] = key;
                        }
                    }
                    else if (key >= SDLK_0 && key <= SDLK_9)
                    {
                        // Números no cambian con Shift/Caps Lock
                        name[index++] = key;
                    }
                    else if (key >= SDLK_SPACE && key <= SDLK_SLASH)
                    {
                        // Procesar caracteres especiales
                        if (mod & KMOD_SHIFT)
                        {
                            switch (key)
                            {
                            case SDLK_1: name[index++] = '!'; break;
                            case SDLK_2: name[index++] = '@'; break;
                            case SDLK_3: name[index++] = '#'; break;
                            case SDLK_4: name[index++] = '$'; break;
                            case SDLK_5: name[index++] = '%'; break;
                            case SDLK_6: name[index++] = '^'; break;
                            case SDLK_7: name[index++] = '&'; break;
                            case SDLK_8: name[index++] = '*'; break;
                            case SDLK_9: name[index++] = '('; break;
                            case SDLK_0: name[index++] = ')'; break;
                            case SDLK_MINUS: name[index++] = '_'; break;
                            case SDLK_EQUALS: name[index++] = '+'; break;
                            default: break; // Otros caracteres
                            }
                        }
                        else
                        {
                            name[index++] = key;
                        }
                    }
                    name[index] = '\0'; // Asegurarse de terminar el string
                }
            }
        }
    }
}


int CompareScores(const void *a, const void *b)
{
    Player *entryA = (Player *)a;
    Player *entryB = (Player *)b;
    return entryB->score - entryA->score; // Ordenar de mayor a menor
}

// Función para guardar el puntaje y ordenar la tabla
void SaveScore(GameState *gamestate, SDL_Renderer *renderer)
{
    char *playerName = GetPlayerName(gamestate);
    int maxPlayers = 10; // Máximo número de jugadores
    char difficulty[10]; // Variable para guardar la dificultad ("facil", "normal", "dificil")

    // Obtén el puntaje actual
    int score = GetScore(gamestate);

    // Obtener dificultad
    int difficultyLevel = GetDiffStatus(gamestate); // Obtener nivel de dificultad
    switch (difficultyLevel)
    {
    case 0:
        strcpy(difficulty, "facil");
        break;
    case 1:
        strcpy(difficulty, "normal");
        break;
    default:
        strcpy(difficulty, "dificil");
        break;
    }

    // Leer los datos existentes
    char buffer[100];   // Buffer temporal para leer líneas
    Player entries[11]; // Máximo permitido + 1 para nuevo jugador
    int count = 0;
    FILE *file = fopen("data/scores.txt", "r");
    if (file)
    {
        while (fgets(buffer, sizeof(buffer), file))
        {
            // Ignorar líneas vacías y validar el formato correcto
            if (strlen(buffer) > 1 && sscanf(buffer, "%49[^,], %d, %9s", entries[count].name, &entries[count].score, entries[count].difficulty) == 3)
            {
                count++;
                if (count >= maxPlayers) // Limitar lectura a 10 jugadores
                    break;
            }
        }
        fclose(file);
    }

    // Agregar el nuevo jugador
    if (count < 11) // Si hay espacio, agregar nuevo jugador
    {
        strncpy(entries[count].name, playerName, sizeof(entries[count].name) - 1);
        entries[count].name[sizeof(entries[count].name) - 1] = '\0'; // Asegurar terminación
        entries[count].score = score;
        strncpy(entries[count].difficulty, difficulty, sizeof(entries[count].difficulty) - 1);
        entries[count].difficulty[sizeof(entries[count].difficulty) - 1] = '\0'; // Asegurar terminación
        count++;
    }

    // Ordenar por puntaje
    qsort(entries, count, sizeof(Player), CompareScores);

    // Truncar la lista a un máximo de 10 jugadores
    if (count > maxPlayers)
        count = maxPlayers;

    // Guardar la lista ordenada, sobrescribiendo el archivo si es necesario
    file = fopen("data/scores.txt", "w");
    if (file)
    {
        for (int i = 0; i < count; i++)
        {
            fprintf(file, "%s, %d, %s\n", entries[i].name, entries[i].score, entries[i].difficulty);

        }
        fclose(file);
    }
    else
    {
        printf("Error: No se pudo guardar el puntaje.\n");
    }
}
