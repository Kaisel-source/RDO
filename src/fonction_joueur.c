#include "fonction_joueur.h"


int mouvementJoueur(int dep, pos_t pos_perso, pos_t pos_cibler, entite_t plateau[N][N]) {
    // Vérifier si la case est à portée de déplacement
    int distance = abs(pos_perso.x - pos_cibler.x) + abs(pos_perso.y - pos_cibler.y);
    printf("%d\n", distance);
    if (distance <= dep && plateau[pos_cibler.x][pos_cibler.y].pv <= 0) {
        // Déplacement possible, effectue le déplacement
        plateau[pos_cibler.x][pos_cibler.y] = plateau[pos_perso.x][pos_perso.y];
        initialiserEntite(&plateau[pos_perso.x][pos_perso.y]);
        return 1;
    } else {
        printf("Cible hors de portée pour le déplacement ou case occupée!\n");
        return 0;
    }
}

/**
 * @brief infige des dommage  avec un spell sur une case cibler et verifie si possible
 * @param pos_cibler
 * @param range 
 * @param dmg 
 * @param pos_perso
 * @param plateau
 */
int attaque_spell(int range,int dmg,pos_t pos_perso,pos_t pos_cibler,entite_t plateau[N][N]){
    // Vérifier si la cible est à portée
    int distance = abs(pos_perso.x - pos_cibler.x) + abs(pos_perso.y - pos_cibler.y);
    if ((distance <= range) && (plateau[pos_cibler.x][pos_cibler.y].pv>0)) {
        // Appliquer les dégâts à la cible
        printf("Sort lancé avec succès ! Dégâts infligés magique: %d\n", dmg);
        plateau[pos_cibler.x][pos_cibler.y].pv-=dmg;
        return 1;
    } else {
        printf("Cible hors de portée pour le sort ou cible incorecte (vise mieux) !\n");
        return 0;
    }
}


/**
 * @brief infige des dommage avec une attaque sur une case cibler et verifie si possible
 * @param pos_cibler
 * @param range 
 * @param dmg 
 * @param pos_perso
 * @param plateau
 */
int attaque_physiqe(int range,int dmg,pos_t pos_perso,pos_t pos_cibler,entite_t plateau[N][N]){
        // Vérifier si la cible est à portée
    int distance = abs(pos_perso.x - pos_cibler.x) + abs(pos_perso.y - pos_cibler.y);
    if ((distance <= range) && (plateau[pos_cibler.x][pos_cibler.y].pv>0)) {
        // Appliquer les dégâts à la cible
        printf("Attaque physique réussie ! Dégâts infligés  physique: %d\n", dmg);
        plateau[pos_cibler.x][pos_cibler.y].pv-=dmg;
        return 1;
    } else {
        printf("Cible hors de portée ou cible incorecte (vise mieux)!\n");
        return 0;
    }
}

