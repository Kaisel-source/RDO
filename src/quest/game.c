 #include "../../include/common/game.h"

void game_add_quest(game_s *g, quest_t *q){
    if(g->nb_quest_saved<TOTAL_QUEST){
        g->quest[g->nb_quest_saved]=q;
        g->nb_quest_saved++;
    }
    else{
        printf("Impossible d'ajouter une quete, nombre de quete max atteint\n");
    }
}

void game_add_npc(game_s *g, npc_s *p){
    if(g->nb_pers_saved<TOTAL_PERS){
        g->npc[g->nb_pers_saved]=p;
        g->nb_pers_saved++;
    }
    else{
        printf("Impossible d'ajouter un perso, nombre de perso max atteint\n");
    }
}

void game_add_main_perso(game_s *g, perso *p){
    g->main_perso=p;
}

void game_item(item_t *item, item_list *list)
{  
    printf("Ajout d'un item\n");
    empty_inventory(list);
    if (empty_inventory(list))
    {
        printf("Ajout en tete\n");
        add_first(item, list);
    }
    else
    {
        printf("Ajout en queue\n");
        add_last(item, list);
    }
    list->nb_item++;
    printf("Poids avant : %d\n", list->weight);
}

void game_add_item(game_s *g, item_t *i){
    printf("Ajout de l'item\n");
    game_item(i,g->item);
}

void game_init_game(game_s *g,map_t *m,SDL_Texture *textureOut,SDL_Texture *textureMonster,SDL_Texture **area){
    g->nb_pers_saved=0;
    g->nb_quest_saved=0;
    g->main_perso=NULL;
    g->map=m;
    g->area=area;
    g->TextureOut=textureOut;
    g->TextureMonster=textureMonster;
    g->item=create_inventory();
}




void game_destroy_game(game_s **g) {
    if (g == NULL || *g == NULL) {
        return;
    }

    // Libération de la mémoire pour chaque PNJ sauvegardé
    printf("NPC\n");
    for (int i = 0; i < (*g)->nb_pers_saved; i++) {
        printf("NPC %d\n", i);
        destroy_npc(&((*g)->npc[i]));
    }

    printf("Quest\n");

    // Libération de la mémoire pour chaque quête sauvegardée
    for (int i = 0; i < (*g)->nb_quest_saved; i++) {
        if((*g)->quest[i] != NULL)
            destroy_quest(&((*g)->quest[i]));
    }

    printf("Item\n");
    // Libération de la mémoire pour l'inventaire du jeu
    destroy_game_stockage(&((*g)->item));

    printf("Perso\n");
    // Libération de la mémoire pour le personnage principal
    destroy_perso(&((*g)->main_perso));

    printf("Area\n");
    // Libération de la mémoire pour la zone de jeu
    free((*g)->area);

    printf("Texture\n");
    // Destruction de la texture SDL
    SDL_DestroyTexture((*g)->TextureOut);
    SDL_DestroyTexture((*g)->TextureMonster);

    printf("Map\n");
    // Export et libération de la mémoire de la carte
    if ((*g)->map != NULL) {
        int num_map_x = (*g)->map->x;
        int num_map_y = (*g)->map->y;
        if ((*g)->map->map != NULL) {
            export_board(&((*g)->map->map[num_map_y][num_map_x]), (*g)->map->path[num_map_y][num_map_x]);
        }    


        free_map(&((*g)->map));
    }
    // Libération de la mémoire pour la structure de jeu elle-même
    free(*g);
    *g = NULL;
}
