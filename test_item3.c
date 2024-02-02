/**
 * @brief 
 * @file test_item3.c
 * @date 2018-12-18
 * @author Aymeric [Yun]
 * @version 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_item.h"



/**
 * @brief display the item information in the console
 * @warning This function is only working for the item_eqpmt type
 * @param item 
 * @return ** void 
 */
void display_eqpmt(const item_eqpmt item) {
    printf("Id : %d \nNom: %s\nType: %s\nPrix item: %d\nPoids: %d\n", item.id, item.name, name_eqpmt(item.type), item.price, item.poids);
    printf("Dommage : %d\nDefense : %d\n", item.item_stat.damage, item.item_stat.defence);
    printf("Agilite : %d\nForce : %d\nEndurance : %d\nChance : %d\nIntelligence : %d\n", item.item_stat.agi, item.item_stat.str, item.item_stat.end, item.item_stat.luck, item.item_stat.intel);
    printf("Description : %s \n\n", item.desc);
}

/**
 * @brief display the ressource information in the console
 * @warning This function is only working for the item_ress type
 * @param ress 
 * @return ** void 
 */
void display_ress(const item_ress ress) {
    printf("Id : %d \nNom: %s\nPrix item: %d\nPoids: %d\nDescription : %s \n\n", ress.id, ress.name, ress.price, ress.poids,ress.desc);
}

void display_common(const inv_item_s item){
    switch (item.type){
        case EQPMT:
            display_eqpmt(*item.item_u->eqpmt);
            break;
        case RESSOURCE:
            display_ress(*item.item_u->ress);
            break;
        default:
            printf("Erreur d'affichage\n");
            break;
    }
}

void destroy_common(item_t *item){
    switch (item->item_inv->type){
        case EQPMT:
            item_destructor(item->item_inv);
            break;
        case RESSOURCE:
            ress_destructor(item->item_inv);
            break;
        default:
            printf("Erreur de destruction\n");
            break;
    }
    free(item);
    item=NULL;
}

/**
 * @brief : Give the string corresponding to the type of equipement for the enum "eqpmt_type"
 * 
 * @param type : Type of equipement  
 * @return ** char* : string corresponding to the type of equipement
 */
char* name_eqpmt(int type) {
    switch (type) {
        case NONE:
            return "Aucun";
        case HEAD:
            return "Head";
        case BODY:
            return "Body";
        case LEGS:
            return "Legs";
        case FOOT:
            return "Foot";
        case RING:
            return "Ring";
        case WEAPON:
            return "Weapon";
        case SHIELD:
            return "Shield";
        default:
            return "Non-Défini";
    }
}

/**
 * @brief : Create an item and convert it to an inventory item
 * 
 * @param id : Corresponds to the id of the item
 * @param name : Name of the item
 * @param type : Type of equipement
 * @param dmg_type : Damage type of the item
 * @param dgt : Damage of the item
 * @param def : Defence of the item
 * @param end : Endurance modifier of the item
 * @param agi : Agility modifier of the item
 * @param str : Strength modifier of the item
 * @param luck : Luck modifier of the item
 * @param intel : Intelligence modifier of the item
 * @param price : Price of the item for selling with pnj
 * @param poids : Weight of the item for the inventory capacity
 * @param desc : Description of the item
 * @return ** item_t* : Return the item converted to an inventory item
 */

item_t* item_creator(int id, char* name, eqpmt_type type, dmg_t dmg_type,int dgt, int def, int end, int agi, int str, int luck,int intel,int price, int poids, char* desc) {
    //Creation of the item and allocation of memory
    item_eqpmt* item = malloc(sizeof(item_eqpmt));
    it_iv* item_union= malloc(sizeof(it_iv));
    inv_item_s *inv_item = malloc(sizeof(inv_item));
    item_t* inv = malloc(sizeof(item_t));

    //Item id, name and type of equipement
    item->id = id;
    item->name = malloc(strlen(name) + 1);
    strcpy(item->name, name);
    item->type = type;

    //Item damage type
    item->dmg_type = dmg_type;

    //Item damage and defence
    item->item_stat.defence = def;
    item->item_stat.damage = dgt;

    //Item stats modifiers
    item->item_stat.agi = agi;
    item->item_stat.str = str;
    item->item_stat.end = end;
    item->item_stat.luck = luck;
    item->item_stat.intel = intel;

    //Item price and weight
    item->price = price;
    item->poids = poids;

    //Item description
    item->desc = malloc(strlen(desc) + 1);
    strcpy(item->desc, desc);
    



    //Attribution to the union and the inventory item
    item_union->eqpmt = item;
    inv_item->type = EQPMT;
    inv_item->item_u = item_union;

    //
    inv->item_inv=inv_item;
    inv->prec=NULL;
    inv->suiv=NULL;

    return inv;
}

