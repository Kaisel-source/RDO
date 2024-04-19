




/*
int main() {
    // Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Royaume des Ombres : l'éveil des Ténèbres", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    
   

   


    // Boucle principale
    int running = 1;
    int settingsPage = 0;
    while (running) {
        // Gestion des événements et affichage des menus
        if (!settingsPage) {
            menu(renderer, playButton, settingsButton, quitButton, &running, &settingsPage);
        } else {
            option(renderer,saveButton, loadButton, deleteButton, quitButton2, &settingsPage);
        }

        SDL_RenderPresent(renderer);
    }


    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
*/