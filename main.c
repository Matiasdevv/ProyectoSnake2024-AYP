#include <SDL2/SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

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

    // Variables del juego (por simplicidad, sólo una cabeza de serpiente y una comida)
    SDL_Rect snake = {100, 100, 20, 20};  // Posición y tamaño de la serpiente
    SDL_Rect food = {200, 200, 20, 20};   // Posición y tamaño de la comida
    int velX = 20, velY = 0;  // Velocidad de la serpiente

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
                    case SDLK_UP:    velX = 0;  velY = -20; break;
                    case SDLK_DOWN:  velX = 0;  velY = 20;  break;
                    case SDLK_LEFT:  velX = -20; velY = 0;  break;
                    case SDLK_RIGHT: velX = 20;  velY = 0;  break;
                    case SDLK_ESCAPE: running = 0; 
                }
            }
        }

        // Movimiento de la serpiente
        snake.x += velX;
        snake.y += velY;

        // Limpia la pantalla
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Negro
        SDL_RenderClear(renderer);

        // Dibuja la comida
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rojo
        SDL_RenderFillRect(renderer, &food);

        // Dibuja la serpiente
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Verde
        SDL_RenderFillRect(renderer, &snake);

        // Actualiza la pantalla
        SDL_RenderPresent(renderer);

        // Control de la velocidad del juego
        SDL_Delay(150);
    }

    // Limpieza
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
