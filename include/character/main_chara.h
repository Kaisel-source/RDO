/**
 * @file main_chara.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/

#ifndef TEMP_H
#define TEMP_H
#include "../common/board.h"
#include "../common/common.h"



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
void init_perso(perso *p, const char *name, int end, int agi, int str, int luck, int intel, int x, int y, direction_t direction, SDL_Renderer **render) ;

/**
 * @brief Initialisation of the personnage for the render
 * 
 * @param p Pointer to the personnage
 * @param x X position of the personnage
 * @param y Y position of the personnage
 * @param direction Direction of the personnage
 * @param render Pointer to the renderer
*/
void init_personnage_render(perso *p,int x,int y,direction_t direction,SDL_Renderer **render);


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



int free_personnage_render(perso **perso);


/**
 * @brief Display the equipment of the personnage
 * 
 * @param p Personnage to display the equipment
*/
void display_equipement(const perso p);


/**
 * @brief Check and level up the personnage
 * 
 * @param p Pointer to the personnage
*/
void level_up(perso *p);


/**
 * @brief Return the total strength of the personnage with his equipement
 * 
 * @param p Personnage to check
 * */
int total_strength(const perso p);

/**
 * @brief Return the total agility of the personnage with his equipement
 * 
 * @param p Personnage to check
*/
int total_agility(const perso p);

/**
 * @brief Return the total endurance of the personnage with his equipement
 * 
 * @param p Personnage to check
*/
int total_endurance(const perso p);
#endif