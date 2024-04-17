#ifndef ENEMIE_H
#define ENEMIE_H

#include "../common/common.h"  // Inclure le fichier d'en-tête des entités




// Déclaration des fonctions pour le fichier enemie.c
int estAporter(pos_t pos, pos_t enemie, int range);
pos_t detecte_mouv(entite_t mat[N][N], pos_t pos, int equipe, int mouv);
pos_t detecte_enemie(entite_t mat[N][N], pos_t pos, int equipe);
void deplacePlusProche(entite_t plateau[N][N], pos_t pos, entite_t perso);
void process_enemy_turn(entite_t plateau_de_combat[N][N], pos_t turn[], int *tour);

#endif /* ENEMIE_H */
