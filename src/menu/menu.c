#include "../common/common.h"

void handle_menu_events(SDL_Renderer *renderer, SDL_Event event, int *running, int *settingsPage) {

    // Chargement des images des boutons
    SDL_Surface *playSurface = IMG_Load("data/image/menu/bouton_jouer.png");
    SDL_Texture *playTexture = SDL_CreateTextureFromSurface(renderer, playSurface);
    SDL_Surface *settingsSurface = IMG_Load("data/image/menu/bouton_sort.png");
    SDL_Texture *settingsTexture = SDL_CreateTextureFromSurface(renderer, settingsSurface);
    SDL_Surface *quitSurface = IMG_Load("data/image/menu/bouton_quitter.png");
    SDL_Texture *quitTexture = SDL_CreateTextureFromSurface(renderer, quitSurface);




    // Initialisation des boutons
    Button playButton = create_Button(SCREEN_WIDTH / 2 - BUTTON_WIDTH / 2, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, playTexture);
    Button settingsButton = create_Button(BUTTON_MARGIN, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, settingsTexture);
    Button quitButton = create_Button(SCREEN_WIDTH - BUTTON_WIDTH - BUTTON_MARGIN, SCREEN_HEIGHT - BUTTON_HEIGHT - BUTTON_MARGIN, quitTexture);

    // Libération des surfaces une fois les textures créées
    SDL_FreeSurface(playSurface);
    SDL_FreeSurface(settingsSurface);
    SDL_FreeSurface(quitSurface);




    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            *running = 0;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);

            if (mouseX >= playButton.rect.x && mouseX <= playButton.rect.x + BUTTON_WIDTH &&
                mouseY >= playButton.rect.y && mouseY <= playButton.rect.y + BUTTON_HEIGHT) {
                printf("Lancer le jeu\n");
            } else if (mouseX >= settingsButton.rect.x && mouseX <= settingsButton.rect.x + BUTTON_WIDTH &&
                       mouseY >= settingsButton.rect.y && mouseY <= settingsButton.rect.y + BUTTON_HEIGHT) {
                printf("Ouvrir les paramètres\n");
                *settingsPage = 1;
            } else if (mouseX >= quitButton.rect.x && mouseX <= quitButton.rect.x + BUTTON_WIDTH &&
                       mouseY >= quitButton.rect.y && mouseY <= quitButton.rect.y + BUTTON_HEIGHT) {
                *running = 0;
            }
        }
    }
}

void menu(SDL_Renderer *renderer, Button playButton, Button settingsButton, Button quitButton, int *running, int *settingsPage) {
    SDL_Event event;

    // Chargement de l'image de fond
    SDL_Surface *backgroundSurface = IMG_Load("data/image/menu/background_rpg.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


    handle_menu_events(renderer, event, running, settingsPage);

    // Affichage de l'image de fond et des boutons du menu principal
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    render_Button(playButton, renderer);
    render_Button(settingsButton, renderer);
    render_Button(quitButton, renderer);
}
