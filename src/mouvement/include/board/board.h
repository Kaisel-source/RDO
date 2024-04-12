#ifndef BOARD_H
#define BOARD_H


#include "../common/common.h"




#define NB_AREA 8
#define FRAME_WALK 0
#define STONE -1
#define TREE -2
#define CRYSTALL -3
#define CACTUS -4
#define WATER -5
#define DOOR_O -6
#define DOOR_C -7

#define SORTIE -9999



int import_board(int (*board)[24][24],char *path);
int export_board(int (*board)[24][24],char *path);

#endif
