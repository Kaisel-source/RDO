#include "../common/common.h"
quest_t *quest_create(char *name, char *desc, int id, quest_status status, int reward_xp, int reward_gold, item_t *reward_item, int required_item_quant, item_t *required_item);
void manage_quest(perso *p);
quest_status quest_status_update(quest_t *quest, perso *p);
void quest_display(const quest_t quest);
void destroy_quest(quest_t **quest);
void quest_list_display(quest_t * const* quest);
int accept_quest(perso *p, quest_t *quest);
void quest_list_destructor(quest_t **quest);
quest_npc_t *quest_npc_create(char *accept, char *refuse, char *on_going, char *completed, quest_t *quest);
void quest_npc_display(const quest_npc_t quest_npc);
void destroy_quest_npc(quest_npc_t **quest_npc);