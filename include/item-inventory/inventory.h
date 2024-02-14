#ifndef INVENTORY_H
#define INVENTORY_H

#include "struct.h"
#include "common.h"
#include "eqpmt.h"


/**
 * @brief Create a inventory object
 * 
 * @return item_list* 
 */
item_list * create_inventory();



/**
 * @brief Return if the list is empty
 * 
 * @param list List to check
 * @return int 
 */
int empty_inventory(item_list *list);



/**
 * @brief Add an item at the beginning of the list
 * 
 * @param item Item to add
 * @param list List to add the item
 */
void add_first(item_t *item, item_list *list);



/**
 * @brief Add an item to the current position of the list
 * @warning Disable
 * @param item Item to add
 * @param list List to add the item
 */
//void add_current(item_t *item, item_list *list);



/**
 * @brief Add an item at the end of the list
 * 
 * @param item Item to add
 * @param list List to add the item
 */
void add_last(item_t *item, item_list *list);



/**
 * @brief Change the current item to the next one
 * 
 * @param list List to change the current item
 */
void suiv_current(item_list *list);



/**
 * @brief Change the current item to the previous one
 * 
 * @param list List to change the current item
 */
void prec_current(item_list *list);

/**
 * @brief Find the queue item in the list
 * 
 * @param list List to find the queue item
 * @return item_t* The queue item
 */
item_t *find_queue(item_list *list);

/**
 * @brief Display the head item in the console
 * 
 * @param list List to display the head item
 */
void display_head(const item_list *list);


/**
 * @brief Display the queue item in the console
 * 
 * @param list List to display the queue item
 *
*/
void display_queue(const item_list *list);

/**
 * @brief Display the current item in the console
 * 
 * @param list List to display the current item
 */
void display_current(const item_list *list);



/**
 * @brief Display the list of items in the console
 * 
 * @param list List to display
 */
void display_inventory(const item_list *list);



/**
 * @brief Calculate the total weight of the inventory
 * 
 * @param list List to calculate the weight
 */
void weight_calc(item_list *list);



/**
 * @brief Destroy the current item and unallocate the memory
 * 
 * @param list List to destroy the current item
 */
void destroy_current(item_list *list);



/**
 * @brief Destroy the list and unallocate the memory
 * 
 * @param list List to destroy
 */
void destroy_inventory(item_list **list);




#endif