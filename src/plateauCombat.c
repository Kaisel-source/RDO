#include "plateauCombat.h"



int nombre_Entite(entite_t plateau[N][N]){
    int nb=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(plateau[i][j].pv>0){
                nb++;
            }
        }
    }
    return nb;
}


/**
 * @brief 
 * @param plateau
 */
void init_plateau(entite_t plateau[N][N]){
    for(int i=0;i<GRID_ROWS;i++){
        for(int j=0;j<GRID_COLUMNS;j++){
            initialiserEntite(&plateau[i][j]);
        }
    }
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
    pos_cible.x=x;
    pos_cible.y=y;
    return pos_cible;
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



int FinDecombat(pos_t turn[N*N], int EquipeGagnante, int EquipePerdant, entite_t plateau[N][N]) {
    int cpt1 = 0, cpt2 = 0;
    for (int i = 0; i < (N*N); i++) {
        // Vérifier que les coordonnées x et y sont dans les limites du plateau
        if (turn[i].x >= 0 && turn[i].x < N && turn[i].y >= 0 && turn[i].y < N) {
            if (plateau[turn[i].x][turn[i].y].equipe == EquipeGagnante) {
                cpt1++;
            }
            if (plateau[turn[i].x][turn[i].y].equipe == EquipePerdant) {
                cpt2++;
            }
        }
    }
    if (cpt1 == 0) {
        return 1;
    }else if (cpt2 == 0) {
        return -1;
    }
    return 0;
}



