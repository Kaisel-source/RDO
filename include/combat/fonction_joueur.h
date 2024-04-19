#ifndef FONCTION_JOUEUR_H
#define FONCTION_JOUEUR_H

#include "../common/common.h"



/**
 * @brief Fonction pour déplacer une entité joueur sur le plateau de jeu
 * 
 * @param dep Le nombre de cases que l'entité peut se déplacer
 * @param pos_perso La position actuelle de l'entité
 * @param pos_cibler La position vers laquelle l'entité veut se déplacer
 * @param plateau Le plateau de jeu contenant les entités
 * @return int 1 si le déplacement a réussi, 0 sinon
 */
int mouvement_Joueur(int dep, pos_t pos_perso, pos_t pos_cibler, entite_t plateau[N][N]);

/**
 * @brief Fonction pour lancer un sort sur une case ciblée par une entité joueur
 * 
 * @param range La portée du sort
 * @param dmg Les dégâts infligés par le sort
 * @param pos_perso La position de l'entité joueur lançant le sort
 * @param pos_cibler La position de la case ciblée par le sort
 * @param plateau Le plateau de jeu contenant les entités
 * @return int 1 si le sort a été lancé avec succès, 0 sinon
 */
int attaque_spell(int range, int dmg, pos_t pos_perso, pos_t pos_cibler, entite_t plateau[N][N]);

/**
 * @brief Fonction pour effectuer une attaque physique sur une case ciblée par une entité joueur
 * 
 * @param range La portée de l'attaque physique
 * @param dmg Les dégâts infligés par l'attaque physique
 * @param pos_perso La position de l'entité joueur effectuant l'attaque
 * @param pos_cibler La position de la case ciblée par l'attaque
 * @param plateau Le plateau de jeu contenant les entités
 * @return int 1 si l'attaque physique a réussi, 0 sinon
 */
int attaque_physiqe(int range, int dmg, pos_t pos_perso, pos_t pos_cibler, entite_t plateau[N][N]);

#endif /* FONCTION_JOUEUR_H */
