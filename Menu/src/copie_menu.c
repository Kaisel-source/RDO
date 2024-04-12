#include "commonSDL.h"



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






int main() {


    // Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Royaume des Ombres : l'éveil des Ténèbres", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Chargement de l'image de fond
    SDL_Surface *backgroundSurface = IMG_Load("../images/wallhav.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


    // Chargement des images des boutons
    SDL_Surface *playSurface = IMG_Load("../images/Play.jpg");
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Surface *settingsSurface = IMG_Load("../images/Engrenage.jpg");
    SDL_Texture *settingsTexture = SDL_CreateTextureFromSurface(renderer, settingsSurface);
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
    Button playButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, playTexture);
    Button settingsButton = create_Button(BUTTON_MARGIN, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, settingsTexture);
    Button quitButton = create_Button(SCREEN_WIDTH - BUTTON_WIDTH - BUTTON_MARGIN, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, quitTexture);
    Button saveButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 200, saveTexture);
    Button loadButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 300, loadTexture);
    Button deleteButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 400, deleteTexture);
    Button quitButton2 = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 500, quitTexture);


    // Boutons de confirmation de suppression
    Button yesButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2, yesTexture);
    Button noButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2 + 200, SCREEN_HEIGHT / 2 - BUTTON_HEIGHT / 2, noTexture);


    // Libération des surfaces une fois les textures créées
    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(settingsSurface);
    SDL_FreeSurface(quitSurface);
    SDL_FreeSurface(saveSurface);
    SDL_FreeSurface(loadSurface);
    SDL_FreeSurface(deleteSurface);
    SDL_FreeSurface(yesSurface);
    SDL_FreeSurface(noSurface);


    // Chargement de l'icône de la fenêtre
    SDL_Surface* iconSurface = IMG_Load("../images/Icone.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);


    SDL_Event event;
    int running = 1;
    int settingsPage = 0; // Variable pour gérer l'affichage de la page des paramètres
    int deleteConfirmation = 0; // Variable pour gérer l'état de la confirmation de suppression


    while (running) {

        while (SDL_PollEvent(&event)) {

            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);



                if (!settingsPage) {

                    // Vérification de l'appui sur les boutons
                    if (mouseX >= playButton.rect.x && mouseX <= playButton.rect.x + BUTTON_WIDTH &&
                        mouseY >= playButton.rect.y && mouseY <= playButton.rect.y + BUTTON_HEIGHT) {
                        printf("Lancer le jeu\n");

                    } else if (mouseX >= settingsButton.rect.x && mouseX <= settingsButton.rect.x + BUTTON_WIDTH &&
                               mouseY >= settingsButton.rect.y && mouseY <= settingsButton.rect.y + BUTTON_HEIGHT) {
                        printf("Ouvrir les paramètres\n");
                        settingsPage = 1; // Afficher la page des paramètres

                    } else if (mouseX >= quitButton.rect.x && mouseX <= quitButton.rect.x + BUTTON_WIDTH &&
                               mouseY >= quitButton.rect.y && mouseY <= quitButton.rect.y + BUTTON_HEIGHT) {
                        running = 0;
                    }




                } else {

                    if (!deleteConfirmation) {

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
                }
            }
        }
        


        // Affichage de l'image de fond
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


        // Affichage des boutons
        if (!settingsPage) {
            render_Button(playButton, renderer);
            render_Button(settingsButton, renderer);
            render_Button(quitButton, renderer);

        } else {

            render_Button(saveButton, renderer);
            render_Button(loadButton, renderer);
            render_Button(deleteButton, renderer);
            render_Button(quitButton2, renderer);

            if (deleteConfirmation) {
                render_Button(yesButton, renderer);
                render_Button(noButton, renderer);
            }
        }

        SDL_RenderPresent(renderer);
    }

    // Libération de la mémoire
    SDL_DestroyTexture(playTexture);
    SDL_DestroyTexture(settingsTexture);
    SDL_DestroyTexture(quitTexture);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
