#include "../../include/common/common.h"





/**
 * @brief Retourne si un ennemi est à portée d'un autre ennemi
 * 
 * @param plateau Le plateau de jeu contenant les entités
 * @param pos La position de l'entité depuis laquelle la portée est vérifiée
 * @param enemie La position de l'ennemi à vérifier
 * @return int 1 si un ennemi est à portée, 0 sinon
 */
int estAporter( pos_t pos, pos_t enemie,int range) {
    
    // Calculer la distance entre les deux positions
    int distance = abs(pos.x - enemie.x) + abs(pos.y - enemie.y);

    if (distance <= range) {
        return 1;
    } else {
        return 0;
    }
}



/**
 * @brief retourne la position la plus proche en fonction de se nombre de point de mouvement vers l enemie le plus proche
 * 
 * @param mat 
 * @param pos 
 * @param equipe 
 * @param mouv 
 * @return pos_t 
 */
pos_t detecte_mouv(entite_t mat[N][N], pos_t pos, int equipe, int mouv) {
    int i, j;
    int plus_procheX = -1, plus_procheY = -1;
    double distance_min = INFINITY;
    pos_t nouvelle_pos = pos; // Créer une nouvelle variable pour stocker la nouvelle position
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) { // Parcours la matrice 
            if (mat[i][j].equipe != equipe && mat[i][j].equipe != 0) { // Si il trouve un ennemi
                double distance = sqrt(pow(i - pos.y, 2) + pow(j - pos.x, 2));
                if (distance < distance_min) {
                    distance_min = distance;
                    plus_procheX = j;
                    plus_procheY = i;
                }
            }
        }
    }
    // Détermination de la nouvelle position sans modifier la position actuelle
    if (plus_procheX != -1 && plus_procheY != -1) {
        // Calcul du déplacement
        int deltaX = plus_procheX - pos.x;
        int deltaY = plus_procheY - pos.y;
        if (abs(deltaX) > abs(deltaY)) {
            nouvelle_pos.x += (deltaX > 0) ? min(mouv, abs(deltaX)) : -min(mouv, abs(deltaX));
        } else {
            nouvelle_pos.y += (deltaY > 0) ? min(mouv, abs(deltaY)) : -min(mouv, abs(deltaY));
        }
    }
    // Renvoie de la nouvelle position
    return nouvelle_pos;
}




/**
 * @brief idem que detecte mouv a l exeption ne renvoie juste la pose de l enemie
 * 
 * @param mat 
 * @param pos 
 * @param equipe 
 * @return pos_t 
 */
pos_t detecte_enemie(entite_t mat[N][N], pos_t pos, int equipe) {
    int i, j;
    int plus_procheX = -1, plus_procheY = -1;
    double distance_min = INFINITY;
    pos_t nouvelle_pos; // Variable pour stocker la nouvelle position

    // Parcours la matrice
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            // Vérifie si l'entité dans la case est un ennemi et que ce n'est pas une case vide
            if (mat[i][j].equipe != equipe && mat[i][j].equipe != 0) {
                // Calcule la distance entre la position actuelle et l'ennemi
                double distance = sqrt(pow(i - pos.y, 2) + pow(j - pos.x, 2));
                // Met à jour la position de l'ennemi le plus proche si la distance est plus petite
                if (distance < distance_min) {
                    distance_min = distance;
                    plus_procheX = i;
                    plus_procheY = j;
                }
            }
        }
    }

    // Assigne les coordonnées de la nouvelle position trouvée
    nouvelle_pos.x = plus_procheX;
    nouvelle_pos.y = plus_procheY;

    // Retourne la nouvelle position
    return nouvelle_pos;
}




/**
 * @brief deplace une entite en fonction de entite.mouv
 * 
 * @param plateau 
 * @param pos 
 * @param perso 
 */
void deplacePlusProche(entite_t plateau[N][N], pos_t pos, entite_t perso) {
    // Trouver la nouvelle position de l'ennemi le plus proche sans modifier la position actuelle
    pos_t nouvelle_pos = detecte_mouv(plateau, pos, perso.equipe, perso.mouv);
    // Déplacer l'entité vers la nouvelle position de l'ennemi le plus proche
    plateau[pos.x][pos.y].pv=0;
    plateau[pos.x][pos.y].pv_max=0;
    plateau[pos.x][pos.y].equipe=0;
    plateau[pos.x][pos.y].attaque=0;
    plateau[pos.x][pos.y].initiative=0;
    plateau[pos.x][pos.y].range=0;
    plateau[nouvelle_pos.x][nouvelle_pos.y] = perso;
}

void process_enemy_turn(entite_t plateau_de_combat[N][N], pos_t turn[], int *tour) {
    if (plateau_de_combat[turn[*tour].x][turn[*tour].y].equipe == 1) {
        pos_t enemiepos = detecte_enemie(plateau_de_combat, turn[*tour], 1);
        if (estAporter( turn[*tour], enemiepos, plateau_de_combat[turn[*tour].x][turn[*tour].y].range) == 1) {
            plateau_de_combat[enemiepos.x][enemiepos.y].pv -= plateau_de_combat[turn[*tour].x][turn[*tour].y].attaque;
        } else {
            deplacePlusProche(plateau_de_combat, turn[*tour], plateau_de_combat[turn[*tour].x][turn[*tour].y]);
        }
        (*tour)++;
    }
}
