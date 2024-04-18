#include "../common/common.h"
npc_s * npc_creator(char* name, char* dialog, int money,char* path,direction_t direction, SDL_Renderer **render, int nb_quest,...);
void destroy_npc(npc_s ** npc);
void display_npc(const npc_s npc);
void npc_quest_interaction(perso *p, npc_s *npc);
void npc_interact(perso *p, npc_s *npc);