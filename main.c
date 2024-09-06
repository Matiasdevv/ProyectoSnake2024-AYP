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
                    case SDLK_LEFT:  velX = -20; velY = 0;   break;
                    case SDLK_RIGHT: velX = 20;  velY = 0;    break;
                    case SDLK_UP:    velX = 0;  velY = -20;  break;
                    case SDLK_DOWN:  velX = 0;  velY = 20;   break;
                    case SDLK_ESCAPE: running = 0; 
                }
            }
        }

        // Movimiento de la serpiente
        snake.x += velX;
        snake.y += velY;
        // Evitar que la serpiente salga de la pantalla
        int limit = 20;  // Definir un límite de 20 píxeles

        if (snake.x < limit) {
         snake.x = limit;  // Detener en el borde izquierdo
        } else if (snake.x + snake.w > SCREEN_WIDTH - limit) {
           snake.x = SCREEN_WIDTH - snake.w - limit;  // Detener en el borde derecho
        }

        if (snake.y < limit) {
         snake.y = limit;  // Detener en el borde superior
        } else if (snake.y + snake.h > SCREEN_HEIGHT - limit) {
           snake.y = SCREEN_HEIGHT - snake.h - limit;  // Detener en el borde inferior
}


        // Detección de colisión entre la serpiente y la comida
        if (SDL_HasIntersection(&snake, &food)) {
             // Si la serpiente come la comida, reposiciona la comida en un lugar aleatorio

             //todo: evaluar hacia que lugar está mirando y modificar
             
                
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
                }

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
        SDL_Delay(100);
    }

    // Limpieza, limpa la memoria 
    SDL_DestroyRenderer(renderer); 
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}