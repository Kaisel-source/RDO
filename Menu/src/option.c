#include "option.h"



void option(){

// Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Royaume des Ombres : l'éveil des Ténèbres", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Chargement de l'image de fond
    SDL_Surface *backgroundSurface = IMG_Load("../images/wallhav.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


// Chargement des images des boutons de la fenêtre de paramètres
    SDL_Surface *quitSurface = IMG_Load("../images/Quit.jpg");
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);
    SDL_Surface *saveSurface = IMG_Load("../images/Save.png");
    SDL_Texture *saveTexture = SDL_CreateTextureFromSurface(renderer, saveSurface);
    SDL_Surface *loadSurface = IMG_Load("../images/Load.png");
    SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
    SDL_Surface *deleteSurface = IMG_Load("../images/Delete.png");
    SDL_Texture *deleteTexture = SDL_CreateTextureFromSurface(renderer, deleteSurface);


    // Chargement des images des boutons de confirmation
    SDL_Surface *yesSurface = IMG_Load("../images/Yes.png");
    SDL_Texture *yesTexture = SDL_CreateTextureFromSurface(renderer, yesSurface);
    SDL_Surface *noSurface = IMG_Load("../images/No.png");
    SDL_Texture *noTexture = SDL_CreateTextureFromSurface(renderer, noSurface);

    Button saveButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 200, saveTexture);
    Button loadButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 300, loadTexture);
    Button deleteButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 400, deleteTexture);
    Button quitButton2 = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 500, quitTexture);


    // Boutons de confirmation de suppression
    Button yesButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2, yesTexture);
    Button noButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2, noTexture);

    SDL_FreeSurface(quitSurface);    
    SDL_FreeSurface(saveSurface);
    SDL_FreeSurface(loadSurface);
    SDL_FreeSurface(deleteSurface);
    SDL_FreeSurface(yesSurface);
    SDL_FreeSurface(noSurface);

    int settingsPage = 0; // Variable pour gérer l'affichage de la page des paramètres
    int deleteConfirmation = 0; // Variable pour gérer l'état de la confirmation de suppression


    if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

    }else if (!deleteConfirmation) {

        // Vérification de l'appui sur les boutons dans la page des paramètres
        if (mouseX >= saveButton.rect.x && mouseX <= saveButton.rect.x + BUTTON_WIDTH &&
            mouseY >= saveButton.rect.y && mouseY <= saveButton.rect.y + BUTTON_HEIGHT) {
            printf("Sauvegarde du jeu\n");
            // Inclure la fonction de sauvegarde


        } else if (mouseX >= loadButton.rect.x && mouseX <= loadButton.rect.x + BUTTON_WIDTH &&
                mouseY >= loadButton.rect.y && mouseY <= loadButton.rect.y + BUTTON_HEIGHT) {
            printf("Chargement du jeu\n");
            // Inclure la fonction de chargement


        } else if (mouseX >= deleteButton.rect.x && mouseX <= deleteButton.rect.x + BUTTON_WIDTH &&
                mouseY >= deleteButton.rect.y && mouseY <= deleteButton.rect.y + BUTTON_HEIGHT) {
            printf("Suppression de la sauvegarde\n");
            // Activer la confirmation de suppression
            deleteConfirmation = 1;


        } else if (mouseX >= quitButton2.rect.x && mouseX <= quitButton2.rect.x + BUTTON_WIDTH &&
                mouseY >= quitButton2.rect.y && mouseY <= quitButton2.rect.y + BUTTON_HEIGHT) {
            settingsPage = 0; // Retourner au menu principal depuis la page des paramètres
        }

    } else {

        // Vérification de l'appui sur les boutons de confirmation de suppression
        if (mouseX >= yesButton.rect.x && mouseX <= yesButton.rect.x + BUTTON_WIDTH &&
            mouseY >= yesButton.rect.y && mouseY <= yesButton.rect.y + BUTTON_HEIGHT) {
            printf("Suppression confirmée\n");
            // Effectuer la suppression de la sauvegarde
            deleteConfirmation = 0; // Réinitialiser la confirmation de suppression

        } else if (mouseX >= noButton.rect.x && mouseX <= noButton.rect.x + BUTTON_WIDTH &&
                mouseY >= noButton.rect.y && mouseY <= noButton.rect.y + BUTTON_HEIGHT) {
            printf("Suppression annulée\n");
            deleteConfirmation = 0; // Réinitialiser la confirmation de suppression
        }
    }


    render_Button(saveButton, renderer);
    render_Button(loadButton, renderer);
    render_Button(deleteButton, renderer);
    render_Button(quitButton2, renderer);

    if (deleteConfirmation) {
        render_Button(yesButton, renderer);
        render_Button(noButton, renderer);
    }
}