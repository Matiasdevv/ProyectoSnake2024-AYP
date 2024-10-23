#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define SEGMENT_SIZE 20
#define BORDER_WIDTH 20
#define MAX_SNAKE_LENGTH 100
int menuOption = 0; // Para rastrear la opción seleccionada
int onMenu = 1;     // Indica si estamos en el menú

int score = 0;
TTF_Font *font = NULL;
SDL_Color textColor = {255, 255, 255}; // Color blanco

typedef struct {
    int x, y, w, h;
} Segment;

SDL_Texture *snakeBodyTexture;
SDL_Texture *snakeTexture;
SDL_Texture *foodTexture;
Segment snake[MAX_SNAKE_LENGTH];
Segment food;
int snakeLength = 2;
int running = 1;
int velX = SEGMENT_SIZE; // Velocidad en X
int velY = 0; // Velocidad en Y
SDL_Event event;


void drawMenu(SDL_Renderer *renderer, TTF_Font *font) {
    // Colores
    SDL_Color white = {255, 255, 255};
    SDL_Color red = {255, 0, 0};

    // Opción de menú "Jugar"
    SDL_Surface *playSurface = TTF_RenderText_Solid(font, "Jugar", menuOption == 0 ? red : white);
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Rect playRect = {SCREEN_WIDTH / 2 - 50, 200, 100, 50};
    SDL_RenderCopy(renderer, playTexture, NULL, &playRect);
    SDL_FreeSurface(playSurface);
    SDL_DestroyTexture(playTexture);

    // Opción de menú "Ranking"
    SDL_Surface *rankingSurface = TTF_RenderText_Solid(font, "Ranking", menuOption == 1 ? red : white);
    SDL_Texture *rankingTexture = SDL_CreateTextureFromSurface(renderer, rankingSurface);
    SDL_Rect rankingRect = {SCREEN_WIDTH / 2 - 50, 300, 100, 50};
    SDL_RenderCopy(renderer, rankingTexture, NULL, &rankingRect);
    SDL_FreeSurface(rankingSurface);
    SDL_DestroyTexture(rankingTexture);

    // Opción de menú "Dificultad"
    SDL_Surface *difficultySurface = TTF_RenderText_Solid(font, "Dificultad", menuOption == 2 ? red : white);
    SDL_Texture *difficultyTexture = SDL_CreateTextureFromSurface(renderer, difficultySurface);
    SDL_Rect difficultyRect = {SCREEN_WIDTH / 2 - 50, 400, 100, 50};
    SDL_RenderCopy(renderer, difficultyTexture, NULL, &difficultyRect);
    SDL_FreeSurface(difficultySurface);
    SDL_DestroyTexture(difficultyTexture);
}


void handleMenuInput(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            menuOption--;
            if (menuOption < 0) {
                menuOption = 2; // Volver a la última opción
            }
            break;
        case SDLK_DOWN:
            menuOption++;
            if (menuOption > 2) {
                menuOption = 0; // Volver a la primera opción
            }
            break;
        case SDLK_RETURN:
            if (menuOption == 0) {
                // Opción "Jugar"
                onMenu = 0; // Salimos del menú y empezamos el juego
            } else if (menuOption == 1) {
                // Opción "Ranking"
                // Aquí puedes implementar la lógica para mostrar el ranking
                printf("Mostrando ranking...\n");
            } else if (menuOption == 2) {
                // Opción "Dificultad"
                // Aquí puedes implementar la lógica para cambiar la dificultad
                printf("Seleccionando dificultad...\n");
            }
            break;
    }
}

void initializeSnake() {
    snake[0].x = SCREEN_WIDTH / 2; // Inicializa en el centro de la pantalla
    snake[0].y = SCREEN_HEIGHT / 2;
    snake[0].w = SEGMENT_SIZE;
    snake[0].h = SEGMENT_SIZE;

    // Inicializa el segundo segmento justo detrás
    snake[1].x = snake[0].x - SEGMENT_SIZE; 
    snake[1].y = snake[0].y; 
    snake[1].w = SEGMENT_SIZE;
    snake[1].h = SEGMENT_SIZE;
}

void initializeFood() {
    food.x = (rand() % 39) * SEGMENT_SIZE;
    food.y = (rand() % 29) * SEGMENT_SIZE;
    food.w = SEGMENT_SIZE;
    food.h = SEGMENT_SIZE;
}

