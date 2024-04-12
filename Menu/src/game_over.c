#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 400
#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 75
#define BUTTON_MARGIN 20

// Structure pour représenter un bouton
typedef struct {
    SDL_Rect rect;
    SDL_Texture *texture;
} Button;

// Fonction pour initialiser un bouton
Button create_Button(int x, int y, SDL_Texture *texture) {
    Button button;
    button.rect.x = x;
    button.rect.y = y;
    button.rect.w = BUTTON_WIDTH;
    button.rect.h = BUTTON_HEIGHT;
    button.texture = texture;
    return button;
}


// Fonction pour afficher un bouton
void render_Button(Button button, SDL_Renderer *renderer) {
    SDL_RenderCopy(renderer, button.texture, NULL, &button.rect);
}

int game_over() {

    // Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Bah alors ? ...On est nul ?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Chargement de l'image de fond
    SDL_Surface *backgroundSurface = IMG_Load("../images/wallhav.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


    // Chargement des images des boutons
    SDL_Surface *goverSurface = IMG_Load("../images/GameOver.png");
    SDL_Texture *goverTexture = SDL_CreateTextureFromSurface(renderer, goverSurface);


    // Initialisation des boutons
    Button goverButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, goverTexture);


    // Libération des surfaces une fois les textures créées
    SDL_FreeSurface(goverSurface);


    // Chargement de l'icône de la fenêtre
    SDL_Surface* iconSurface = IMG_Load("../images/Icone.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);


    SDL_Event event;
    int running = 1;

    while (running) {

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                // Vérification de l'appui sur les boutons
                if (mouseX >= goverButton.rect.x && mouseX <= goverButton.rect.x + BUTTON_WIDTH &&
                    mouseY >= goverButton.rect.y && mouseY <= goverButton.rect.y + BUTTON_HEIGHT) {
                    printf("Game Over!\n");
                    //lorsque l'on clique sur le bouton, on retuourne au menu
                    running = 0;


                } 
                
            }
        }
        


        // Affichage de l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


        // Affichage des boutons
        render_Button(goverButton, renderer);

        SDL_RenderPresent(renderer);
    }

    // Libération de la mémoire
    SDL_DestroyTexture(goverTexture);

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
