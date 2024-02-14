#ifndef TEMP_H
#define TEMP_H
#include "common.h"
#include "struct.h"

typedef struct stat_p{
    int intel;
    int str;
    int luck;
    int agi;
    int end;

    //int available;
}stat_s;



typedef struct pers{
    char *name;

    stat_s *stat;

    int hp;
    int hp_max;

    int mp;
    int mp_max;

    int xp;
    int xp_max;

    int level;

    unsigned int weight_max;
    int money;

    item_list *inventory;
} perso;



/**
 * *@brief Initialisation of the personnage and attribution of the stat
 * 
 * @param p Pointer to the personnage
 * @param name Name of the personnage
 * @param end Stat endurance of the personnage 
 * @param agi Stat agility of the personnage
 * @param str Stat strength of the personnage
 * @param luck Stat luck of the personnage
 * @param intel Stat intelligence of the personnage
 */
void init_perso(perso *p, char *name,int end, int agi, int str, int luck,int intel);


/**
 * @brief Display the personnage information in the console
 * 
 * @param p Personnage to display
 */
void display_perso(const perso p);

/**
 * @brief Add the item in the inventory
 * 
 * @param p Pointer to the personnage
 * @param item Item to add
 */
void take_item(perso *p,item_t *item);



/**
 * @brief Check the item and return if it's in the inventory
 * 
 * @param p Pointer to the personnage
 * @param item Item to check
 * @return int quantity if presente, or 0 is absent or -1 in case of ERROR
 */
int in_inventory(perso *p, int id,type_it type);



/**
 * @brief Unnallocate the memory of the personnage and destroy it
 * 
 * @param p Pointer to the personnage
 */
void destroy_perso(perso **p);

#endif