
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <math.h>


#define N 10
#define min(a, b) (((a) < (b)) ? (a) : (b))

const float porcen= 0.85;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 790;
const int GRID_ROWS = 10;
const int GRID_COLUMNS = 10;
const int BUTTON_SIZEx = SCREEN_WIDTH/GRID_COLUMNS;
const int BUTTON_SIZEy = SCREEN_HEIGHT*porcen/GRID_ROWS;
const int BUTTON_MARGIN = 0;


typedef struct{
    int pv;
    int pv_max;
    int attaque;
    int alive;
    SDL_Texture * img;
    int equipe;
    int mouv;
}entite_t;

typedef struct{
    int x;
    int y;
}pos_t;





pos_t detecte_enemie_proche(entite_t  mat[N][N],pos_t pos,int equipe,int mouv){
    int i,j;
    int plus_procheX=-1,plus_procheY=-1;
    double distance_min = INFINITY;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){       //parcours la matrice 
            if(mat[i][j].equipe!=equipe && mat[i][j].equipe!=0){   //Si il trouve un enemie
                double distance = sqrt(pow(i-pos.y, 2) + pow(j-pos.x, 2));
                if(distance < distance_min){
                    distance_min = distance;
                    plus_procheX = j;
                    plus_procheY = i;
                }
            }
        }
    }
    // Déplacement d'une case vers l'ennemi le plus proche
    if (plus_procheX != -1 && plus_procheY != -1) {
        // Calcul du déplacement
        int deltaX = plus_procheX - pos.x;
        int deltaY = plus_procheY - pos.y;

    if (abs(deltaX) > abs(deltaY)) {
            pos.x += (deltaX > 0) ? min(mouv, abs(deltaX)) : -min(mouv, abs(deltaX));
        } else {
            pos.y += (deltaY > 0) ? min(mouv, abs(deltaY)) : -min(mouv, abs(deltaY));
        }
    }

    // Renvoie de la nouvelle position
    return pos;
}




void deplacePlusProche(entite_t  plateau[N][N],pos_t pos,entite_t  perso){
    pos_t dep;
    dep=detecte_enemie_proche(plateau,pos,perso.equipe,perso.mouv);
    plateau[pos.x][pos.y].pv=1;
    plateau[pos.x][pos.y].equipe=0;
    plateau[pos.x][pos.y].pv_max=0;
    plateau[pos.x][pos.y].attaque=0;
    plateau[dep.x][dep.y]=perso;
}



void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect) {
    SDL_RenderCopy(renderer, imageTexture, NULL, buttonRect);
}

typedef struct {
    SDL_Rect rect;       // Rectangle définissant la position et la taille du bouton
    SDL_Texture* texture; // Texture du bouton (à générer avec SDL_CreateTextureFromSurface())
} Button;



SDL_Rect getButtonRect(int bouttonx, int bouttony) {
    Button buttonRect;
    buttonRect.rect.x = bouttonx;
    buttonRect.rect.y = bouttony;
    buttonRect.rect.w = BUTTON_SIZEx;
    buttonRect.rect.h = BUTTON_SIZEy;
    
    return buttonRect.rect;
}



