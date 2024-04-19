#include "../../include/common/common.h"

// Fonction pour initialiser le turn order
void init_turn_order(pos_t turn[N*N]) {
    // Parcourir le plateau de jeu et stocker les positions des entités vivantes
    for (int i = 0; i < (N*N); i++) {
        turn[i].x = 0;
        turn[i].y = 0;
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
    init_turn_order(turn);
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
    int max;
    // Tri des entités en fonction de leur initiative
    for (int k = 0; k < cpt - 1; k++) {
        max = k;
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


void afficher_turn_order(pos_t turn[N*N]) {
    printf("Turn order :\n");
    for (int i = 0; i < N*N; i++) {
        printf("(%d, %d) \n ", turn[i].x, turn[i].y);
    }
    printf("\n");
}







