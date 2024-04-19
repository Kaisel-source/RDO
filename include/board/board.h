/**
 * @file board.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-04-14
*/


#ifndef BOARD_H
#define BOARD_H


#include "../common/board.h"




#define NB_AREA 16
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
#define FENCE -10
#define FIRECAMP -11
#define YURT -12
#define WOOD -13
#define STONE2 -14
#define GOLDCRYSTAL -15

#define SORTIE -9999
#define MONSTER -10000


/**
 * @brief : Import a board from a file
 * @param board : the board who receive the data
 * @param path : the path of the file
*/
int import_board(int (*board)[24][24],char *path);

/**
 * @brief : Export a board to a file
 * @param board : the board who contain the data
 * @param path : the path of the file
*/
int export_board(int (*board)[24][24],char *path);

#endif
