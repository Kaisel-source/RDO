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

/**
 * @brief ensemble des caracteristique des ennemies,allies
 * et des personnages jouable.
 * 
 */
typedef struct{
    int pv;
    int pv_max;
    int attaque;
    int alive;
    SDL_Texture * img;
    int equipe;
    int mouv;
    int initiative;
    int range;
}entite_t;


/**
 * @brief position 
 * 
 */
typedef struct{
    int x;
    int y;
}pos_t;

/**
 * @brief position + image d un espace defeni
 * 
 */
typedef struct {
    SDL_Rect rect;       // Rectangle définissant la position et la taille du bouton
    SDL_Texture* texture; // Texture du bouton (à générer avec SDL_CreateTextureFromSurface())
} Button;




/**
 * @brief retourne la position la plus proche en fonction de se nombre de point de mouvement vers l enemie le plus proche
 * 
 * @param mat 
 * @param pos 
 * @param equipe 
 * @param mouv 
 * @return pos_t 
 */
pos_t detecte_mouv(entite_t mat[N][N], pos_t pos, int equipe, int mouv) {
    int i, j;
    int plus_procheX = -1, plus_procheY = -1;
    double distance_min = INFINITY;
    pos_t nouvelle_pos = pos; // Créer une nouvelle variable pour stocker la nouvelle position
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) { // Parcours la matrice 
            if (mat[i][j].equipe != equipe && mat[i][j].equipe != 0) { // Si il trouve un ennemi
                double distance = sqrt(pow(i - pos.y, 2) + pow(j - pos.x, 2));
                if (distance < distance_min) {
                    distance_min = distance;
                    plus_procheX = j;
                    plus_procheY = i;
                }
            }
        }
    }
    // Détermination de la nouvelle position sans modifier la position actuelle
    if (plus_procheX != -1 && plus_procheY != -1) {
        // Calcul du déplacement
        int deltaX = plus_procheX - pos.x;
        int deltaY = plus_procheY - pos.y;
        if (abs(deltaX) > abs(deltaY)) {
            nouvelle_pos.x += (deltaX > 0) ? min(mouv, abs(deltaX)) : -min(mouv, abs(deltaX));
        } else {
            nouvelle_pos.y += (deltaY > 0) ? min(mouv, abs(deltaY)) : -min(mouv, abs(deltaY));
        }
    }
    // Renvoie de la nouvelle position
    return nouvelle_pos;
}

/**
 * @brief idem que detecte mouv a l exeption ne renvoie juste la pose de l enemie
 * 
 * @param mat 
 * @param pos 
 * @param equipe 
 * @return pos_t 
 */
pos_t detecte_enemie(entite_t mat[N][N], pos_t pos, int equipe) {
    int i, j;
    int plus_procheX = -1, plus_procheY = -1;
    double distance_min = INFINITY;
    pos_t nouvelle_pos; // Variable pour stocker la nouvelle position

    // Parcours la matrice
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            // Vérifie si l'entité dans la case est un ennemi et que ce n'est pas une case vide
            if (mat[i][j].equipe != equipe && mat[i][j].equipe != 0) {
                // Calcule la distance entre la position actuelle et l'ennemi
                double distance = sqrt(pow(i - pos.y, 2) + pow(j - pos.x, 2));
                // Met à jour la position de l'ennemi le plus proche si la distance est plus petite
                if (distance < distance_min) {
                    distance_min = distance;
                    plus_procheX = j;
                    plus_procheY = i;
                }
            }
        }
    }

    // Assigne les coordonnées de la nouvelle position trouvée
    nouvelle_pos.x = plus_procheX;
    nouvelle_pos.y = plus_procheY;

    // Retourne la nouvelle position
    return nouvelle_pos;
}

/**
 * @brief deplace une entite en fonction de entite.mouv
 * 
 * @param plateau 
 * @param pos 
 * @param perso 
 */
