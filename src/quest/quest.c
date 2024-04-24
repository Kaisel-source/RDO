 #include "../../include/common/common.h"


quest_t *quest_create(char *name, char *desc, int id, quest_status status, int reward_xp, int reward_gold, item_t *reward_item, int required_item_quant, item_t *required_item){
    quest_t *quest = malloc(sizeof(quest_t));
    quest->name = malloc(strlen(name) + 1);
    strcpy(quest->name, name);
    quest->desc = malloc(strlen(desc) + 1);
    strcpy(quest->desc, desc);
    quest->id = id;
    quest->status = status;
    quest->reward_xp = reward_xp;
    quest->reward_gold = reward_gold;
    quest->reward_item = reward_item;
    quest->required_item_quant = required_item_quant;
    quest->required_item = required_item;
    return quest;
}

void manage_quest(perso *p){
    for(int i=0;i<p->nb_quest;i++){
        if(p->quest[i]->status == COMPLETED){
            p->quest[i]=NULL;
            p->nb_quest--;
        }
    }
    //compactage
    
}

quest_status quest_status_update(quest_t *quest, perso *p){
    int id=quest->required_item->item_inv->type==EQPMT?quest->required_item->item_inv->item_u->eqpmt->id:quest->required_item->item_inv->item_u->ress->id;
    printf("Statut update: %d / %d\n",quest->required_item_quant, in_inventory(p, id,quest->required_item->item_inv->type));
    if(quest->status == ON_GOING && quest->required_item_quant <= in_inventory(p, id,quest->required_item->item_inv->type)){
        quest->status = COMPLETED;
        take_item(p, quest->reward_item);
        p->xp += quest->reward_xp;
        p->money += quest->reward_gold;

        remove_n(p, *quest->required_item, quest->required_item_quant);
        

        manage_quest(p);
        printf("Quete completee\n");

    }
    else if(quest->status == NOT_STARTED){
        quest->status = ON_GOING;
        printf("Quete en cours\n");
        printf("Avancement : %d / %d\n", in_inventory(p, id,quest->required_item->item_inv->type), quest->required_item_quant);
    }

    else if(quest->status == COMPLETED){
        printf("Quete deja completee\n");
    }
    return quest->status;
}

void quest_display(const quest_t quest){
    printf("Nom: %s\nId: %d\nDescription: %s\nStatus: %s\nReward XP: %d\nReward Gold: %d\nRequired Item Quantity: %d\n\n", quest.name, quest.id, quest.desc, quest.status==ON_GOING?"ON_GOING":quest.status==COMPLETED?"COMPLETED":"NOT_STARTED", quest.reward_xp, quest.reward_gold, quest.required_item_quant);
}

void destroy_quest(quest_t **quest){
    printf("Destruction de la quete\n");
    if(*quest){
        printf("1\n");
       
        printf("2\n");
        if((*quest)->name)
        free((*quest)->name);
        printf("3\n");
        if((*quest)->desc)
            free((*quest)->desc);
        printf("4\n");
        free(*quest);
        *quest = NULL;
    }
}

void quest_list_destructor(quest_t **quest){
    for(int i=0;i<NB_MAX_QUEST;i++)

            destroy_quest(&quest[i]);
}

void quest_list_display(quest_t * const* quest){
    for(int i=0;i<NB_MAX_QUEST;i++){
        //printf("%p",quest[i]);
        if(quest[i])
            quest_display(*quest[i]);
        else
            printf("Quete non disponible\n");
    }
    
}

int accept_quest(perso *p, quest_t *quest){
    if(quest->status == NOT_STARTED && p->nb_quest < NB_MAX_QUEST){
        quest->status = ON_GOING;
        p->quest[p->nb_quest++] = quest;
        return 1;
    }
    else{
        printf("Quete deja acceptee ou nombre de quete maximum atteint\n");
        quest_status_update(quest, p);
        return 0;
    }
}

quest_npc_t *quest_npc_create(char *accept, char *refuse, char *on_going, char *completed, quest_t *quest){
    quest_npc_t *quest_npc = malloc(sizeof(quest_npc_t));
    quest_npc->accept = malloc(strlen(accept) + 1);
    strcpy(quest_npc->accept, accept);
    quest_npc->refuse = malloc(strlen(refuse) + 1);
    strcpy(quest_npc->refuse, refuse);
    quest_npc->on_going = malloc(strlen(on_going) + 1);
    strcpy(quest_npc->on_going, on_going);
    quest_npc->completed = malloc(strlen(completed) + 1);
    strcpy(quest_npc->completed, completed);

    quest_npc->quest = quest;
    return quest_npc;
}

void quest_npc_display(const quest_npc_t quest_npc){
    printf("Accept: %s\nRefuse: %s\nOn going: %s\nCompleted: %s\n", quest_npc.accept, quest_npc.refuse, quest_npc.on_going, quest_npc.completed);
    quest_display(*quest_npc.quest);
}

void destroy_quest_npc(quest_npc_t **quest_npc){
    printf("1\n");
    free((*quest_npc)->accept);
    printf("2\n");
    free((*quest_npc)->refuse);
    printf("3\n");
    free((*quest_npc)->on_going);
    printf("4\n");
    free((*quest_npc)->completed);
    printf("5\n");
    destroy_quest(&(*quest_npc)->quest);
    printf("6\n");
    free(*quest_npc);
    *quest_npc = NULL;
}