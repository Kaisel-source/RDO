#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <combatcommun.h>

#define N 10
#define min(a, b) (((a) < (b)) ? (a) : (b))


int estAporter(entite_t plateau[N][N], pos_t pos, pos_t enemie,int range);

pos_t detecte_mouv(entite_t mat[N][N], pos_t pos, int equipe, int mouv);

pos_t detecte_enemie(entite_t mat[N][N], pos_t pos, int equipe);


void deplacePlusProche(entite_t plateau[N][N], pos_t pos, entite_t perso);


void process_enemy_turn(entite_t plateau_de_combat[N][N], pos_t turn[], int *tour);