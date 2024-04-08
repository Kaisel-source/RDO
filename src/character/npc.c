#include "../../include/common/common.h"
#include <stdarg.h>
npc_s * npc_creator(char* name, char* dialog, int money, int nb_quest,...){
    npc_s * npc = malloc(sizeof(npc_s));

    npc->name=malloc(strlen(name)+1);
    npc->dialog=malloc(strlen(dialog)+1);

    strcpy(npc->name,name);
    strcpy(npc->dialog,dialog);

    npc->money = money;
    npc->inventory = create_inventory();
    npc->nb_quest = nb_quest;

    npc->quest = malloc(sizeof(quest_npc_t)*npc->nb_quest);
    
    va_list args;
    va_start(args,nb_quest);
    for(int i=0;i<nb_quest;i++){
        npc->quest[i]=va_arg(args,quest_npc_t*);
    }
    return npc;
}

void destroy_npc(npc_s ** npc){
    free((*npc)->name);
    free((*npc)->dialog);
    destroy_stockage(&(*npc)->inventory);
    for(int i=0;i<(*npc)->nb_quest;i++){
        destroy_quest_npc(&(*npc)->quest[i]);
    }
    free((*npc)->quest);
    free(*npc);
    *npc=NULL;
}

void display_npc(const npc_s npc){
    printf("Nom : %s\nDialog : %s\nArgent : %d\n",npc.name,npc.dialog,npc.money);
    printf("Nb quete : %d\n",npc.nb_quest);
    for(int i=0;i<npc.nb_quest;i++){
        printf("Quete %d\n",i);
        quest_npc_display(*npc.quest[i]);
    }
}

void npc_quest_interaction(perso *p, npc_s *npc){
    int choice,i;
    printf("Quel quete voulez vous faire ?\n");
    for(i=0;(i<npc->nb_quest)&&npc->quest[i]->quest->status==COMPLETED;i++);
    if(i==npc->nb_quest){
        printf("Aucune quete disponible\n");
        return;
    }
    else{
        quest_display(*npc->quest[i]->quest);
    }
    scanf("%d",&choice);
    switch(choice){
        case 1:
            printf("Accepter la quete\n");
            accept_quest(p,npc->quest[choice]->quest);
            break;
        case 2:
            printf("Refuser la quete\n");
            break;
        default:
            printf("Choix invalide\n");
            break;
    }
}

void npc_interact(perso *p, npc_s *npc){
    printf("Interaction avec %s\n",npc->name);
    printf("%s\n",npc->dialog);
    int choice;
    printf("1: Parler\n2: Vendre\n3: Acheter\n4: Quetes\n");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            printf("Parler\n");
            break;
        case 2:
            printf("Vendre\n");
            break;
        case 3:
            printf("Acheter\n");
            break;
        case 4:
            printf("Quetes\n");
            npc_quest_interaction(p,npc);
            break;
        default:
            printf("Choix invalide\n");
            break;
    }
}