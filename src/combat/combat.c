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





#include "../../include/common/common.h"



/*
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
            showInventory(inventory, font, renderer, textColor, bgColor, &boundingRect);
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
*/