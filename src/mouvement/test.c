#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define IMAGE_WIDTH 65
#define IMAGE_HEIGHT 65
#define ELEMENT_SIZE 65 // Taille de chaque élément dans l'image
#define ELEMENT_ROW_COUNT 4 // Nombre d'éléments par ligne dans l'image

// Fonction pour charger une image
SDL_Texture* loadTexture(SDL_Renderer *renderer, const char *file) {
    SDL_Surface *surface = IMG_Load(file);
    SDL_Texture *texture = NULL;
    if (surface) {
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }
    return texture;
}

int main(int argc, char* args[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Chargement de l'image
    SDL_Texture* image = loadTexture(renderer, "image/perso.png");
    if (!image) {
        printf("Failed to load image!\n");
        return 1;
    }

    // Choisissez l'élément spécifique à afficher
    int elementIndex = 0; // Index de l'élément dans l'image (commence à 0)
    int elementRow = elementIndex / ELEMENT_ROW_COUNT; // Ligne de l'élément dans l'image
    int elementColumn = elementIndex % ELEMENT_ROW_COUNT; // Colonne de l'élément dans l'image

    // Boucle principale
    SDL_Event e;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Effacement de l'écran
        SDL_RenderClear(renderer);

        // Affichage de l'élément spécifique de l'image
        SDL_Rect srcRect = {elementColumn * ELEMENT_SIZE, elementRow * ELEMENT_SIZE, ELEMENT_SIZE, ELEMENT_SIZE};
        SDL_Rect destRect = {SCREEN_WIDTH / 2 - ELEMENT_SIZE / 2, SCREEN_HEIGHT / 2 - ELEMENT_SIZE / 2, ELEMENT_SIZE, ELEMENT_SIZE};
        SDL_RenderCopy(renderer, image, &srcRect, &destRect);

        // Actualisation de l'écran
        SDL_RenderPresent(renderer);
    }

    // Libération des ressources
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
