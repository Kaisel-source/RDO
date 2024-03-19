#ifndef COMMON_H
#define COMMON_H
#include <string.h>

#include "struct.h"

#include "../item-inventory/ressource.h"
#include "../item-inventory/inventory.h"
#include "../item-inventory/temp.h"
#include "../item-inventory/consommable.h"
#include "../item-inventory/eqpmt.h"
#include "../quest/quest.h"
#include "game.h"

#define ERROR -1
#define TRUE 1
#define FALSE 0


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