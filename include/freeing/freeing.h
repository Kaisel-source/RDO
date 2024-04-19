/**
 * @file main_chara.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-04-14
*/

#ifndef FREE_H
#define FREE_H
#include "../common/board.h"


/**
 * @brief Free the area texture
 * 
 * @param area Area to free
*/
int free_area(SDL_Texture ***area);

/**
 * @brief Free the map
 * 
 * @param map Map to free
*/
int free_map(map_t **map);
#endif