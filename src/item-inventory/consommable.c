#include "../../include/item-inventory/consommable.h"

item_t* conso_create(char* name,int id, int poids, int price, int hp, int mp, int xp,int available,char *desc,int quantity)
{
    item_conso *conso = malloc(sizeof(item_conso));
    it_iv* item_union= malloc(sizeof(it_iv));  // X
    inv_item_s *inv_item = malloc(sizeof(inv_item));  
    item_t* inv = malloc(sizeof(item_t));

    conso->name = malloc(strlen(name) + 1);
    strcpy(conso->name, name);
    conso->id = id;
    conso->poids = poids;
    conso->price = price;
    
    conso->hp = hp;
    conso->mp = mp;
    conso->exp = xp;

    conso->available = available;

    conso->desc = malloc(strlen(desc) + 1);
    strcpy(conso->desc, desc);


    //Attribution to the union and the inventory item
    item_union->conso = conso;
    inv_item->type = CONSUM;
    inv_item->item_u = item_union;
    inv_item->quantity=quantity;

    //
    inv->item_inv=inv_item;
    inv->prec=NULL;
    inv->suiv=NULL;

    return inv;
}



void display_conso(const item_conso conso)
{
    printf("Nom: %s\nId: %d\nPoids: %d\nPrix: %d\nHP: %d\nMP: %d\nXP: %d\nAvailable: %d\nDescription: %s\n\n", conso.name, conso.id, conso.poids, conso.price, conso.hp, conso.mp, conso.exp,conso.available, conso.desc);
}



void conso_destructor(inv_item_s** item){ 
    //Unnalocation of memory for the text items
    free((*item)->item_u->conso->desc);
    free((*item)->item_u->conso->name);
    (*item)->item_u->conso->desc=NULL;
    (*item)->item_u->conso->name=NULL;
    

    //Unnalocation of memory for the item
    free((*item)->item_u->conso);
    (*item)->item_u->conso=NULL;

    //Unnalocation of memory for the union
    free((*item)->item_u);
    (*item)->item_u=NULL;


    //Unnalocation of memory for the inventory item
    free(*item);
    *item=NULL;
}



void use_conso(perso* p , item_conso* conso)
{
    p->hp += conso->hp;
    p->mp += conso->mp;
    p->xp += conso->exp;
    if(p->hp > p->hp_max)
    {
        p->hp = p->hp_max;
    }
    if(p->mp > p->mp_max)
    {
        p->mp = p->mp_max;
    }
    if(p->xp > p->xp_max)
    {
        level_up(p);
    }
    
}