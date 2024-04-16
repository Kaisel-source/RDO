#ifndef COMMUN_H
#define COMMUN_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define N 10
#define min(a, b) (((a) < (b)) ? (a) : (b))


#define porcen 0.70
#define SCREEN_WIDTH  1080
#define SCREEN_HEIGHT  790
#define GRID_ROWS  10
#define GRID_COLUMNS  10
#define BUTTON_SIZEx  SCREEN_WIDTH/GRID_COLUMNS
#define BUTTON_SIZEy  SCREEN_HEIGHT*porcen/GRID_ROWS
#define BUTTON_MARGIN  0

/**
 * @brief Structure pour représenter une position sur le plateau
 */
typedef struct {
    int x; /**< Coordonnée en X */
    int y; /**< Coordonnée en Y */
} pos_t;

// Structure représentant une entité
typedef struct {
    char prenom[50];
    char classe[50];
    int pv;
    int pv_max;
    int attaque;
    int alive;
    void *img; // Pointeur vers l'image de l'entité, à définir selon votre utilisation
    int equipe;
    int mouv;
    int initiative;
    int range;
} entite_t;

// Structure représentant un bouton
typedef struct {
    SDL_Rect rect;       // Rectangle définissant la position et la taille du bouton
    SDL_Texture* texture; // Texture du bouton (à générer avec SDL_CreateTextureFromSurface())
} Button;

typedef struct {
    char *name;
    char *description;
} Item;




#include "Bouton.h"
#include "entite.h"
#include "enemie.h"
#include "fonction_joueur.h"
#include "text_ecrire.h"
#include "plateauCombat.h"
#include "turn_order.h"
#include "inventaire_affiche.h"






#endif /* COMBAT_H */
