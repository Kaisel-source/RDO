#include "struct.h"
#include "temp.h"

/**
 * @brief : Create a consumable object
 * 
 * @param name : Name of the consumable
 * @param id : Corresponds to the id of the consumable
 * @param poids : Weight of the consumable for the inventory capacity
 * @param price : Price of the consumable for selling with pnj
 * @param hp : Health points given by the consumable
 * @param mp : Mana points given by the consumable
 * @param xp : Experience points given by the consumable
 * @param available : Point avaible for using given by the consumable
 * @param desc : Description of the consumable
 * @return item_t* 
 */
item_t* conso_create(char* name,int id, int poids, int price, int hp, int mp, int xp,int available,char *desc);

/**
 * @brief : Free the memory of the consumable
 * 
 * @param item : Consumable to free
 */
void conso_destructor(inv_item_s** item);

/**
 * @brief : Display the consumable
 * 
 * @param conso : Consumable to display
 */
void display_conso(const conso_s conso);

/**
 * @brief : Use the consumable
 * 
 * @param p : Personnage who use the consumable
 * @param conso : Consumable to use
 */
void use_conso(perso* p,conso_s* conso);