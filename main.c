#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int SEGMENT_SIZE = 20;

SDL_Rect food = {200, 200, SEGMENT_SIZE, SEGMENT_SIZE}; // Posición y tamaño de la comida

int velX = SEGMENT_SIZE, velY = 0; // Velocidad de la serpiente

SDL_Rect snake[100]; // Declare the array with a fixed size
int snakeLength = 2; // Initially, the snake has 2 segments

// Initialize the snake array
void initializeSnake()
{
    snake[0].x = 100;
    snake[0].y = 100;
    snake[0].w = SEGMENT_SIZE;
    snake[0].h = SEGMENT_SIZE;
}

// Bucle del juego
int running = 1;
SDL_Event event;

void snakeMovement(SDL_Event event)
{
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
        // No permitir moverse a la izquierda si ya se está moviendo a la derecha
        if (velX != SEGMENT_SIZE)
        {
            velX = -SEGMENT_SIZE;
            velY = 0;
        }
        break;
    case SDLK_RIGHT:
        // No permitir moverse a la derecha si ya se está moviendo a la izquierda
        if (velX != -SEGMENT_SIZE)
        {
            velX = SEGMENT_SIZE;
            velY = 0;
        }
        break;
    case SDLK_UP:
        // No permitir moverse hacia arriba si ya se está moviendo hacia abajo
        if (velY != SEGMENT_SIZE)
        {
            velX = 0;
            velY = -SEGMENT_SIZE;
        }
        break;
    case SDLK_DOWN:
        // No permitir moverse hacia abajo si ya se está moviendo hacia arriba
        if (velY != -SEGMENT_SIZE)
        {
            velX = 0;
            velY = SEGMENT_SIZE;
        }
        break;
    case SDLK_ESCAPE:
        running = 0;
        break;
    }
}

void setSnakeLimits()
{

    // Evitar que la serpiente salga de la pantalla
    int limit = SEGMENT_SIZE;

    if (snake[0].x < limit)
    {
        snake[0].x = limit; // Detener en el borde izquierdo
    }
    else if (snake[0].x + snake[0].w > SCREEN_WIDTH - limit)
    {
        snake[0].x = SCREEN_WIDTH - snake[0].w - limit; // Detener en el borde derecho
    }

    if (snake[0].y < limit)
    {
        snake[0].y = limit; // Detener en el borde superior
    }
    else if (snake[0].y + snake[0].h > SCREEN_HEIGHT - limit)
    {
        snake[0].y = SCREEN_HEIGHT - snake[0].h - limit; // Detener en el borde inferior
    }
}

void snakeFoodCollition()
{
    // Detección de colisión entre la serpiente y la comida
    if (SDL_HasIntersection(&snake[0], &food))
    {
        int ramdom_number = (rand() % 39) * 20; // genera un numero aleatorio dentro de la cuadricula
        int ramdom_number2 = (rand() % 29) * 20;

        if (ramdom_number == 0)
        { // verificar que el numero no sea 0
            while (ramdom_number == 0)
            {
                ramdom_number = (rand() % 39) * 20; // dar numeros aleatorios hasta que sea distinto a 0
            }
        }

        if (ramdom_number2 == 0)
        { // verificar que el numero no sea 0
            while (ramdom_number2 == 0)
            {
                ramdom_number2 = (rand() % 29) * 20; // dar numeros aleatorios hasta que sea distinto a 0
            }
        }

        food.x = ramdom_number;  // establecer el numero como posicion en x de la comida
        food.y = ramdom_number2; // establecer el numero como posicion en y de la comida
        snakeLength++;           // Aumentar el tamaño de la serpiente
    }
}

void snakeBodyCollition()
{
    // verifica si colisiona o no el cuerpo con la cabeza
    for (int i = 1; i < snakeLength; i++)
    {
        if (SDL_HasIntersection(&snake[0], &snake[i + 1]))
        {
            running = 0;
        }
    }
}

void drawSnake(SDL_Renderer *renderer)
{
    // Dibuja la serpiente
    for (int i = 0; i < snakeLength; i++)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
        SDL_RenderFillRect(renderer, &snake[i]);
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    // Inicializa generador de números aleatorios
    initializeSnake();

    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Crea la ventana
    SDL_Window *window = SDL_CreateWindow("Snake Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (!window)
    {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crea el renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    while (running)
    {
        // Manejo de eventos
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN)
            {
                snakeMovement(event);
            }
        }
        // Mover cada segmento al lugar del segmento anterior
        for (int i = snakeLength - 1; i > 0; i--)
        {
            snake[i] = snake[i - 1];
        }

        snake[0].x += velX;
        snake[0].y += velY;

        setSnakeLimits();

        snakeBodyCollition();

        snakeFoodCollition();

        // Limpia la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
        SDL_RenderClear(renderer);

        // Dibuja la comida
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
        SDL_RenderFillRect(renderer, &food);

        drawSnake(renderer);

        // Actualiza la pantalla
        SDL_RenderPresent(renderer);

        // Control de la velocidad del juego
        SDL_Delay(200);
    }

    // Limpieza
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
