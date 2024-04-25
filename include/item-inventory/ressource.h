/**
 * @file ressource.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/

#ifndef RESSOURCE_H
#define RESSOURCE_H

#include "../common/common.h"

/**
 * @brief Create a ressource object an convert it to an inventory item
 * 
 * @param id : Corresponds to the id of the ressource
 * @param name : Name of the ressource
 * @param price : Price of the ressource for selling with pnj
 * @param poids : Weight of the ressource for the inventory capacity
 * @param desc  :  Description of the ressource
 * @return item_t*
 */
item_t* ress_creator(int id, char* name, int price, int poids, char* desc,int quantity);



/**
 * @brief display the ressource information in the console
 * @warning This function is only working for the item_ress type
 * @param ress Ressource to display
 * @return ** void 
 */
void display_ress(const item_ress ress);



/**
 * @brief Unnallocate the memory of the ressource and destroy it
 * @warning This function is only working for the item_ress type____
 * @param item Ressource to destroy
 */
void ress_destructor(inv_item_s** item);

#endif