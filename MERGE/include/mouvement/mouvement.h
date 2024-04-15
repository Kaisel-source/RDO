#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include "../common/board.h"
int collision(int (*board)[24][24],int x,int y);
int interact(game_s *game,int x,int y);

#endif