void deplacePlusProche(entite_t plateau[N][N], pos_t pos, entite_t perso) {
    // Trouver la nouvelle position de l'ennemi le plus proche sans modifier la position actuelle
    pos_t nouvelle_pos = detecte_mouv(plateau, pos, perso.equipe, perso.mouv);
    // Déplacer l'entité vers la nouvelle position de l'ennemi le plus proche
    plateau[pos.x][pos.y].pv=0;
    plateau[pos.x][pos.y].pv_max=0;
    plateau[pos.x][pos.y].equipe=0;
    plateau[pos.x][pos.y].attaque=0;
    plateau[pos.x][pos.y].initiative=0;
    plateau[pos.x][pos.y].range=0;
    plateau[nouvelle_pos.x][nouvelle_pos.y] = perso;
}

/**
 * @brief Retourne si un ennemi est à portée d'un autre ennemi
 * 
 * @param plateau Le plateau de jeu contenant les entités
 * @param pos La position de l'entité depuis laquelle la portée est vérifiée
 * @param enemie La position de l'ennemi à vérifier
 * @return int 1 si un ennemi est à portée, 0 sinon
 */
int estAporter(entite_t plateau[N][N], pos_t pos, pos_t enemie,int range) {
    
    // Calculer la distance entre les deux positions
    int distance = abs(pos.x - enemie.x) + abs(pos.y - enemie.y);

    if (distance <= range) {
        return 1;
    } else {
        return 0;
    }
}

/**
 * @brief trie les position dans l orde decroissant les entite en fonction de leur stat initiative dans un tableau par tri selection
 * 
 * @param mat 
 * @param turn 
 */
void turn_order(entite_t mat[N][N], pos_t turn[N*N]) {
    int cpt = 0;
    pos_t temp;

    // Stocker les positions des entités vivantes dans le tableau turn
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j].pv > 0) {
                turn[cpt].x = i;
                turn[cpt].y = j;
                cpt++;
            }
        }
    }

    // Tri des entités en fonction de leur initiative
    for (int k = 0; k < cpt - 1; k++) {
        int max = k;
        for (int u = k + 1; u < cpt; u++) {
            if (mat[turn[u].x][turn[u].y].initiative > mat[turn[max].x][turn[max].y].initiative) { 
                max = u;
            }
        }
        if (max != k) {
            temp = turn[k];
            turn[k] = turn[max];
            turn[max] = temp;
        }
    }
}


/**
 * @brief colle une img sur un espace defini
 * 
 * @param renderer 
 * @param imageTexture 
 * @param buttonRect 
 */
void setButtonImage(SDL_Renderer* renderer, SDL_Texture* imageTexture, SDL_Rect* buttonRect) {
    SDL_RenderCopy(renderer, imageTexture, NULL, buttonRect);
}


/**
 * @brief infige des dommage avec une attaque sur une case cibler et verifie si possible
 * @param pos_cibler
 * @param range 
 * @param dmg 
 * @param pos_perso
 * @param plateau
 */
int attaque_physiqe(int range,int dmg,pos_t pos_perso,pos_t pos_cibler,entite_t plateau[N][N]){
        // Vérifier si la cible est à portée
    int distance = abs(pos_perso.x - pos_cibler.x) + abs(pos_perso.y - pos_cibler.y);
    if ((distance <= range) && (plateau[pos_cibler.x][pos_cibler.y].pv>0)) {
        // Appliquer les dégâts à la cible
        printf("Attaque physique réussie ! Dégâts infligés : %d\n", dmg);
        plateau[pos_cibler.x][pos_cibler.y].pv-=dmg;
        return 1;
    } else {
        printf("Cible hors de portée ou cible incorecte (vise mieux)!\n");
        return 0;
    }
}

/**
 * @brief infige des dommage  avec un spell sur une case cibler et verifie si possible
 * @param pos_cibler
 * @param range 
 * @param dmg 
 * @param pos_perso
 * @param plateau
 */
