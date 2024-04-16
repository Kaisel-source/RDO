
#include "option.h"

void handle_options_events(SDL_Renderer *renderer, SDL_Event event, int *settingsPage, int *deleteConfirmation) {

    // Chargement des images des boutons
    SDL_Surface *quitSurface = IMG_Load("../images/Quit.jpg");
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);

    // Chargement des images des boutons de la fenêtre de paramètres
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

    // Initialisation des boutons
    Button quitButton = create_Button(SCREEN_WIDTH - BUTTON_WIDTH - BUTTON_MARGIN, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, quitTexture);
    Button saveButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 200, saveTexture);
    Button loadButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 300, loadTexture);
    Button deleteButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 400, deleteTexture);
    Button quitButton2 = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 500, quitTexture);
    Button yesButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2, yesTexture);
    Button noButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2, noTexture);

    // Libération des surfaces une fois les textures créées
    SDL_FreeSurface(quitSurface);
    SDL_FreeSurface(saveSurface);
    SDL_FreeSurface(loadSurface);
    SDL_FreeSurface(deleteSurface);
    SDL_FreeSurface(yesSurface);
    SDL_FreeSurface(noSurface);


    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *settingsPage = 0; // Retour au menu principal si on quitte
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

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
                *deleteConfirmation = 1;
            } else if (mouseX >= quitButton2.rect.x && mouseX <= quitButton2.rect.x + BUTTON_WIDTH &&
                       mouseY >= quitButton2.rect.y && mouseY <= quitButton2.rect.y + BUTTON_HEIGHT) {
                *settingsPage = 0; // Retourner au menu principal depuis la page des paramètres
            }
        }
    }
}

void option(SDL_Renderer *renderer, Button saveButton, Button loadButton, Button deleteButton, Button quitButton, Button quitButton2, Button yesButton, Button noButton, int *settingsPage, int *deleteConfirmation) {
    SDL_Event event;
    
    // Chargement de l'image de fond
    SDL_Surface *backgroundSurface = IMG_Load("../images/wallhav.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    handle_options_events(renderer , event, settingsPage, deleteConfirmation);

    // Affichage de l'image de fond et des boutons des options
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    render_Button(saveButton, renderer);
    render_Button(loadButton, renderer);
    render_Button(deleteButton, renderer);
    render_Button(quitButton2, renderer);

    if (*deleteConfirmation) {
        render_Button(yesButton, renderer);
        render_Button(noButton, renderer);
    }
}
