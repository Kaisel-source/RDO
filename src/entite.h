#ifndef ENTITE_H
#define ENTITE_H

#include "commun.h" 



// Déclaration des fonctions pour le fichier entite.c
entite_t create_entity(const char *prenom, const char *classe, int pv, int pv_max, int attaque, int equipe, int mouv, int initiative, int range);
void initialiserEntite(entite_t *entite);

#endif /* ENTITE_H */