void drawSnake(SDL_Renderer *renderer) {
    for (int i = 0; i < snakeLength; i++) {
        SDL_Rect rect = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};
        if (i == 0) {
            // Usar la textura de la cabeza para el primer segmento
            SDL_RenderCopy(renderer, snakeTexture, NULL, &rect);
        } else {
            // Usar la textura del cuerpo para los demás segmentos
            SDL_RenderCopy(renderer, snakeBodyTexture, NULL, &rect);
        }
    }
}
// Nueva función para dibujar los bordes del mapa
void drawMapBorders(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Color verde

    // Borde superior
    SDL_Rect topBorder = {0, 0, SCREEN_WIDTH, BORDER_WIDTH};
    SDL_RenderFillRect(renderer, &topBorder);

    // Borde inferior
    SDL_Rect bottomBorder = {0, SCREEN_HEIGHT - BORDER_WIDTH, SCREEN_WIDTH, BORDER_WIDTH};
    SDL_RenderFillRect(renderer, &bottomBorder);

    // Borde izquierdo
    SDL_Rect leftBorder = {0, 0, BORDER_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &leftBorder);

    // Borde derecho
    SDL_Rect rightBorder = {SCREEN_WIDTH - BORDER_WIDTH, 0, BORDER_WIDTH, SCREEN_HEIGHT};
    SDL_RenderFillRect(renderer, &rightBorder);
}

void snakeMovement(SDL_Event event) {
    switch (event.key.keysym.sym) {
        case SDLK_UP:
            if (velY == 0) { // Solo puede ir hacia arriba si no está yendo hacia arriba o abajo
                velX = 0;
                velY = -SEGMENT_SIZE;
            }
            break;
        case SDLK_DOWN:
            if (velY == 0) { // Solo puede ir hacia abajo si no está yendo hacia arriba o abajo
                velX = 0;
                velY = SEGMENT_SIZE;
            }
            break;
        case SDLK_LEFT:
            if (velX == 0) { // Solo puede ir hacia la izquierda si no está yendo hacia la izquierda o derecha
                velX = -SEGMENT_SIZE;
                velY = 0;
            }
            break;
        case SDLK_RIGHT:
            if (velX == 0) { // Solo puede ir hacia la derecha si no está yendo hacia la izquierda o derecha
                velX = SEGMENT_SIZE;
                velY = 0;
            }
            break;
    }
}


void setSnakeLimits() {
    if (snake[0].x < BORDER_WIDTH) {
        snake[0].x = BORDER_WIDTH;
    } else if (snake[0].x >= SCREEN_WIDTH - BORDER_WIDTH) {
        snake[0].x = SCREEN_WIDTH - BORDER_WIDTH - SEGMENT_SIZE;
    }
    if (snake[0].y < BORDER_WIDTH) {
        snake[0].y = BORDER_WIDTH;
    } else if (snake[0].y >= SCREEN_HEIGHT - BORDER_WIDTH) {
        snake[0].y = SCREEN_HEIGHT - BORDER_WIDTH - SEGMENT_SIZE;
    }
}

void drawFood(SDL_Renderer *renderer) {
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};
    SDL_RenderCopy(renderer, foodTexture, NULL, &foodRect);
}

void snakeFoodCollition() {
    // Detección de colisión entre la serpiente y la comida
    SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
    SDL_Rect foodRect = {food.x, food.y, food.w, food.h};
    
    if (SDL_HasIntersection(&snakeHead, &foodRect)) {
        int random_number = (rand() % 39) * SEGMENT_SIZE; // generar número aleatorio dentro de la cuadrícula
        int random_number2 = (rand() % 29) * SEGMENT_SIZE;

         if (random_number == 0) {
            while (random_number == 0) {
                random_number = (rand() % 39) * SEGMENT_SIZE; // seguir generando números hasta que sea distinto de 0
            }
        }

        // Verificar que el número no sea 0 para random_number2
        if (random_number2 == 0) {
            while (random_number2 == 0) {
                random_number2 = (rand() % 29) * SEGMENT_SIZE; // seguir generando números hasta que sea distinto de 0
            }
        }


        food.x = random_number;  // actualizar la posición x de la comida
        food.y = random_number2;  // actualizar la posición y de la comida
        snakeLength++;      // aumentar el tamaño de la serpiente
        score++; // Aumenta el puntaje cuando come comida
    }
}

