/**
 * @file board.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-04-14
*/

#ifndef BOARD_C_H
#define BOARD_C_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "struct.h"




#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 800
#define SPRITE_WIDTH 200 // Nouvelle largeur de l'image
#define SPRITE_HEIGHT 150 // Nouvelle hauteur de l'image

#define BOARD_SIZE_X 24
#define BOARD_SIZE_Y 24



// Calcul de la taille des cases du plateau en fonction de la taille de la fenêtre
#define CELL_WIDTH (WINDOW_WIDTH / BOARD_SIZE_X)
#define CELL_HEIGHT (WINDOW_HEIGHT / BOARD_SIZE_Y)

#define FRAME_DROITE 8
#define FRAME_GAUCHE 9
#define FRAME_HAUT 10
#define FRAME_BAS 11
#define TAILLE_SPRITE 65



#include "../mouvement/mouvement.h"
#include "../rending/rending.h"
#include "../board/board.h"
#include "../freeing/freeing.h"
#include "../build/map_build.h"
#include "common.h"


#endif