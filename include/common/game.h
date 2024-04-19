/**
 * @file game.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/
#ifndef GAME_H
#define GAME_H
#include "struct.h"
#include "common.h"

/**
 * @brief Create a game object
 * 
 * @param g Game to create
 * @param m Map of the game
 * @param textureOut Texture of the out of the map
 * @param textureMonster Texture of the monster
 * @param area Area of the game
 */
void game_init_game(game_s *g,map_t *m,SDL_Texture *textureOut,SDL_Texture *textureMonster,SDL_Texture **area);

/**
 * @brief Add a NPC in the game
 * 
 * @param g Game to add the NPC
 * @param p NPC to add
 */
void game_add_npc(game_s *g, npc_s *p);

/**
 * @brief Add the main personnage in the game
 * 
 * @param g Game to add the main personnage
 * @param p Main personnage to add
 */
void game_add_main_perso(game_s *g, perso *p);

/**
 * @brief Add a quest in the game
 * 
 * @param g Game to add the quest
 * @param q Quest to add
 */
void game_add_quest(game_s *g, quest_t *q);

/**
 * @brief Display the game in the console
 * 
 * @param g Game to display
 */
void game_display_game(const game_s g);

/**
 * @brief Add an item in the game
 * 
 * @param g Game to add the item
 * @param it Item to add
 */
void game_add_item(game_s *g, item_t *it);

/**
 * @brief Destroy the game
 * 
 * @param g Game to destroy
 */
void game_destroy_game(game_s **g);

/**
 * @brief Add an item to the game structure game
 * 
 * @param g Game to display
 * @param render Renderer of the window
 */
void game_item(item_t *item, item_list *list);

#endif