int attaque_spell(int range,int dmg,pos_t pos_perso,pos_t pos_cibler,entite_t plateau[N][N]){
    // Vérifier si la cible est à portée
    int distance = abs(pos_perso.x - pos_cibler.x) + abs(pos_perso.y - pos_cibler.y);
    if ((distance <= range) && (plateau[pos_cibler.x][pos_cibler.y].pv>0)) {
        // Appliquer les dégâts à la cible
        printf("Sort lancé avec succès ! Dégâts infligés : %d\n", dmg);
        plateau[pos_cibler.x][pos_cibler.y].pv-=dmg;
        return 1;
    } else {
        printf("Cible hors de portée pour le sort ou cible incorecte (vise mieux) !\n");
        return 0;
    }
}

/**
 * @brief retoune un espace defenie sous la forme d un rectangle 
 * 
 * @param bouttonx 
 * @param bouttony 
 * @return SDL_Rect 
 */
SDL_Rect getButtonRect(int bouttonx, int bouttony) {
    Button buttonRect;
    buttonRect.rect.x = bouttonx;
    buttonRect.rect.y = bouttony;
    buttonRect.rect.w = BUTTON_SIZEx;
    buttonRect.rect.h = BUTTON_SIZEy;
    
    return buttonRect.rect;
}

/**
 * @brief Construct a new void object
 * 
 * @param mouseX 
 * @param mouseY 
 */
pos_t plateau_cible(int mouseX,int mouseY,entite_t plateau[N][N],int gridX,int gridY){
    pos_t pos_cible;
    int x=-1,y=-1;
    SDL_Event event;
    event.type = SDL_MOUSEBUTTONUP;
    while(event.type != SDL_MOUSEBUTTONDOWN){
        for (int row = 0; row < GRID_ROWS; row++) {
        for (int column = 0; column < GRID_COLUMNS; column++) {
            int buttonX = gridX + column * (BUTTON_SIZEx + BUTTON_MARGIN);
            int buttonY = gridY + row * (BUTTON_SIZEy + BUTTON_MARGIN);
            if (mouseX >= buttonX && mouseX <= buttonX + BUTTON_SIZEx && mouseY >= buttonY && mouseY <= buttonY + BUTTON_SIZEy) {
                    printf("Bouton (%d, %d) clique !\n", row, column);
                    printf("pv = %d !\n", plateau[row][column].pv);
                    printf("equipe = %d !\n", plateau[row][column].equipe);
                    x=row;
                    y=column;
            }
        }
    }
    SDL_PollEvent(&event);    
    }
    pos_cible.x=x;
    pos_cible.y=y;
    return pos_cible;
}

/**
 * @brief 
 * @param plateau
 */
void init_plateau(entite_t plateau[N][N]){
    for(int i=0;i<GRID_ROWS;i++){
        for(int j=0;j<GRID_COLUMNS;j++){
            plateau[i][j].pv=0;
            plateau[i][j].pv_max=0;
            plateau[i][j].equipe=0;
            plateau[i][j].attaque=0;
            plateau[i][j].initiative=0;
            plateau[i][j].range=0;
        }
    }
}

/**
 * @brief fait le dessin d un echequier
 * 
 * @param plateau_de_combat 
 * @param gridX 
 * @param gridY 
 * @param rien 
 * @param buttonRect 
 * @param renderer 
 */
void dessin_plateau(entite_t plateau_de_combat[N][N],int gridX,int gridY, SDL_Texture* rien,Button buttonRect,SDL_Renderer* renderer){
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
            }else{
                setButtonImage(renderer,rien,&buttonRect.rect);
            }

        }
    } 
}


