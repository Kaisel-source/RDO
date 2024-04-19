#ifndef ENTITE_H
#define ENTITE_H

#include "../common/common.h"



// Déclaration des fonctions pour le fichier entite.c
entite_t create_entity(const char *prenom, const char *classe, int pv, int pv_max, int attaque, int equipe, int mouv, int initiative, int range);
void initialiser_Entite(entite_t *entite);

#endif /* ENTITE_H */
