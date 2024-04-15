#include "entite.h"



entite_t create_entity(const char *prenom, const char *classe, int pv, int pv_max, int attaque, int equipe, int mouv, int initiative, int range) {
    entite_t perso;
    strcpy(perso.prenom, prenom);
    strcpy(perso.classe, classe);
    perso.pv = pv;
    perso.pv_max = pv_max;
    perso.attaque = attaque;
    perso.alive = 1; // L'entité est initialement vivante
    perso.img = NULL; 
    perso.equipe = equipe;
    perso.mouv = mouv;
    perso.initiative = initiative;
    perso.range = range;
    return perso;
}

void initialiserEntite(entite_t *entite) {
    entite->prenom[0] = '\0';
    entite->classe[0] = '\0';
    entite->pv = 0;
    entite->pv_max = 0;
    entite->attaque = 0;
    entite->alive = 0;
    entite->img = NULL;
    entite->equipe = 0;
    entite->mouv = 0;
    entite->initiative = 0;
    entite->range = 0;
}