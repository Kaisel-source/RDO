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

void game_add_perso(game_s *g, perso *p){
    if(g->nb_pers_saved<TOTAL_PERS){
        g->p[g->nb_pers_saved]=p;
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

void game_init_game(game_s *g){
    g->nb_pers_saved=0;
    g->nb_quest_saved=0;
    g->main_perso=NULL;
    g->item=create_inventory();
}




void game_destroy_game(game_s **g){
    for(int i=0;i<TOTAL_PERS;i++){
        destroy_perso(&(*g)->p[i]);
    }
    printf("END DESTRUCTION PERSO\n");
    for(int i=0;i<TOTAL_QUEST;i++){
        destroy_quest(&(*g)->quest[i]);
    }
    printf("END DESTRUCTION QUEST\n");
    destroy_game_stockage(&(*g)->item);
    printf("END DESTRUCTION INVENTORY\n");
    printf("START DESTRUCTION MAIN PERSO\n");
    destroy_perso(&(*g)->main_perso);
    printf("END DESTRUCTION MAIN PERSO\n");
    free(*g);
    *g=NULL;
}