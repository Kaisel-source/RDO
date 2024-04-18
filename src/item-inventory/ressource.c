#include "../../include/common/common.h"


item_t * ress_creator(int id, char* name, int price, int poids, char* desc,int quantity) {
    //Creation of the ressource and allocation of memory
    item_ress* ress = malloc(sizeof(item_eqpmt));
    it_iv* item_union= malloc(sizeof(it_iv));
    inv_item_s *inv_item = malloc(sizeof(inv_item));
    item_t* inv = malloc(sizeof(item_t));

    //Ressource id and name
    ress->id = id;
    ress->name = malloc(strlen(name) + 1);
    strcpy(ress->name, name);

    //Ressource price and weight
    ress->price = price;
    ress->poids = poids;

    //Ressource description
    ress->desc = malloc(strlen(desc) + 1);
    strcpy(ress->desc, desc);



    //Attribution to the union and the inventory item
    item_union->ress = ress;
    inv_item->type = RESSOURCE;
    inv_item->quantity=quantity;
    inv_item->item_u = item_union;

    //
    inv->item_inv=inv_item;
    inv->prec=NULL;
    inv->suiv=NULL;

    return inv;
}



void display_ress(const item_ress ress) {
    printf("Id : %d \nNom: %s\nPrix item: %d\nPoids: %d\nDescription : %s \n\n", ress.id, ress.name, ress.price, ress.poids,ress.desc);
}



void ress_destructor(inv_item_s** item){
    //Unnalocation of memory for the text items
    printf("Unnallocation of memory for the text items\n");
    free((*item)->item_u->ress->desc);
    free((*item)->item_u->ress->name);
    (*item)->item_u->ress->desc=NULL;
    (*item)->item_u->ress->name=NULL;

    printf("Unnallocation of memory for the union\n");
    //Unnalocation of memory for the item
    free((*item)->item_u->ress);
    (*item)->item_u->ress=NULL;

    printf("Unnallocation of memory for the inventory item\n");
    //Unnalocation of memory for the union
    free((*item)->item_u);
    (*item)->item_u=NULL;

    printf("Unnallocation of memory for the inventory item\n");
    //Unnalocation of memory for the inventory item
    free(*item);
    *item=NULL;


    

}


