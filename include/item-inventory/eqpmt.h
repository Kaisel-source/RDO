#ifndef EQPMT_H
#define EQPMT_H

#include "struct.h"


/**
 * @brief : Create an item and convert it to an inventory item
 * 
 * @param id : Corresponds to the id of the item
 * @param name : Name of the item
 * @param type : Type of equipement
 * @param dmg_type : Damage type of the item
 * @param dgt : Damage of the item
 * @param def : Defence of the item
 * @param end : Endurance modifier of the item
 * @param agi : Agility modifier of the item
 * @param str : Strength modifier of the item
 * @param luck : Luck modifier of the item
 * @param intel : Intelligence modifier of the item
 * @param price : Price of the item for selling with pnj
 * @param poids : Weight of the item for the inventory capacity
 * @param desc : Description of the item
 * @return ** item_t* : Return the item converted to an inventory item
 */
item_t* eqpmt_creator(int id, char* name, eqpmt_type type, dmg_t dmg_type, int damage, int defence, int str, int agi, int end, int luck, int intel, int price, int poids, char* desc);



/**
 * @brief display the item information in the console
 * @warning This function is only working for the item_eqpmt type
 * @param item Eqpmt to display
 * @return ** void 
 */
void display_eqpmt(const item_eqpmt eqpmt);



/**
 * @brief : Give the string corresponding to the type of equipement for the enum "eqpmt_type"
 * 
 * @param type : Type of equipement  
 * @return ** char* : string corresponding to the type of equipement
 */
char* name_eqpmt(int type);



/**
 * @brief Unallocate the memory of the equipement and destroy it
 * @warning This function is only working for the item_eqpmt type
 * @param item Eqpmt to destroy
 */
void eqpmt_destructor(inv_item_s** item);



#endif