int main(){

    entite_t  perso1;
    perso1.pv=100;
    perso1.pv_max=100;
    perso1.attaque=40;
    perso1.equipe=1;
    perso1.mouv=3;
    perso1.initiative=61;
    perso1.range=2;

    entite_t perso2;
    perso2.pv=100;
    perso2.pv_max=100;
    perso2.attaque=40;
    perso2.equipe=2;
    perso2.mouv=3;
    perso2.initiative=51;
    perso2.range=2;

    pos_t pos1;
    pos_t pos2;
    pos_t turn[N*N];

    int cpt1;


    

    entite_t  plateau_de_combat[GRID_ROWS][GRID_COLUMNS];
    init_plateau(plateau_de_combat);

    //declare les surfaces de case sous forme de button
    Button bouton1;
    Button bouton2;
    Button buttonRect;

    //creation de fenetre 
    SDL_Window* window = SDL_CreateWindow("RDO TEST",
    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    // Création d'un renderer pour dessiner dans la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //charge le fond
    SDL_Surface* backgroundSurface = IMG_Load("../img/Wallhaven.png");
    if (backgroundSurface == NULL) {
        printf("Erreur de chargement de l'image de fond : %s\n", IMG_GetError());
        return 1;
    }



    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    

    // Calcul de la taille de la grille
    int gridWidth = GRID_COLUMNS * (BUTTON_SIZEx + BUTTON_MARGIN) - BUTTON_MARGIN;
    int gridHeight = GRID_ROWS * (BUTTON_SIZEy + BUTTON_MARGIN) - BUTTON_MARGIN;

    // Calcul de la position de la grille
    int gridX = (SCREEN_WIDTH-gridWidth);
    int gridY = (SCREEN_HEIGHT-gridHeight)/2;

    // Calcul de la position du bouton dans le coin bas droit du rectangle inferieur
    int buttonBottomX = SCREEN_WIDTH - BUTTON_SIZEx - BUTTON_MARGIN;
    int buttonBottomY = SCREEN_HEIGHT - BUTTON_SIZEy - BUTTON_MARGIN;

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

    SDL_Texture* buttonTexture2 = SDL_CreateTextureFromSurface(renderer, buttonSurface2);
    SDL_Texture* attText = SDL_CreateTextureFromSurface(renderer, att);

    perso1.img = SDL_CreateTextureFromSurface(renderer, persoSurface1);

    perso2.img = SDL_CreateTextureFromSurface(renderer, persoSurface2);
    
    



    int action=0;
    int mouseX, mouseY;
    int quit = 0;
    int cpt=0;
    int tour=0;
    int tourmax=0;
    int time=0;
    pos_t enemiepos;
    pos_t posCible;
    posCible.x=-1;
    posCible.y=-1;
    int condition=0;
    int interrupt=0;
    plateau_de_combat[0][0]=perso1;
    plateau_de_combat[5][5]=perso2;
    turn_order(plateau_de_combat,turn);

    for(int i=0;i<GRID_ROWS;i++){
        for(int j=0;j<GRID_COLUMNS;j++){
            if(plateau_de_combat[i][j].pv>0){
                tourmax++;
            }
        }
    }





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
                        printf("Bouton %d %d !\n",posCible.x,posCible.y);
                        if(plateau_de_combat[turn[tour].x][turn[tour].y].equipe==2){
                            if(mouseX >= buttonBottomX && mouseX <= buttonBottomX + BUTTON_SIZEx && mouseY >= buttonBottomY && mouseY <= buttonBottomY + BUTTON_SIZEy){
                                printf("Bouton attaque clique !\n");
                                posCible=plateau_cible(mouseX,mouseY,plateau_de_combat,gridX,gridY);
                                attaque_spell(plateau_de_combat[turn[tour].x][turn[tour].y].range,plateau_de_combat[turn[tour].x][turn[tour].y].attaque,turn[tour],posCible,plateau_de_combat);
                                printf("Bouton %d %d !\n",posCible.x,posCible.y);
                             }if(mouseX >= buttonBottomX && mouseX <= buttonBottomX + BUTTON_SIZEx && mouseY >= (buttonBottomY - BUTTON_SIZEy) && mouseY <= buttonBottomY){
                                    printf("Bouton spell !\n");

                             }if(mouseX >= (buttonBottomX - BUTTON_SIZEx) && mouseX <= buttonBottomX && mouseY >= buttonBottomY && mouseY <= buttonBottomY + BUTTON_SIZEy){
                                if(tour < tourmax - 1){
                                    tour+=1;
                                    printf("end tour joueur %d !\n",tour);
                                }else{
                                    tour=0;
                                    printf("SS end tour joueur %d !\n",tour);
                                }
                             }if(mouseX >= (buttonBottomX - BUTTON_SIZEx) && mouseX <= buttonBottomX && mouseY >= (buttonBottomY - BUTTON_SIZEy) && mouseY <= buttonBottomY){
                                    printf("inventory  !\n");
                             }if(condition==0){

                             }
                        }
                    break;
                }
            }
            if (plateau_de_combat[turn[tour].x][turn[tour].y].equipe == 1) {
                enemiepos=detecte_enemie(plateau_de_combat,turn[tour],1);
                if(estAporter(plateau_de_combat,turn[tour],enemiepos,plateau_de_combat[turn[tour].x][turn[tour].y].range)==1){
                    plateau_de_combat[enemiepos.x][enemiepos.y].pv-=plateau_de_combat[turn[tour].x][turn[tour].y].attaque;
                    printf("estaporter \n");
                }else{
                    deplacePlusProche(plateau_de_combat, turn[tour], plateau_de_combat[turn[tour].x][turn[tour].y]);
                }
                    tour += 1;
                    printf("end tour enemie %d !\n",tour);
            }

        turn_order(plateau_de_combat,turn);


        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        dessin_plateau(plateau_de_combat,gridX,gridY,buttonTexture2,buttonRect,renderer);
  
        // Dessiner le rectangle superieur
        SDL_Rect topRect = {0, 0, SCREEN_WIDTH, gridY};
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0); // Couleur blanche
        SDL_RenderFillRect(renderer, &topRect);

        // Dessiner le rectangle inferieur
        SDL_Rect bottomRect = {0, gridY + gridHeight, SCREEN_WIDTH, SCREEN_HEIGHT - gridY - gridHeight};
        SDL_RenderFillRect(renderer, &bottomRect);

        // Dessiner le rectangle du bouton
        Button buttonBottom;
        buttonBottom.rect.x = buttonBottomX;
        buttonBottom.rect.y = buttonBottomY;
        buttonBottom.rect.w = BUTTON_SIZEx;
        buttonBottom.rect.h = BUTTON_SIZEy;

        Button buttonBottom2;
        buttonBottom2.rect.x = buttonBottomX;
        buttonBottom2.rect.y = buttonBottomY - BUTTON_SIZEy;
        buttonBottom2.rect.w = BUTTON_SIZEx;
        buttonBottom2.rect.h = BUTTON_SIZEy;

        Button buttonBottom3;
        buttonBottom3.rect.x = buttonBottomX - BUTTON_SIZEx;
        buttonBottom3.rect.y = buttonBottomY;
        buttonBottom3.rect.w = BUTTON_SIZEx;
        buttonBottom3.rect.h = BUTTON_SIZEy;

        Button buttonBottom4;
        buttonBottom4.rect.x = buttonBottomX - BUTTON_SIZEx;
        buttonBottom4.rect.y = buttonBottomY - BUTTON_SIZEy;
        buttonBottom4.rect.w = BUTTON_SIZEx;
        buttonBottom4.rect.h = BUTTON_SIZEy;



    // Remplir le rectangle du bouton
    setButtonImage(renderer, attText, &buttonBottom.rect);
    setButtonImage(renderer, attText, &buttonBottom2.rect);
    setButtonImage(renderer, attText, &buttonBottom3.rect);
    setButtonImage(renderer, attText, &buttonBottom4.rect);



    SDL_RenderPresent(renderer);
    
    }

    
    SDL_DestroyTexture(perso1.img);
    SDL_DestroyTexture(perso2.img);
    SDL_DestroyTexture(attText);
    SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}