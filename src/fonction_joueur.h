#include <combatcomun.h>

int mouvementJoueur(int dep, pos_t pos_perso, pos_t pos_cibler, entite_t plateau[N][N]);

int attaque_spell(int range,int dmg,pos_t pos_perso,pos_t pos_cibler,entite_t plateau[N][N]);

int attaque_physiqe(int range,int dmg,pos_t pos_perso,pos_t pos_cibler,entite_t plateau[N][N]);