#ifndef TURN_ORDER_H
#define TURN_ORDER_H

#include "../common/common.h"



/**
 * @brief Fonction pour initialiser le turn order
 * 
 * @param turn Le tableau pour stocker l'ordre des tours
 */
void init_turn_order(pos_t turn[N*N]);

/**
 * @brief Fonction pour trier les positions dans l'ordre décroissant des entités en fonction de leur stat initiative dans un tableau par tri sélection
 * 
 * @param mat Le plateau de jeu contenant les entités
 * @param turn Le tableau pour stocker l'ordre des tours
 */
void turn_order(entite_t mat[N][N], pos_t turn[N*N]);

/**
 * @brief Fonction pour afficher l'ordre des tours
 * 
 * @param turn Le tableau contenant l'ordre des tours
 */
void afficher_turn_order(pos_t turn[N*N]);

#endif /* TURN_ORDER_H */
