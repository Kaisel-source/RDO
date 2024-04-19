#ifndef ENEMIE_H
#define ENEMIE_H

#include "../common/common.h"  // Inclure le fichier d'en-tête des entités




// Déclaration des fonctions pour le fichier enemie.c
/**
 * @brief verifie si la position d une entite d une equipe differente se trouve a porter 
 * 
 * @param pos position allier
 * @param enemie position de l enemie 
 * @param range la porter de l entite a la position pos
 * @return int 1 si oui sinon 0
 */
int est_A_porter(pos_t pos, pos_t enemie, int range);

/**
 * @brief trouve la position dans la matrice la position la plus proche 
 * 
 * @param mat plateau d entite 
 * @param pos position de depart 
 * @param equipe enemie le plus proche
 * @param mouv nombre de case max qui peut sauter
 * @return pos_t position sur laquelle il peut se deplacer
 */
pos_t detecte_mouv(entite_t mat[N][N], pos_t pos, int equipe, int mouv);

/**
 * @brief renvoie la position de l enemie le plus proche
 * 
 * @param mat plateau
 * @param pos position  de l entite 
 * @param equipe equipe de l entite 
 * @return pos_t position de l enemie le plus proche
 */
pos_t detecte_enemie(entite_t mat[N][N], pos_t pos, int equipe);

/**
 * @brief deplace une entite 
 * 
 * @param plateau plateau 
 * @param pos position de depart
 * @param perso entite a deplcer
 */
void deplace_Plus_Proche(entite_t plateau[N][N], pos_t pos, entite_t perso);

/**
 * @brief fais le tour des IA 
 * 
 * @param plateau_de_combat plateau
 * @param turn tableau de position du turn order 
 * @param tour position dans le tableau actuelle 
 */
void process_enemy_turn(entite_t plateau_de_combat[N][N], pos_t turn[], int *tour);

#endif /* ENEMIE_H */
