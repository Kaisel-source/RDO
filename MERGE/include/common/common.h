#ifndef COMMON_H
#define COMMON_H

#define ERROR -1
#define TRUE 1
#define FALSE 0
#define N 10
#define min(a, b) (((a) < (b)) ? (a) : (b))

#define porcen 0.70
#define GRID_ROWS  10
#define GRID_COLUMNS  10
#define BUTTON_SIZEx  WINDOW_WIDTH/GRID_COLUMNS
#define BUTTON_SIZEy  WINDOW_HEIGHT*porcen/GRID_ROWS
#define BUTTON_MARGIN  0

#include <string.h>
#include "struct.h"
#include "board.h"
#include "../item-inventory/ressource.h"
#include "../item-inventory/inventory.h"
#include "../item-inventory/consommable.h"
#include "../item-inventory/eqpmt.h"
#include "../character/main_chara.h"
#include "../character/npc.h"
#include "../quest/quest.h"
#include "../combat/Bouton.h"
#include "../combat/entite.h"
#include "../combat/enemie.h"
#include "../combat/fonction_joueur.h"
#include "../combat/text_ecrire.h"
#include "../combat/plateauCombat.h"
#include "../combat/turn_order.h"
#include "../combat/inventaire_affiche.h"


#include "game.h"


/**
 * @brief Display the item by calling the display function associated with the type of the item
 * 
 * @param item Item to display
 */
void display_common(const inv_item_s item);



/**
 * @brief Destroy the item by calling the destructor associated with the type of the item
 * 
 * @param item List of the item to destroy
 */
void destroy_common_item_stock(item_list *inv);

/**
 * @brief 
 * 
 * @param item 
 * @param player 
 */
void use_common(perso *player);


int export(const perso *p);
int import(perso *p);

void add_n(perso *p,item_t it, int nb);
void remove_n(perso *p,item_t it, int nb);


#endif