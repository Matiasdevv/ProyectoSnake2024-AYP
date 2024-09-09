#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>  
#include <time.h>   

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
// Tamaño de cada segmento de la serpiente
const int SEGMENT_SIZE = 20;

int main(int argc, char* argv[]) {
    // Inicializa SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error al inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }

    // Crea la ventana
    SDL_Window* window = SDL_CreateWindow("Snake Game",
                                          SDL_WINDOWPOS_CENTERED,
                                          SDL_WINDOWPOS_CENTERED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);

    if (!window) {
        printf("Error al crear la ventana: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Crea el renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        printf("Error al crear el renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Inicializa generador de números aleatorios
    srand(time(NULL));

    SDL_Rect food = {200, 200, SEGMENT_SIZE, SEGMENT_SIZE};   // Posición y tamaño de la comida
    int velX = SEGMENT_SIZE, velY = 0;  // Velocidad de la serpiente

    // Lista de segmentos de la serpiente (comenzando con la cabeza)
    SDL_Rect snake[100];  // Máximo de 100 segmentos por simplicidad
    int snakeLength = 2;  // Inicialmente, la serpiente tiene 2 segmentos
    snake[0] = (SDL_Rect){100, 100, SEGMENT_SIZE, SEGMENT_SIZE};  // Inicializa la cabeza de la serpiente

    // Bucle del juego
    int running = 1;
    SDL_Event event;

    while (running) {
        // Manejo de eventos
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:  velX = -SEGMENT_SIZE; velY = 0;   break;
                    case SDLK_RIGHT: velX = SEGMENT_SIZE;  velY = 0;    break;
                    case SDLK_UP:    velX = 0;  velY = -SEGMENT_SIZE;  break;
                    case SDLK_DOWN:  velX = 0;  velY = SEGMENT_SIZE;   break;
                    case SDLK_ESCAPE: running = 0;
                }
            }
        }

        // Movimiento de la serpiente
        // Mover cada segmento al lugar del segmento anterior
        for (int i = snakeLength - 1; i > 0; i--) {
            snake[i] = snake[i - 1];
        }

        // Mover la cabeza
        snake[0].x += velX;
        snake[0].y += velY;

        // Evitar que la serpiente salga de la pantalla
        int limit = SEGMENT_SIZE;

        if (snake[0].x < limit) {
            snake[0].x = limit;  // Detener en el borde izquierdo
        } else if (snake[0].x + snake[0].w > SCREEN_WIDTH - limit) {
            snake[0].x = SCREEN_WIDTH - snake[0].w - limit;  // Detener en el borde derecho
        }

        if (snake[0].y < limit) {
            snake[0].y = limit;  // Detener en el borde superior
        } else if (snake[0].y + snake[0].h > SCREEN_HEIGHT - limit) {
            snake[0].y = SCREEN_HEIGHT - snake[0].h - limit;  // Detener en el borde inferior
        }

        // Detección de colisión entre la serpiente y la comida
        if (SDL_HasIntersection(&snake[0], &food)) {
             int ramdom_number = (rand()% 39)*20;  //genera un numero aleatorio dentro de la cuadricula
                int ramdom_number2 = (rand()% 29)*20; 

                if (ramdom_number == 0) {  //verificar que el numero no sea 0
                 while (ramdom_number == 0 ) { 
                   ramdom_number= (rand()% 39)*20; // dar numeros aleatorios hasta que sea distinto a 0
                   }
                }
                
                if (ramdom_number2 == 0 ) { //verificar que el numero no sea 0
                    while(ramdom_number2 == 0) {
                   ramdom_number2= (rand()% 29)*20;  // dar numeros aleatorios hasta que sea distinto a 0
                   }
                }
    
        food.x = ramdom_number; //establecer el numero como posicion en x de la comida
        food.y = ramdom_number2; // establecer el numero como posicion en y de la comida
                  
            snakeLength++;  // Aumentar el tamaño de la serpiente
        }

        // Limpia la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
        SDL_RenderClear(renderer);

        // Dibuja la comida
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
        SDL_RenderFillRect(renderer, &food);

        // Dibuja la serpiente
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
        for (int i = 0; i < snakeLength; i++) {
            SDL_RenderFillRect(renderer, &snake[i]);
        }

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
