/**
 * @file map_build.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-04-14
*/

#ifndef BUILD_H
#define BUILD_H

#include "../common/board.h"

/**
 * @brief Build a change the value of a block in the board
 * @param board : the board who receive the data
 * @param value : the value of the block for the change
 * @param x : the x position of the block to change
 * @param y : the y position of the block to change
*/
int build_board(int (*board)[24][24],int value,int x,int y);

/**
 * @brief Build a block in the board
 * @param board : the board who receive the data
 * @param key : the key of the input keyboard for the block to build
 * @param x : the x position of the block to build
 * @param y : the y position of the block to build
*/
int pose_block(int (*board)[24][24],int key,int x,int y);
#endif