#ifndef COMMON_H
#define COMMON_H

#include "struct.h"
#include "eqpmt.h"
#include "ressource.h"
#include "inventory.h"
#include "temp.h"

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
 * @param item Item to destroy
 */
void destroy_common(item_t **item, int *nb_item);

/**
 * @brief 
 * 
 * @param item 
 * @param player 
 */
void use_common(item_t *item, perso *player);

#endif