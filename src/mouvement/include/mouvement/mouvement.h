#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include "../common/common.h"
int collision(int (*board)[24][24],int x,int y);
int interact(map_t *map,int x,int y,int direction,personnage_t *perso);

#endif