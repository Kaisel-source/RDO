#include "../../include/item-inventory/main.h"


int main(){
    
    printf("Creation du perso \n\n");
    perso *p = malloc(sizeof(perso));
    init_perso(p, "toto", 10,10,10,10,10);

    printf("Creation des stats de l'item \n\n");
    item_t *item ;
    item_t *item2 ;
    item_t *item3 ;
    item = eqpmt_creator(1,"epee", WEAPON, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "une epee");
    item2 = eqpmt_creator(2,"bouclier", SHIELD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un bouclier");
    item3 = eqpmt_creator(3,"Casque", HEAD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un casque");

    
    printf("Ajout des items dans l'inventaire \n\n");
    printf("Ajout de l'item 1 \n\n");
    add_first(item, p->inventory);
    display_inventory(p->inventory);

    

    printf("\n\n----------------------------------\n\n");
    printf("\n\n----------------------------------\n\n");

    printf("Ajout de l'item 2 \n\n");
    add_current(item2, p->inventory);
    display_inventory(p->inventory);
    printf("----------------------------------\n");
    suiv_current(p->inventory);
    display_current(p->inventory);

    printf("\n\n----------------------------------\n\n");
    printf("\n\n----------------------------------\n\n");
    printf("Ajout de l'item 3 \n\n");
    suiv_current(p->inventory);
    add_current(item3, p->inventory);
    display_inventory(p->inventory);



    printf("\n\n----------------------------------\n\n");
    printf("TAKE ITEM");
    printf("\n\n----------------------------------\n\n");
    printf("take item 1\n\n");
    take_item(p, item);
    printf("take item 3\n\n");
    take_item(p, item3);    
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

    printf("\n\n----------------------------------\n\n");
    printf("INVENTORY");
    printf("\n\n----------------------------------\n");
    display_inventory(p->inventory);

    printf("\n\n----------------------------------\n\n");
    printf("Current");
    printf("\n\n----------------------------------\n");

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


    printf("\nDestruction du perso \n\n");
    destroy_perso(&p);

    return 0;
}