// Función para verificar colisión del cuerpo de la serpiente
void snakeBodyCollition() {
    // Verifica si la cabeza colisiona con algún segmento del cuerpo
    for (int i = 1; i < snakeLength; i++) {
        SDL_Rect snakeHead = {snake[0].x, snake[0].y, snake[0].w, snake[0].h};
        SDL_Rect snakeBodySegment = {snake[i].x, snake[i].y, snake[i].w, snake[i].h};

        if (SDL_HasIntersection(&snakeHead, &snakeBodySegment)) {
            running = 0; // Termina el juego si hay colisión
        }
    }
}

void drawScore(SDL_Renderer *renderer) {
    char scoreText[20];
    sprintf(scoreText, "Score: %d", score);  // Convierte el puntaje a una cadena

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    if (textSurface == NULL) {
        printf("Error al crear la superficie del texto: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (textTexture == NULL) {
        printf("Error al crear la textura del texto: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);
        return;
    }

    SDL_Rect textRect;
    textRect.x = BORDER_WIDTH;  // Posición X, un poco desplazado desde el borde izquierdo
    textRect.y = BORDER_WIDTH - textSurface->h + 6;  // Posición Y, justo arriba del borde verde
    textRect.w = textSurface->w;
    textRect.h = textSurface->h;

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);  // Renderiza el texto

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}



int fileExists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));
    initializeSnake();// Inicializar serpiente
    initializeFood(); // Inicializar la comida

   // Inicializar SDL y TTF
    if (SDL_Init(SDL_INIT_VIDEO) < 0 || TTF_Init() < 0) {
        printf("Error al inicializar SDL o TTF: %s\n", SDL_GetError());
        return 1;
    }
    
    font = TTF_OpenFont("ComicSansMS3.ttf", 24);
if (font == NULL) {
    printf("Error al cargar la fuente: %s\n", TTF_GetError());
    return 1;
}



    SDL_Window *window = SDL_CreateWindow("Snake Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Cargar la fuente ComicSansMS3.ttf para el menú y el score
    TTF_Font *font = TTF_OpenFont("ComicSansMS3.ttf", 24); // Tamaño 24 para el menú y el score
    if (!font) {
        printf("Error al cargar la fuente ComicSansMS3.ttf: %s\n", TTF_GetError());
        return 1;
    }

    if (!renderer) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    
while (onMenu) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                onMenu = 0;
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                handleMenuInput(event); // Manejar la entrada del menú
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMenu(renderer, font); // Dibujar el menú

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    // Aquí empieza el juego después de que se sale del menú
    initializeSnake();
    initializeFood();

    if (!fileExists("snake_sprite.bmp")) {
        printf("El archivo snake_sprite.bmp no existe.\n");
        return 1;
    }

    if (!fileExists("food_sprite.bmp")) {
        printf("El archivo food_sprite.bmp no existe.\n");
        return 1;
    }

    SDL_Surface *snakeSurface = SDL_LoadBMP("snake_sprite.bmp");
    if (!snakeSurface) {
        printf("Error al cargar la textura de la serpiente: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *foodSurface = SDL_LoadBMP("food_sprite.bmp");
    if (!foodSurface) {
        printf("Error al cargar la textura de la comida: %s\n", SDL_GetError());
        return 1;
    }
    SDL_Surface *snakeBodySurface = SDL_LoadBMP("snake_body.bmp"); // Archivo de textura del cuerpo
    if (!snakeBodySurface) {
        printf("Error al cargar snake_body.bmp: %s\n", SDL_GetError());
        return 1;
    }
    snakeBodyTexture = SDL_CreateTextureFromSurface(renderer, snakeBodySurface);
    SDL_FreeSurface(snakeBodySurface);
    snakeTexture = SDL_CreateTextureFromSurface(renderer, snakeSurface);
    foodTexture = SDL_CreateTextureFromSurface(renderer, foodSurface);
    SDL_FreeSurface(snakeSurface);
    SDL_FreeSurface(foodSurface);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                snakeMovement(event);
            }
        }

        for (int i = snakeLength - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        snake[0].x += velX;
        snake[0].y += velY;

        setSnakeLimits();

        snakeFoodCollition(); // Verificar colisión con la comida
        snakeBodyCollition(); // Verificar colisión con el cuerpo

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawMapBorders(renderer);// Dibujar los bordes
        drawSnake(renderer);// Dibujar la serpiente
        drawFood(renderer);  // Dibujar la comida
        drawScore(renderer);//Dibujar el puntaje

        SDL_RenderPresent(renderer);
        SDL_Delay(200);
    }
    TTF_CloseFont(font);
    SDL_DestroyTexture(snakeTexture);
    SDL_DestroyTexture(foodTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}