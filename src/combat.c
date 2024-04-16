/**
 * @file combat.c
 * @author Mael gaumont
 * @brief interface de combat
 * @version 0.1
 * @date 2024-02-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */





#include "commun.h"

/*
int main(){

    int gagnant;

    SDL_Window* window = SDL_CreateWindow("RDO TEST",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    entite_t  plateau_de_combat[GRID_ROWS][GRID_COLUMNS];
    init_plateau(plateau_de_combat);
    //creation de perso1 prenom/classe/pv/pv_max/force/equipe/mouv/iniative/range
    entite_t perso1 = create_entity("Bob", "Guerrier", 100, 100, 20, 1, 3, 15, 5);
    entite_t perso2 = create_entity("Goblin", "Brigand", 100, 100, 100, 2, 2, 10, 5);

    SDL_Surface*  persoSurface1 = IMG_Load("img/ennemi.png");
    if (persoSurface1 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* persoSurface2 = IMG_Load("img/allie.png");
    if (persoSurface2 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface*  perdue = IMG_Load("img/game_over.jpeg");
    if (perdue == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture * perdueTexture = SDL_CreateTextureFromSurface(renderer,perdue);
    perso1.img = SDL_CreateTextureFromSurface(renderer, persoSurface1);
    perso2.img = SDL_CreateTextureFromSurface(renderer, persoSurface2);

    SDL_FreeSurface(persoSurface2);
    SDL_FreeSurface(persoSurface1);
    SDL_FreeSurface(perdue);

    plateau_de_combat[0][0]=perso1;
    plateau_de_combat[5][5]=perso2;

    gagnant=combat(plateau_de_combat,window,renderer);
    printf("%d",gagnant);
    if(gagnant==-1){
       SDL_RenderCopy(renderer, perdueTexture, NULL, NULL); //ecran game over
    }

    SDL_Delay(1000);

    SDL_DestroyTexture(perso1.img);
    SDL_DestroyTexture(perso2.img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
*/


int main() {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() != 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Création de la fenêtre SDL
    SDL_Window *window = SDL_CreateWindow("Exemple d'inventaire", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Création du renderer SDL
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement de la police de caractères
    TTF_Font *font = TTF_OpenFont("img/police.ttf", 12);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police de caractères : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Définition des couleurs
    SDL_Color textColor = {255, 255, 255, 255};
    SDL_Color bgColor = {0, 100, 100, 255};

    // Définition de l'inventaire
    Item inventory[] = {
        {"Épée", "Une arme tranchante"},
        {"Potion de santé", "Restaure des points de vie"}
    };
    int nbItems = sizeof(inventory) / sizeof(inventory[0]);

    // Rectangle englobant pour l'affichage
    SDL_Rect boundingRect;

    
    showInventory(nbItems, inventory, font, renderer, textColor, bgColor, &boundingRect);
    int inventoryVisible = 0;

    int quit = 0;
    SDL_Event event;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_i) {
                    // Affichage/masquage de l'inventaire lorsque la touche "i" est enfoncée
                    toggleInventoryVisibility(&boundingRect, renderer, &inventoryVisible);
                }
            }
        }

        // Effacement de l'écran
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Affichage de l'inventaire si nécessaire
        if (inventoryVisible) {
            showInventory(nbItems, inventory, font, renderer, textColor, bgColor, &boundingRect);
        }

        // Affichage effectif sur la fenêtre
        SDL_RenderPresent(renderer);
    }

    

    // Libération des ressources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}