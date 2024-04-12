#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"
#include <math.h>
#include <SDL2/SDL_ttf.h>
#include <Bouton.h>
#include <enemie.h>
#include <text_ecrire.h>
#include <turn_order.h>

#define N 10
#define min(a, b) (((a) < (b)) ? (a) : (b))

const float porcen= 0.70;
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 790;
const int GRID_ROWS = 10;
const int GRID_COLUMNS = 10;
const int BUTTON_SIZEx = SCREEN_WIDTH/GRID_COLUMNS;
const int BUTTON_SIZEy = SCREEN_HEIGHT*porcen/GRID_ROWS;
const int BUTTON_MARGIN = 0;

/**
 * @brief position 
 * 
 */
typedef struct{
    int x;
    int y;
}pos_t;

/**
 * @brief ensemble des caracteristique des ennemies,allies
 * et des personnages jouable.
 * 
 */
typedef struct{
    char  prenom[30];
    char  classe[30];
    int pv;
    int pv_max;
    int attaque;
    int alive;
    SDL_Texture * img;
    int equipe;
    int mouv;
    int initiative;
    int range;
}entite_t;


