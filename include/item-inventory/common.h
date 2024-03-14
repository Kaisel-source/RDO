#ifndef COMMON_H
#define COMMON_H
#include <string.h>

#include "struct.h"

#include "ressource.h"
#include "inventory.h"
#include "temp.h"
#include "consommable.h"
#include "eqpmt.h"

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
void destroy_common(perso *p);

/**
 * @brief 
 * 
 * @param item 
 * @param player 
 */
void use_common(perso *player);


int export(const perso *p);
int import(perso *p);
#endif