#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdbool.h>






// Dimensions de la fenêtre
const int SCREEN_WIDTH = 1820;
const int SCREEN_HEIGHT = 1080;

// Dimensions et position des boutons
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 75;
const int BUTTON_QUIT_X = 100;
const int BUTTON_QUIT_Y = 900;
const int BUTTON_MARGIN = 20; // Marge entre les boutons








// Fonction pour initialiser SDL et créer la fenêtre
bool init_SDL(SDL_Window** window, SDL_Renderer** renderer) {


    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'a pas pu être initialisé! SDL_Error: %s\n", SDL_GetError());
        return false;
    }


    // Création de la fenêtre
    *window = SDL_CreateWindow("Menu SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("La fenêtre n'a pas pu être créée! SDL_Error: %s\n", SDL_GetError());
        return false;
    }


    // Création du renderer
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Le renderer n'a pas pu être créé! SDL_Error: %s\n", SDL_GetError());
        return false;
    }


    return true;
}









// Fonction pour charger les ressources (images, polices, etc.)
bool load_Media(SDL_Renderer* renderer, SDL_Texture** textureBackground, SDL_Texture** textureButton1, SDL_Texture** textureButton2, SDL_Texture** textureButton3, SDL_Texture** textureButton4) {
    // Charger l'image de fond JPEG
    SDL_Surface* loadedSurface = IMG_Load("Wallhaven.jpg");


    if (loadedSurface == NULL) {
        printf("Impossible de charger l'image de fond JPG! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }


    // Convertir la surface en texture
    *textureBackground = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (*textureBackground == NULL) {
        printf("Impossible de créer la texture de fond à partir de la surface! SDL_Error: %s\n", SDL_GetError());
        return false;
    }


    // Libérer la surface chargée
    SDL_FreeSurface(loadedSurface);


    // Charger les images des boutons JPEG
    loadedSurface = IMG_Load("Quit.jpg"); //Boutton Pour Quitter le jeu
    if (loadedSurface == NULL) {
        printf("Impossible de charger l'image du bouton Quit JPG! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    *textureButton1 = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (*textureButton1 == NULL) {
        printf("Impossible de créer la texture du bouton Quit à partir de la surface! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(loadedSurface);



    loadedSurface = IMG_Load("Play.jpg"); //Boutton pour lance le jeu
    if (loadedSurface == NULL) {
        printf("Impossible de charger l'image du bouton Play JPG! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    *textureButton2 = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (*textureButton2 == NULL) {
        printf("Impossible de créer la texture du bouton play à partir de la surface! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(loadedSurface);



    loadedSurface = IMG_Load("Engrenage.jpg"); //Boutton pour les paramètres
    if (loadedSurface == NULL) {
        printf("Impossible de charger l'image du bouton Engrenage JPG! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    *textureButton3 = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (*textureButton3 == NULL) {
        printf("Impossible de créer la texture du bouton Engrenage à partir de la surface! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(loadedSurface);



    loadedSurface = IMG_Load("Credit.jpg"); //Boutton pour
    if (loadedSurface == NULL) {
        printf("Impossible de charger l'image du bouton Crédit JPG! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    *textureButton4 = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    if (*textureButton4 == NULL) {
        printf("Impossible de créer la texture du bouton de crédit à partir de la surface! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_FreeSurface(loadedSurface);



    return true;
}




// Fonction pour gérer l'événement de clic
void handle_Click(SDL_Event* event, bool* quit) {
    
    if (event->type == SDL_MOUSEBUTTONDOWN) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);


        // Vérifier si le clic se trouve dans la zone du boutton quitter
        if ((mouseX >= BUTTON_QUIT_X && mouseX <= BUTTON_QUIT_X + BUTTON_WIDTH) && (mouseY >= BUTTON_QUIT_Y && mouseY <= BUTTON_QUIT_Y + BUTTON_HEIGHT)) {
            *quit = true;
        }



        // Vérifier si le clic se trouve dans la zone du boutton paramètre et créer la fenêtre de paramètre
        if((mouseX >= BUTTON_QUIT_X && mouseX <= BUTTON_QUIT_X + BUTTON_WIDTH) && (mouseY >= BUTTON_QUIT_Y - (2 * (BUTTON_HEIGHT + BUTTON_MARGIN)) && mouseY <= BUTTON_QUIT_Y - (2 * (BUTTON_HEIGHT + BUTTON_MARGIN)) + BUTTON_HEIGHT)){
            
            *quit = true;


        }


    }
}




// Fonction pour libérer les ressources et fermer SDL
void close_SDL(SDL_Window* window, SDL_Renderer* renderer) {
    // Libérer le renderer
    SDL_DestroyRenderer(renderer);


    // Libérer la fenêtre
    SDL_DestroyWindow(window);


    // Quitter SDL
    SDL_Quit();
}










int main(int argc, char* args[]) {
    // Déclaration des variables
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* textureBackground = NULL;
    SDL_Texture* textureButton1 = NULL;
    SDL_Texture* textureButton2 = NULL;
    SDL_Texture* textureButton3 = NULL;
    SDL_Texture* textureButton4 = NULL;
    bool quit = false;


    // Initialiser SDL
    if (!init_SDL(&window, &renderer)) {
        return 1;
    }


    // Charger les ressources
    if (!load_Media(renderer, &textureBackground, &textureButton1, &textureButton2, &textureButton3, &textureButton4)) {
        close_SDL(window, renderer);
        return 1;
    }


    // Boucle principale du programme
    SDL_Event e;
    while (!quit) {

        // Gestion des événements
        while (SDL_PollEvent(&e) != 0) {
            // Si l'utilisateur veut quitter
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            // Gérer les clics de souris
            handle_Click(&e, &quit);
        }


        // Effacer l'écran
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(renderer);


        // Dessiner l'image de fond
        SDL_Rect destRectBackground = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_RenderCopy(renderer, textureBackground, NULL, &destRectBackground);


        // Dessiner les boutons
        for (int i = 0; i < 4; ++i) {
            int buttonY = BUTTON_QUIT_Y - (i * (BUTTON_HEIGHT + BUTTON_MARGIN));
            SDL_Texture* currentButtonTexture = NULL;
            switch (i) {
                case 0:
                    currentButtonTexture = textureButton1;
                    break;
                case 1:
                    currentButtonTexture = textureButton2;
                    break;
                case 2:
                    currentButtonTexture = textureButton3;
                    break;
                case 3:
                    currentButtonTexture = textureButton4;
                    break;
            }

            SDL_Rect destRectButton = {BUTTON_QUIT_X, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT};
            SDL_RenderCopy(renderer, currentButtonTexture, NULL, &destRectButton);
        }


        // Mettre à jour l'écran
        SDL_RenderPresent(renderer);
    }


    // Libérer les ressources et quitter SDL
    close_SDL(window, renderer);

    return 0;
}
