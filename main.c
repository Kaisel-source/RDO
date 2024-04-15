#include "../../include/item-inventory/main.h"


int main(){
    
    game_s *g = malloc(sizeof(game_s));
    game_init_game(g);
    printf("Creation du perso \n\n");
    perso *p = malloc(sizeof(perso));
    init_perso(p, "toto", 10,10,10,10,10);

    printf("Creation des stats de l'item \n\n");
    item_t *item ;
    item_t *item2 ;
    item_t *item3 ;
    item_t *item4 ;
    item_t *ress;
    quest_t *q;
    game_add_main_perso(g,p);
    
    item = eqpmt_creator(1,"epee", WEAPON, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "une epee",1);
    item2 = eqpmt_creator(2,"bouclier", SHIELD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un bouclier",1);
    item3 = eqpmt_creator(3,"Casque", HEAD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un casque",1);
    item4 = eqpmt_creator(4,"Armure", BODY, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "une armure",1);

    ress = ress_creator(1,"ressource",10,10,"Test",1);
    q=quest_create("Un pas a la fois","Tuer 10 Monstres",1,NOT_STARTED,100,10,item,1,ress);
    game_add_quest(g,q);
    printf("Creation des items \n\n");
    game_add_item(g,item);
    printf("item 1\n");
    game_add_item(g,item2);
    printf("item 2\n");
    game_add_item(g,item3);
    printf("item 3\n");
    game_add_item(g,item4);
    printf("item 4\n");
    game_add_item(g,ress);
    printf("Creation des quetes \n\n");
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
    printf("\n\n----------------------------------\n");
    printf("QUETE");
    printf("\n\n----------------------------------\n");
    
    take_item(p, ress);
    
    accept_quest(p,q);
    printf("\n\n----------------------------------\n");
    printf("PERSONNAGE");
    printf("\n\n----------------------------------\n");
    display_perso(*p);

    
    printf("\n\n----------------------------------\n");
    printf("\n\n----------------------------------\n");
    accept_quest(p,q);

    
    printf("\n\n----------------------------------\n");
    printf("\n\n----------------------------------\n");
    printf("\n\n----------------------------------\n");
    printf("PERSONNAGE");
    printf("\n\n----------------------------------\n");
    display_perso(*p);
    /*
    printf("\n\n----------------------------------\n");
    printf("SAVING...");
    printf("\n\n----------------------------------\n");
    printf("%s\n",export(p)?"Succes Sauvegarde":"Echec Sauvegarde");
    printf("Fin Sauvegarde...\n");
    printf("\nDestruction du perso \n\n");
    destroy_perso(&p);

    printf("\n\n----------------------------------\n");
    printf("IMPORT...");
    printf("\n\n----------------------------------\n");
    p=malloc(sizeof(perso));
    import(p);
    display_perso(*p);
    */
    printf("\n\n----------------------------------\n");
    printf("TURN OFF\n");
    printf("\n\n----------------------------------\n");
    game_destroy_game(&g);
    return 0;
}