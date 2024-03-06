#include "../../include/item-inventory/common.h"
#include "../../include/item-inventory/temp.h"

void init_perso(perso *p, char *name,int end, int agi, int str, int luck,int intel){
    p->name = malloc(strlen(name) + 1);
    strcpy(p->name, name);

    p->stat = malloc(sizeof(stat_s));
    p->stat->intel = intel;
    p->stat->str = str;
    p->stat->luck = luck;
    p->stat->agi = agi;
    p->stat->end = end;
    p->stat->available=0;

    p->hp_max = p->stat->end*10;
    p->mp_max = p->stat->intel*10;

    p->hp = p->hp_max;
    p->mp = p->mp_max;
    
    p->level = 1;
    p->xp=0;
    p->xp_max=0;
    
    p->weight_max=p->stat->str*10;

    p->money=100;

    p->inventory = create_inventory();

}



void take_item(perso *p,item_t *item){
    item_t *tmp = p->inventory->head;
    int id=item->item_inv->type==EQPMT?item->item_inv->item_u->eqpmt->id:item->item_inv->item_u->ress->id;
    if(in_inventory(p,id,item->item_inv->type)>0){
        printf("item deja dans l'inventaire\n\n");
        tmp = p->inventory->head;
        while(tmp->item_inv != item->item_inv){
            tmp = tmp->suiv;
        }
        tmp->item_inv->quantity++;
    }
    else{
        printf("Ajout de l'item\n\n");
        add(item,p->inventory);

    }
}



int in_inventory(perso *p, int id, type_it type){
    item_t *tmp = p->inventory->head;
    for(int i=0;i<p->inventory->nb_item;i++){
        if(type==RESSOURCE){
            if(tmp->item_inv->item_u->ress->id == id)
                return tmp->item_inv->quantity;
            tmp = tmp->suiv;
        }
        else if (type==EQPMT){
            printf("%d == %d\n",tmp->item_inv->item_u->eqpmt->id,id);
            if(tmp->item_inv->item_u->eqpmt->id == id)
                return tmp->item_inv->quantity;
            tmp = tmp->suiv;
        }
        
        
    }
    return 0;
}

void display_perso(const perso p){
    printf("Nom: %s\n", p.name);
    printf("Niveau: %d\n\n", p.level);
    printf("XP: %d / %d\n", p.xp,p.xp_max);
    printf("HP: %d / %d\n", p.hp, p.hp_max);
    printf("MP: %d / %d\n", p.mp, p.mp_max);
    printf("Poids max: %d\n\n", p.weight_max);
    printf("Argent: %d\n\n", p.money);
    printf("Statistiques:\n");
    printf("Endurance: %d\n", p.stat->end);
    printf("Agilité: %d\n", p.stat->agi);
    printf("Force: %d\n", p.stat->str);
    printf("Chance: %d\n", p.stat->luck);
    printf("Intelligence: %d\n\n", p.stat->intel);
    display_equipement(p);
    printf("\n\nInventaire:\n");
    display_inventory(p.inventory);
}

void display_equipement(const perso p){
    printf("Equipement:\n");
    for(int i=0;i<7;i++){
        if(p.eqpmt[i]!=NULL){
            display_eqpmt(*p.eqpmt[i]);
        }
        else{
            printf("Emplacement vide\n");
        
        }
    }
}

void destroy_perso(perso **p){
    if(*p!=NULL){
        free((*p)->name);
        (*p)->name=NULL;
        free((*p)->stat);
        (*p)->stat=NULL;
        destroy_inventory(*p);
        free(*p);
        *p=NULL;
    }
}

void level_up(perso *p){
    while(p->xp>=p->xp_max){
        p->level++;
        p->xp_max*=2;
        p->xp=p->xp-p->xp_max;
        p->stat->available+=5;
    }
}