
#include "../../include/menu/option.h"

void handle_options_events(SDL_Renderer *renderer, SDL_Event event, int *settingsPage) {

    // Chargement des images des boutons
    SDL_Surface *quitSurface = IMG_Load("data/image/menu/bouton_quitter.png");
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);

    // Chargement des images des boutons de la fenêtre de paramètres
    SDL_Surface *saveSurface = IMG_Load("data/image/menu/bouton_sauvegarde.png");
    SDL_Texture *saveTexture = SDL_CreateTextureFromSurface(renderer, saveSurface);
    SDL_Surface *loadSurface = IMG_Load("data/image/menu/bouton_charger.png");
    SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
    SDL_Surface *deleteSurface = IMG_Load("data/image/menu/bouton_reset.png");
    SDL_Texture *deleteTexture = SDL_CreateTextureFromSurface(renderer, deleteSurface);


    // Initialisation des boutons

    Button saveButton = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 200, saveTexture);
    Button loadButton = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 300, loadTexture);
    Button deleteButton = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 400, deleteTexture);
    Button quitButton2 = create_Button(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, 500, quitTexture);
 
    // Libération des surfaces une fois les textures créées
    SDL_FreeSurface(quitSurface);
    SDL_FreeSurface(saveSurface);
    SDL_FreeSurface(loadSurface);
    SDL_FreeSurface(deleteSurface);


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
            } else if (mouseX >= quitButton2.rect.x && mouseX <= quitButton2.rect.x + BUTTON_WIDTH &&
                       mouseY >= quitButton2.rect.y && mouseY <= quitButton2.rect.y + BUTTON_HEIGHT) {
                *settingsPage = 0; // Retourner au menu principal depuis la page des paramètres
            }
        }
    }
}

void option(SDL_Renderer *renderer, Button saveButton, Button loadButton, Button deleteButton, Button quitButton2, int *settingsPage) {
    SDL_Event event;
    
    // Chargement de l'image de fond
    SDL_Surface *backgroundSurface = IMG_Load("data/image/menu/background_rpg.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    handle_options_events(renderer , event, settingsPage);

    // Affichage de l'image de fond et des boutons des options
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    render_Button(saveButton, renderer);
    render_Button(loadButton, renderer);
    render_Button(deleteButton, renderer);
    render_Button(quitButton2, renderer);

}
