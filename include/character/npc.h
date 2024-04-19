/**
 * @file npc.h
 * @author Aymeric MABIRE
 * @brief 
 * @version 0.1
 * @date 2024-03-10
*/

#ifndef NPC_H
#define NPC_H
#include "../common/common.h"

/**
 * @brief Create an NPC
 * 
 * @param name : Name of the NPC
 * @param dialog : Dialog of the NPC
 * @param money : Money of the NPC
 * @param path : Path of the NPC of the render
 * @param direction : Direction of the NPC
 * @param render : Pointer to the renderer
 * @param nb_quest : Number of quest
 * @param ... : List of quest
*/
npc_s * npc_creator(char* name, char* dialog, int money,char* path,direction_t direction, SDL_Renderer **render, int nb_quest,...);

/**
 * @brief Destroy the NPC
 * 
 * @param npc : NPC to destroy
*/
void destroy_npc(npc_s ** npc);

/**
 * @brief Display the NPC in the console
 * 
 * @param npc : NPC to display
*/
void display_npc(const npc_s npc);

/**
 * @brief Interaction of the NPC about the quest
 * 
 * @param p : Personnage who interact with the NPC
 * @param npc : NPC who interact with the personnage
*/
void npc_quest_interaction(perso *p, npc_s *npc);

/**
 * @brief Interaction of the NPC
 * 
 * @param p : Personnage who interact with the NPC
 * @param npc : NPC who interact with the personnage
*/
void npc_interact(perso *p, npc_s *npc);

#endif
