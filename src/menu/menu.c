#include "../../include/menu/menu.h"

int handle_menu_events(SDL_Renderer *renderer,Button playButton, Button settingsButton, Button quitButton, SDL_Event event, int *running, int *settingsPage) {




    while (SDL_PollEvent(&event)) {
        
        if (event.type == SDL_QUIT) {
            *running = 0;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            if (mouseX >= playButton.rect.x && mouseX <= playButton.rect.x + BUTTON_WIDTH &&
                mouseY >= playButton.rect.y && mouseY <= playButton.rect.y + BUTTON_HEIGHT) {
                return 1;
            } else if (mouseX >= settingsButton.rect.x && mouseX <= settingsButton.rect.x + BUTTON_WIDTH &&
                       mouseY >= settingsButton.rect.y && mouseY <= settingsButton.rect.y + BUTTON_HEIGHT) {
                        *settingsPage = 1;
            } else if (mouseX >= quitButton.rect.x && mouseX <= quitButton.rect.x + BUTTON_WIDTH &&
                       mouseY >= quitButton.rect.y && mouseY <= quitButton.rect.y + BUTTON_HEIGHT) {
                *running = 0;
            }
        }
    }
    return 0;
}

int menu(SDL_Renderer *renderer, Button playButton, Button settingsButton, Button quitButton, int *running, int *settingsPage) {
    SDL_Event event;
    int renvoie=0;
    // Chargement de l'image de fond
    SDL_Surface *backgroundSurface = IMG_Load("data/image/menu/background_rpg.png");
    SDL_Texture *backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);


    renvoie = handle_menu_events(renderer,playButton,settingsButton,quitButton, event, running, settingsPage);

    // Affichage de l'image de fond et des boutons du menu principal
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
    render_Button(playButton, renderer);
    render_Button(settingsButton, renderer);
    render_Button(quitButton, renderer);
    return renvoie;
}
