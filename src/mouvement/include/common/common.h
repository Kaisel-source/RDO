#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <unistd.h>

#define NB_MAP_X 2
#define NB_MAP_Y 1


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

typedef struct img_s{
    int nb_sprite;
    int num_ref;
    SDL_Rect **texture;
}img_t;

typedef struct{
    int x;
    int y;
    int map[NB_MAP_Y][NB_MAP_X][24][24];
    char* path[NB_MAP_Y][NB_MAP_X];
}map_t;

typedef enum{
    WALK_R,
    WALK_L,
    WALK_U,
    WALK_D,
    INTERACT,
    HIDE,
    IDLE
}state_t;

typedef enum{
    DOWN,
    RIGHT,
    LEFT,
    UP
    
}direction_t;

typedef struct {
    int x;
    int y;
    direction_t direction;
    state_t state;
    SDL_Texture *Texture;
    img_t **sprite_move;
    SDL_Rect *position;
}personnage_t;

#include "../mouvement/mouvement.h"
#include "../rending/rending.h"
#include "../board/board.h"
#include "../freeing/freeing.h"
#include "../build/map_build.h"

#endif