/**
 * @brief Unallocate the memory of the equipement and destroy it
 * @warning This function is only working for the item_eqpmt type
 * @param item 
 */

void item_destructor(inv_item_s* item){
    //Unnalocation of memory for the text items
    free(item->item_u->eqpmt->desc);
    free(item->item_u->eqpmt->name);
    item->item_u->eqpmt->desc=NULL;
    item->item_u->eqpmt->name=NULL;

    //Unnalocation of memory for the item
    free(item->item_u->eqpmt);
    item->item_u->eqpmt=NULL;

    //Unnalocation of memory for the union
    free(item->item_u);
    item->item_u=NULL;

    //Unnalocation of memory for the inventory item
    free(item);
    item=NULL;
}


/**
 * @brief Unnallocate the memory of the ressource and destroy it
 * @warning This function is only working for the item_ress type____
 * @param item 
 */
void ress_destructor(inv_item_s* item){
    //Unnalocation of memory for the text items
    free(item->item_u->ress->desc);
    free(item->item_u->ress->name);
    item->item_u->ress->desc=NULL;
    item->item_u->ress->name=NULL;

    //Unnalocation of memory for the item
    free(item->item_u->ress);
    item->item_u->ress=NULL;

    //Unnalocation of memory for the union
    free(item->item_u);
    item->item_u=NULL;

    //Unnalocation of memory for the inventory item
    free(item);
    item=NULL;

    

}

/**
 * @brief Create a ressource object an convert it to an inventory item
 * 
 * @param id : Corresponds to the id of the ressource
 * @param name : Name of the ressource
 * @param price : Price of the ressource for selling with pnj
 * @param poids : Weight of the ressource for the inventory capacity
 * @param desc  :  Description of the ressource
 * @return item_t*
 */
item_t* ress_creator(int id, char* name, int price, int poids, char* desc) {
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
    inv_item->item_u = item_union;

    //
    inv->item_inv=inv_item;
    inv->prec=NULL;
    inv->suiv=NULL;

    return inv;
}

/**
 * @brief Create a inventory object
 * 
 * @return item_list* 
 */
item_list * create_inventory(){
    item_list *list = malloc(sizeof(item_list));
    list->head = NULL;
    list->queue = NULL;
    return list;
}

/**
 * @brief Return if the list is empty
 * 
 * @param list 
 * @return int 
 */
int empty_inventory(item_list *list){
    return (list->head == NULL);
}

/**
 * @brief 
 * 
 * @param item 
 * @param list 
 */
void add_first(item_t *item, item_list *list){
    
    if (empty_inventory(list)){
        list->head = item;
        list->queue = list->head;
    }
    else{
        item->prec = list->queue;
        item->suiv = list->head;
        list->head = item;
    }
    weight_calc(list);
}

/**
 * @brief 
 * 
 * @param item 
 * @param list 
 */
void add_last(item_t *item, item_list *list){

    if (empty_inventory(list)){
        list->head = item;
        list->queue = list->head;
    }
    else{
        item->prec = list->queue;
        list->queue->suiv = item; 
        list->queue = item; 
    }
    weight_calc(list);
}

void display_inventory(const item_list *list){
    item_t *item = list->head;
    while (item != NULL){
        display_common(*item->item_inv);
        item = item->suiv;
    }
    printf("Poids total : %d\n",list->weight);
}

void destroy_inventory(item_list *list){
    item_t *item = list->head;
    while (item != NULL){
        destroy_common(item);
        item = item->suiv;
    }
    free(list);
    list=NULL;
}

void weight_calc(item_list *list){
    item_t *item = list->head;
    list->weight=0;
    while (item != NULL){
        switch (item->item_inv->type){
            case EQPMT:
                list->weight += item->item_inv->item_u->eqpmt->poids;
                break;
            case RESSOURCE:
                list->weight += item->item_inv->item_u->ress->poids;
                break;
            default:
                printf("Erreur de calcul de poids\n");
                break;
        }
        item = item->suiv;
    }
}

int main()
{
    item_list *list = create_inventory();
    item_t *item1 = item_creator(1,"Epee",WEAPON,PHYSICAL,10,0,0,0,0,0,0,10,10,"Une epee");
    item_t *item2 = item_creator(2,"Bouclier",SHIELD,PHYSICAL,0,10,0,0,0,0,0,10,10,"Un bouclier");
    item_t *item3 = ress_creator(3,"Potion",10,10,"Une potion");
    add_first(item1,list);
    add_first(item2,list);
    add_last(item3,list);

    display_inventory(list);
    destroy_inventory(list);
    return 0;
}