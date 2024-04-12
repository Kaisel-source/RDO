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



#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <math.h>
#include <SDL2/SDL_ttf.h>

#define N 10
#define min(a, b) (((a) < (b)) ? (a) : (b))

const float porcen= 0.70;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 790;
const int GRID_ROWS = 10;
const int GRID_COLUMNS = 10;
const int BUTTON_SIZEx = SCREEN_WIDTH/GRID_COLUMNS;
const int BUTTON_SIZEy = SCREEN_HEIGHT*porcen/GRID_ROWS;
const int BUTTON_MARGIN = 0;






int main(){
    //creation de perso1 prenom/classe/pv/pv_max/force/equipe/mouv/iniative/range
    entite_t perso1 = create_entity("Bob", "Guerrier", 100, 100, 20, 1, 3, 15, 1);
    entite_t perso2 = create_entity("Goblin", "Brigand", 50, 50, 10, 2, 2, 10, 1);

    //matrice du plateau de combat
    entite_t  plateau_de_combat[GRID_ROWS][GRID_COLUMNS];
    init_plateau(plateau_de_combat);
    //creation du tableau de tour 
    pos_t turn[N*N];
    init_turn_order(turn);

    int FIN=0;
    

    //declare les surfaces de case sous forme de button
    Button bouton1;
    Button bouton2;
    Button buttonRect;
    Button buttonBottom; 
    Button buttonBottom2; 
    Button buttonBottom3; 
    Button buttonBottom4;
    //declare les couleur pour sdl ttf 
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Color bgColor = { 30, 30, 30, 255 };
    SDL_Rect boundingRect;

    //creation de fenetre 
    SDL_Window* window = SDL_CreateWindow("RDO TEST",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Création d'un renderer pour dessiner dans la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Calcul de la taille de la grille
    int gridWidth = GRID_COLUMNS * (BUTTON_SIZEx + BUTTON_MARGIN) - BUTTON_MARGIN;
    int gridHeight = GRID_ROWS * (BUTTON_SIZEy + BUTTON_MARGIN) - BUTTON_MARGIN;

    // Calcul de la position de la grille
    int gridX = (SCREEN_WIDTH-gridWidth);
    int gridY = (SCREEN_HEIGHT-gridHeight)/2;

    // Calcul de la position du bouton dans le coin bas droit du rectangle inferieur
    int buttonBottomX = SCREEN_WIDTH - BUTTON_SIZEx - BUTTON_MARGIN;
    int buttonBottomY = SCREEN_HEIGHT - BUTTON_SIZEy - BUTTON_MARGIN;

    //charge le fond
    SDL_Surface* backgroundSurface = IMG_Load("../img/Wallhaven.png");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }

    // initialise les image
    SDL_Surface* buttonSurface2 = IMG_Load("../img/mouv.png");
    if (buttonSurface2 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface*  persoSurface1 = IMG_Load("../img/ennemi.png");
    if (persoSurface1 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* persoSurface2 = IMG_Load("../img/allie.png");
    if (persoSurface2 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }


    SDL_Surface* fondinter= IMG_Load("../img/fondinter.png");
    if (fondinter == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    SDL_Surface* att = IMG_Load("../img/att.png");
    if (att == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }
    SDL_Surface* Fini = IMG_Load("../img/image.jpg");
    if (persoSurface2 == NULL) {
        printf("Erreur de l image : %s\n", IMG_GetError());
        return 1;
    }

    // Initialisation de SDL_ttf
    if (TTF_Init() < 0) {
        printf("Erreur lors de l'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    // Chargement de la police de caractères
    TTF_Font *font = TTF_OpenFont("../img/police.ttf", 15);
    if (font == NULL) {
        printf("Erreur lors du chargement de la police de caractères : %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    //declaration des texture 
    SDL_Texture* Text_Fini =SDL_CreateTextureFromSurface(renderer, Fini);
    SDL_Texture* buttonTexture2 = SDL_CreateTextureFromSurface(renderer, buttonSurface2);
    SDL_Texture* attText = SDL_CreateTextureFromSurface(renderer, att);
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    perso1.img = SDL_CreateTextureFromSurface(renderer, persoSurface1);
    perso2.img = SDL_CreateTextureFromSurface(renderer, persoSurface2);
    //destruction des surface  
    SDL_FreeSurface(Fini);
    SDL_FreeSurface(persoSurface2);
    SDL_FreeSurface(persoSurface1);
    SDL_FreeSurface(att);
    SDL_FreeSurface(buttonSurface2);
    SDL_FreeSurface(backgroundSurface);
    
    int mouseX, mouseY;
    int quit = 0;
    int tour=0;
    int tourmax=0;
    int action=0;

    pos_t enemiepos;
    pos_t posCible;
    pos_t pl;

    posCible.x=-1;
    posCible.y=-1;
    plateau_de_combat[0][0]=perso1;
    plateau_de_combat[5][5]=perso2;


    tourmax=nombre_Entite(plateau_de_combat);
    turn_order(plateau_de_combat,turn);

    while ((!quit)) {
        mouseX, mouseY;
        SDL_Event event;
          while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                    SDL_GetMouseState(&mouseX, &mouseY);
                        pl=plateau_cible(mouseX,mouseY,plateau_de_combat,gridX,gridY);
                        if(plateau_de_combat[turn[tour].x][turn[tour].y].equipe==2){
                            if((mouseX >= buttonBottomX && mouseX <= buttonBottomX + BUTTON_SIZEx && mouseY >= buttonBottomY && mouseY <= buttonBottomY + BUTTON_SIZEy) && (action==0)){
                                action=1;
                             }if((mouseX >= buttonBottomX && mouseX <= buttonBottomX + BUTTON_SIZEx && mouseY >= (buttonBottomY - BUTTON_SIZEy) && mouseY <= buttonBottomY) && (action==0)){
                                    action=2;
                             }if((mouseX >= (buttonBottomX - BUTTON_SIZEx) && mouseX <= buttonBottomX && mouseY >= buttonBottomY && mouseY <= buttonBottomY + BUTTON_SIZEy) && ((action==0)|| (action==5))){
                                if(tour < tourmax - 1){
                                    tour+=1;
                                }else{
                                    tour=0;
                                }
                                    action=0;
                             }if((mouseX >= (buttonBottomX - BUTTON_SIZEx) && mouseX <= buttonBottomX && mouseY >= (buttonBottomY - BUTTON_SIZEy) && mouseY <= buttonBottomY) && (action==0)){
                                action=3;
                             }if(action==1 && pl.x!=-1 && pl.y!=-1){
                                attaque_physiqe(plateau_de_combat[turn[tour].x][turn[tour].y].range,plateau_de_combat[turn[tour].x][turn[tour].y].attaque,turn[tour],pl,plateau_de_combat);
                                action=5;
                             }
                             if(action==2 && pl.x!=-1 && pl.y!=-1){
                                attaque_spell(plateau_de_combat[turn[tour].x][turn[tour].y].range,plateau_de_combat[turn[tour].x][turn[tour].y].attaque,turn[tour],pl,plateau_de_combat);
                                action=5;
                             }
                             if(action==3 && pl.x!=-1 && pl.y!=-1){
                                 mouvementJoueur(plateau_de_combat[turn[tour].x][turn[tour].y].mouv,turn[tour],pl,plateau_de_combat);
                                action=5;  
                             }
                        }
                    break;
                }
            }

        process_enemy_turn(plateau_de_combat, turn, &tour);// fait le tour de l enemie cherche a s aprocher 

        turn_order(plateau_de_combat,turn); // retri le deroulement des tour   

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL); //affiche le fond 
        dessin_plateau(plateau_de_combat,gridX,gridY,buttonTexture2,buttonRect,renderer); //affiche la grille 
  
        // Dessiner le rectangle superieur
        SDL_Rect topRect = {0, 0, SCREEN_WIDTH, gridY};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); // Couleur blanche
        SDL_RenderFillRect(renderer, &topRect);

        // Dessiner le rectangle inferieur
        SDL_Rect bottomRect = {0, gridY + gridHeight, SCREEN_WIDTH, SCREEN_HEIGHT - gridY - gridHeight};
        SDL_RenderFillRect(renderer, &bottomRect);

        // Dessiner le rectangle du bouton
        buttonBottom = initButton(buttonBottomX, buttonBottomY, BUTTON_SIZEx, BUTTON_SIZEy);
        buttonBottom2 = initButton(buttonBottomX, buttonBottomY - BUTTON_SIZEy, BUTTON_SIZEx, BUTTON_SIZEy);
        buttonBottom3 = initButton(buttonBottomX - BUTTON_SIZEx, buttonBottomY, BUTTON_SIZEx, BUTTON_SIZEy);
        buttonBottom4 = initButton(buttonBottomX - BUTTON_SIZEx, buttonBottomY - BUTTON_SIZEy, BUTTON_SIZEx, BUTTON_SIZEy);



        // Remplir le rectangle du bouton
        setButtonImage(renderer, attText, &buttonBottom.rect);
        setButtonImage(renderer, attText, &buttonBottom2.rect);
        setButtonImage(renderer, attText, &buttonBottom3.rect);
        setButtonImage(renderer, attText, &buttonBottom4.rect);

        //affiche stat si entite mob cliquer 
        if ((pl.x >= 0 && pl.x < GRID_ROWS) && (pl.y >= 0 && pl.y < GRID_COLUMNS)) {
            if ((action == 0 || action == 5) && (plateau_de_combat[pl.x][pl.y].classe>0) && (plateau_de_combat[pl.x][pl.y].pv>0)) {
                drawTextWithStats(renderer, font, plateau_de_combat[pl.x][pl.y].prenom, plateau_de_combat[pl.x][pl.y].classe,plateau_de_combat[pl.x][pl.y].pv,plateau_de_combat[pl.x][pl.y].attaque,0,gridY + gridHeight, 250, 300, 0, textColor, bgColor, &boundingRect);
            }
        }

        //verifie si une equipe a gagner ou non et renvoi la victoire ou defaite pour le joueur (1 = win 0=combat en cour et -1 pour defaite)
        FIN=FinDecombat(turn,1,2,plateau_de_combat);


        if(FIN==-1){
            SDL_RenderCopy(renderer, Text_Fini, NULL, NULL); //ecran game over
        }if(FIN==1){
            printf("ta gagne "); //win 
        }

    
    SDL_RenderPresent(renderer); //affiche 
    
    }


    //detruit tout 
    SDL_DestroyTexture(Text_Fini);
    SDL_DestroyTexture(perso1.img);
    SDL_DestroyTexture(perso2.img);
    SDL_DestroyTexture(attText);
    SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}