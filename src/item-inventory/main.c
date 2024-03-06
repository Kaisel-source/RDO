#include "../../include/item-inventory/main.h"


int main(){
    
    printf("Creation du perso \n\n");
    perso *p = malloc(sizeof(perso));
    init_perso(p, "toto", 10,10,10,10,10);

    printf("Creation des stats de l'item \n\n");
    item_t *item ;
    item_t *item2 ;
    item_t *item3 ;
    item_t *item4 ;
    item = eqpmt_creator(1,"epee", WEAPON, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "une epee");
    item2 = eqpmt_creator(2,"bouclier", SHIELD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un bouclier");
    item3 = eqpmt_creator(3,"Casque", HEAD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un casque");
    item4 = eqpmt_creator(4,"Armure", BODY, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "une armure");
    
    printf("Ajout des items dans l'inventaire \n\n");
    printf("Ajout de l'item 1 \n\n");
    add(item, p->inventory);
    display_inventory(p->inventory);
    printf("nb_elm : %d\n",p->inventory->nb_item);
    

    printf("\n\n----------------------------------\n\n");
    printf("\n\n----------------------------------\n\n");

    printf("Ajout de l'item 2 \n\n");
    int id=item2->item_inv->type==EQPMT?item2->item_inv->item_u->eqpmt->id:item2->item_inv->item_u->ress->id;
    printf("ID:%d  QUANT : %d \n",id,in_inventory(p,item2->item_inv->type,id));
    take_item(p, item2); 
    display_inventory(p->inventory);
    printf("----------------------------------\n");
    suiv_current(p->inventory);
    display_current(p->inventory);
    printf("nb_elm : %d\n",p->inventory->nb_item);

    printf("\n\n----------------------------------\n\n");
    printf("\n\n----------------------------------\n\n");
    printf("Ajout de l'item 3 \n\n");
    suiv_current(p->inventory);
    take_item(p, item3); 
    
    display_inventory(p->inventory);
    printf("nb_elm : %d\n",p->inventory->nb_item);


    printf("\n\n----------------------------------\n\n");
    printf("TAKE ITEM");
    printf("\n\n----------------------------------\n\n");
    printf("take item 1\n\n");
    take_item(p, item);
    printf("nb_elm : %d\n",p->inventory->nb_item);
    take_item(p, item3);
    printf("Display\n");

    printf("take item 4\n\n");
    take_item(p, item4);
  
    display_inventory(p->inventory);


    printf("\n\n----------------------------------\n\n");
    printf("SUIV");
    printf("\n\n----------------------------------\n");
    display_current(p->inventory);
    suiv_current(p->inventory);
    printf("----------------------------------\n");
    display_current(p->inventory);
    suiv_current(p->inventory);
    printf("----------------------------------\n");
    display_current(p->inventory);
    suiv_current(p->inventory);
    printf("----------------------------------\n");
    display_current(p->inventory);
    suiv_current(p->inventory);
    printf("nb_elm : %d\n",p->inventory->nb_item);
    printf("\n\n----------------------------------\n\n");



    printf("INVENTORY");
    printf("\n\n----------------------------------\n");
    display_inventory(p->inventory);
    printf("nb_elm : %d\n",p->inventory->nb_item);
    printf("\n\n----------------------------------\n\n");


    printf("Current");
    printf("\n\n----------------------------------\n");
    printf("nb_elm : %d\n",p->inventory->nb_item);  
    p->inventory->current=find_queue(p->inventory);
    display_current(p->inventory);


    printf("\n\n----------------------------------\n\n");
    printf("PREC");
    printf("\n\n----------------------------------\n");
    prec_current(p->inventory);
    display_current(p->inventory);
    printf("----------------------------------\n");
    prec_current(p->inventory);
    display_current(p->inventory);
    printf("----------------------------------\n");
    prec_current(p->inventory); // XX
    display_current(p->inventory);
    printf("----------------------------------\n");
    prec_current(p->inventory);
    display_current(p->inventory);

    printf("Perso");
    printf("\n\n----------------------------------\n");
    display_perso(*p);
    printf("\nDestruction du perso \n\n");
    destroy_perso(&p);

    return 0;
}