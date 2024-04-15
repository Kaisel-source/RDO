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
       SDL_Delay(1000);
    }

    SDL_DestroyTexture(perso1.img);
    SDL_DestroyTexture(perso2.img);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

