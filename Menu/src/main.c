#include "commonSDL.h"






int main() {
    // Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Royaume des Ombres : l'éveil des Ténèbres", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Chargement de l'icône de la fenêtre
    SDL_Surface* iconSurface = IMG_Load("../images/Icone.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);
   

    // Chargement des images des boutons
    SDL_Surface *playSurface = IMG_Load("../images/bouton_jouer.png");
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Surface *settingsSurface = IMG_Load("../images/bouton_paramètre.png");
    SDL_Texture *settingsTexture = SDL_CreateTextureFromSurface(renderer, settingsSurface);
    SDL_Surface *quitSurface = IMG_Load("../images/bouton_quitter.png");
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);

    // Chargement des images des boutons de la fenêtre de paramètres
    SDL_Surface *saveSurface = IMG_Load("../images/bouton_sauvegarde.png");
    SDL_Texture *saveTexture = SDL_CreateTextureFromSurface(renderer, saveSurface);
    SDL_Surface *loadSurface = IMG_Load("../images/bouton_charger.png");
    SDL_Texture *loadTexture = SDL_CreateTextureFromSurface(renderer, loadSurface);
    SDL_Surface *deleteSurface = IMG_Load("../images/bouton_reset.png");
    SDL_Texture *deleteTexture = SDL_CreateTextureFromSurface(renderer, deleteSurface);



    // Initialisation des boutons
    Button playButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, playTexture);
    Button settingsButton = create_Button(BUTTON_MARGIN, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, settingsTexture);
    Button quitButton = create_Button(SCREEN_WIDTH - BUTTON_WIDTH - BUTTON_MARGIN, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, quitTexture);
    Button saveButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 200, saveTexture);
    Button loadButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 300, loadTexture);
    Button deleteButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 400, deleteTexture);
    Button quitButton2 = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, 500, quitTexture);


    // Libération des surfaces une fois les textures créées
    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(settingsSurface);
    SDL_FreeSurface(quitSurface);
    SDL_FreeSurface(saveSurface);
    SDL_FreeSurface(loadSurface);
    SDL_FreeSurface(deleteSurface);


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

    // Libération de la mémoire
    SDL_DestroyTexture(playTexture);
    SDL_DestroyTexture(settingsTexture);
    SDL_DestroyTexture(quitTexture);
    
    SDL_DestroyTexture(saveTexture);
    SDL_DestroyTexture(loadTexture);
    SDL_DestroyTexture(deleteTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
