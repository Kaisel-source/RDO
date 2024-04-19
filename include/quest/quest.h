/**
 * @file quest.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/

#ifndef QUEST_H
#define QUEST_H

#include "../common/common.h"

/**
 * @brief Create the quest
 * 
 * @param name Name of the quest
 * @param desc Description of the quest
 * @param id Id of the quest
 * @param status Status of the quest
 * @param reward_xp Xp reward of the quest
 * @param reward_gold Gold reward of the quest
 * @param reward_item Item reward of the quest
 * @param required_item_quant Quantity of the required item for complete te quest
 * @param required_item Required item for complete te quest
 * @return quest_t* 
*/
quest_t *quest_create(char *name, char *desc, int id, quest_status status, int reward_xp, int reward_gold, item_t *reward_item, int required_item_quant, item_t *required_item);

/**
 * @brief Manage the quest of the personnage
 * 
 * @param p Personnage to manage the quest
*/
void manage_quest(perso *p);

/**
 * @brief Update the status of the quest
 * 
 * @param quest Quest to update
 * @param p Personnage to update the quest
 * @return quest_status updated status
*/
quest_status quest_status_update(quest_t *quest, perso *p);

/**
 * @brief Display the quest in the console
 * 
 * @param quest Quest to display
*/
void quest_display(const quest_t quest);

/**
 * @brief Destroy the quest
 * 
 * @param quest Quest to destroy
*/
void destroy_quest(quest_t **quest);

/**
 * @brief Display the list of the quest in the console
 * 
 * @param quest List of the quest to display
*/
void quest_list_display(quest_t * const* quest);

/**
 * @brief Accept the quest
 * 
 * @param p Personnage who accept the quest
 * @param quest Quest to accept
 * @return int 
*/
int accept_quest(perso *p, quest_t *quest);

/**
 * @brief Destroy the list of the quest
 * 
 * @param quest List of the quest to destroy
*/
void quest_list_destructor(quest_t **quest);

/**
 * @brief Create the quest npc
 * 
 * @param accept Accept message
 * @param refuse Refuse message
 * @param on_going On going message
 * @param completed Completed message
 * @param quest Quest of the npc
 * @return quest_npc_t* 
*/
quest_npc_t *quest_npc_create(char *accept, char *refuse, char *on_going, char *completed, quest_t *quest);

/**
 * @brief Display the quest npc in the console
 * 
 * @param quest_npc Quest npc to display
*/
void quest_npc_display(const quest_npc_t quest_npc);

/**
 * @brief Destroy the quest npc
 * 
 * @param quest_npc Quest npc to destroy
*/
void destroy_quest_npc(quest_npc_t **quest_npc);

#endif