int main(){

    entite_t  perso1;
    perso1.pv=100;
    perso1.pv_max=100;
    perso1.attaque=10;
    perso1.equipe=1;
    perso1.mouv=3;

    entite_t perso2;
    perso2.pv=100;
    perso2.pv_max=100;
    perso2.attaque=10;
    perso2.equipe=2;
    perso2.mouv=3;

    pos_t pos1;
    pos_t pos2;

    int cpt1;
    

    entite_t  plateau_de_combat[GRID_ROWS][GRID_COLUMNS];
    for(int i=0;i<GRID_ROWS;i++){
        for(int j=0;j<GRID_COLUMNS;j++){
            plateau_de_combat[i][j].pv=0;
            plateau_de_combat[i][j].pv_max=0;
            plateau_de_combat[i][j].equipe=0;
            plateau_de_combat[i][j].attaque=0;
        }
    }


    //declare les surfaces de case sous forme de button
    Button bouton1;
    Button bouton2;
    Button buttonRect;

    //creation de fenetre 
    SDL_Window* window = SDL_CreateWindow("RDO TEST",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Création d'un renderer pour dessiner dans la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Calcul de la taille de la grille
    int gridWidth = GRID_COLUMNS * (BUTTON_SIZEx + BUTTON_MARGIN) - BUTTON_MARGIN;
    int gridHeight = GRID_ROWS * (BUTTON_SIZEy + BUTTON_MARGIN) - BUTTON_MARGIN;


    // Dessiner le rectangle supérieur
    SDL_Rect topRect = {0, 0, SCREEN_WIDTH, gridY};
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur blanche
    SDL_RenderFillRect(renderer, &topRect);

    // Dessiner le rectangle inférieur
    SDL_Rect bottomRect = {0, gridY + gridHeight, SCREEN_WIDTH, SCREEN_HEIGHT - gridY - gridHeight};
    SDL_RenderFillRect(renderer, &bottomRect);

    // Calcul de la position du bouton dans le coin bas droit du rectangle inférieur
    int buttonBottomX = SCREEN_WIDTH - BUTTON_SIZEx - BUTTON_MARGIN;
    int buttonBottomY = SCREEN_HEIGHT - BUTTON_SIZEy - BUTTON_MARGIN;


    // initialise les image
    SDL_Surface* buttonSurface2 = IMG_Load("../img/New Piskel.png");
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

    SDL_Texture* buttonTexture2 = SDL_CreateTextureFromSurface(renderer, buttonSurface2);
    SDL_Texture* attText = SDL_CreateTextureFromSurface(renderer, att);

    perso1.img = SDL_CreateTextureFromSurface(renderer, persoSurface1);

    perso2.img = SDL_CreateTextureFromSurface(renderer, persoSurface2);
    
    // Dessiner le rectangle du bouton
    Button buttonBottom;
    buttonBottom.rect.x = buttonBottomX;
    buttonBottom.rect.y = buttonBottomY;
    buttonBottom.rect.w = BUTTON_SIZEx;
    buttonBottom.rect.h = BUTTON_SIZEy;

    // Remplir le rectangle du bouton
    setButtonImage(renderer, attText, &buttonBottom.rect);

    //charge le fond
    SDL_Surface* backgroundSurface = IMG_Load("../img/Wallhaven.png");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }



    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    // Calcul de la position de la grille
    int gridX = (SCREEN_WIDTH-gridWidth);
    int gridY = (SCREEN_HEIGHT-gridHeight)/2;

    int action=0;
    int mouseX, mouseY;
    int quit = 0;
    int cpt=0;
    plateau_de_combat[0][0]=perso1;
    plateau_de_combat[5][5]=perso2;




    


    while (!quit) {
        mouseX, mouseY;
        SDL_Event event;
          while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT:
                        quit = 1;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                         SDL_GetMouseState(&mouseX, &mouseY);
                        for (int row = 0; row < GRID_ROWS; row++) {
                            for (int column = 0; column < GRID_COLUMNS; column++) {
                                int buttonX = gridX + column * (BUTTON_SIZEx + BUTTON_MARGIN);
                                int buttonY = gridY + row * (BUTTON_SIZEy + BUTTON_MARGIN);
                                if (mouseX >= buttonX && mouseX <= buttonX + BUTTON_SIZEx && mouseY >= buttonY && mouseY <= buttonY + BUTTON_SIZEy) {
                                    printf("Bouton (%d, %d) clique !\n", row, column);
                                    printf("pv = %d !\n", plateau_de_combat[row][column].pv);
                                    printf("equipe = %d !\n", plateau_de_combat[row][column].equipe);
                                    action=1;
                                }
                            }
                        }
                        break;

                }
            }

        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);
        for (int row = 0; row < GRID_ROWS; row++) {
            for (int column = 0; column < GRID_COLUMNS; column++) {
                // Calcul de la position du bouton dans la grille
                int buttonX = gridX + column * (BUTTON_SIZEx + BUTTON_MARGIN);
                int buttonY = gridY + row * (BUTTON_SIZEy + BUTTON_MARGIN);
                // Dessiner le rectangle du bouton
                buttonRect.rect.x =  buttonX;   
                buttonRect.rect.y =  buttonY;
                buttonRect.rect.w =  BUTTON_SIZEx;
                buttonRect.rect.h = BUTTON_SIZEy;
                if(plateau_de_combat[row][column].pv>0){
                    setButtonImage(renderer,plateau_de_combat[row][column].img,&buttonRect.rect);
                    pos1.x=row;
                    pos1.y=column;
                    deplacePlusProche(plateau_de_combat,pos1,plateau_de_combat[row][column]); 
                }else{
                    setButtonImage(renderer,buttonTexture2,&buttonRect.rect);
                }

            }
        }   




        SDL_RenderPresent(renderer);
    }

    



    SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}