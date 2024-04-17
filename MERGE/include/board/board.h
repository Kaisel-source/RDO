#ifndef BOARD_H
#define BOARD_H


#include "../common/board.h"




#define NB_AREA 10
#define GRASS 0
#define STONE -1
#define BUSH -2
#define CRYSTALL -3
#define CACTUS -4
#define WATER -5
#define DOOR_O -6
#define DOOR_C -7
#define TREE -8
#define TILES -9

#define SORTIE -9999
#define MONSTER -10000



int import_board(int (*board)[24][24],char *path);
int export_board(int (*board)[24][24],char *path);

#endif
