#include "struct.h"
#include "common.h"

void game_init_game(game_s *g,map_t *m,SDL_Texture *textureOut,SDL_Texture **area);
void game_add_npc(game_s *g, npc_s *p);
void game_add_main_perso(game_s *g, perso *p);
void game_add_quest(game_s *g, quest_t *q);
void game_display_game(const game_s g);
void game_add_item(game_s *g, item_t *it);
void game_destroy_game(game_s **g);
void game_item(item_t *item, item_list *list);