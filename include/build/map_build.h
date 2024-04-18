#ifndef BUILD_H
#define BUILD_H

#include "../common/board.h"


int build_board(int (*board)[24][24],int value,int x,int y);
int pose_block(int (*board)[24][24],int key,int x,int y);
#endif