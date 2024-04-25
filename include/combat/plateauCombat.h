/**
 * @file plateauCombat.h
 * @author Mael Gaumont
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/
#ifndef PLATEAU_COMBAT_H
#define PLATEAU_COMBAT_H

#include "../common/common.h" 



/**
 * @brief Fonction pour compter le nombre d'entités présentes sur le plateau de combat
 * 
 * @param plateau Le plateau de combat contenant les entités
 * @return int Le nombre d'entités présentes sur le plateau de combat
 */
int nombre_Entite(entite_t plateau[N][N]);

/**
 * @brief Fonction pour initialiser le plateau de combat en plaçant des entités vides
 * 
 * @param plateau Le plateau de combat à initialiser
 */
void init_plateau(entite_t plateau[N][N]);

/**
 * @brief Fonction pour déterminer la case ciblée sur le plateau de combat en fonction des coordonnées de la souris
 * 
 * @param mouseX La position en X de la souris
 * @param mouseY La position en Y de la souris
 * @param plateau Le plateau de combat contenant les entités
 * @param gridX La position X de la grille sur l'écran
 * @param gridY La position Y de la grille sur l'écran
 * @return pos_t La position de la case ciblée
 */
pos_t plateau_cible(int mouseX, int mouseY,int gridX, int gridY);

/**
 * @brief Fonction pour dessiner le plateau de combat sur l'écran
 * 
 * @param plateau_de_combat Le plateau de combat contenant les entités
 * @param gridX La position X de la grille sur l'écran
 * @param gridY La position Y de la grille sur l'écran
 * @param rien La texture à utiliser pour les cases vides
 * @param buttonRect La structure de bouton à utiliser pour dessiner les cases
 * @param renderer Le renderer SDL à utiliser pour dessiner
 */
void dessin_plateau(entite_t plateau_de_combat[N][N], int gridX, int gridY, SDL_Texture* rien, Button buttonRect, SDL_Renderer* renderer);

/**
 * @brief Fonction pour déterminer si le combat est terminé et qui a gagné
 * 
 * @param turn Le tableau de tour
 * @param EquipeGagnante Le numéro de l'équipe gagnante
 * @param EquipePerdant Le numéro de l'équipe perdante
 * @param plateau Le plateau de combat contenant les entités
 * @return int 1 si l'équipe gagnante a remporté la victoire, -1 si l'équipe perdante a perdu, 0 sinon (combat en cours)
 */
int Fin_De_combat(pos_t turn[N*N], int EquipeGagnante, int EquipePerdant, entite_t plateau[N][N]);


int combat(entite_t plateau_de_combat[N][N],SDL_Window* window,SDL_Renderer* renderer);

#endif /* PLATEAU_COMBAT_H */
