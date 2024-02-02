#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test_item.h"

char* name_eqpmt(int x) {
    switch (x) {
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

void affich_item(item_eqpmt x) {
    printf("Id : %d \nNom: %s\nType: %s\nPrix: %d\nPoids: %d\n\n", x.id, x.name, name_eqpmt(x.type), x.price, x.poids);
}

item_eqpmt* item_creator(int id, char* name, eqpmt_type type, int price, int poids, int dgt, int def, int end, int agi, int str, int luck) {
    item_eqpmt* item1 = malloc(sizeof(item_eqpmt));
    item1->id = id;
    item1->name = malloc(strlen(name) + 1);
    strcpy(item1->name, name);
    item1->type = type;
    item1->price = price;
    item1->poids = poids;

    item1->item.agi = agi;
    item1->item.str = str;
    item1->item.end = end;
    item1->item.luck = luck;

    item1->item.defence = def;
    item1->item.damage = dgt;

    return item1;
}



// Primitives

item_list * create_list(){

    item_list *list = malloc(sizeof(item_list));
    list->head = NULL;
    list->queue = NULL;
    return list;
}

int empty_list(item_list *list){

    return (list->head == NULL);
}

void add_first(item_t *item, item_list *list){

    if (empty_list(list)){
        list->head = item;
        list->queue = list->head;
    }
    else{
        item->prec = list->queue;
        item->suiv = list->head;
        list->head = item;
    }
}

void add_last(item_t *item, item_list *list){

    if (empty_list(list)){
        list->head = item;
        list->queue = list->head;
    }
    else{
        item->prec = list->queue;
        list->queue->suiv = item; 
        list->queue = item; 
    }
}

void print_list(item_list *list){

    item_t *current = list->head;

    if(empty_list(list)) printf("La liste est vide !\n");

    printf("[ ");

    while (current != NULL){

        affich_item(*(current->item));
        current = current->suiv;
        
    }

}





// Main


int main(){

    item_list *list = create_list();
    item_eqpmt* test,*test1;
    
    item_t *item1 = malloc(sizeof(item_t));
    item_t *item2 = malloc(sizeof(item_t));
    
    
    test = item_creator(0, "epee", WEAPON, 10, 10, 5, 0, 0, 0, 0, 0);
    test1 = item_creator(1, "bouclier", SHIELD, 100, 15, 5, 0, 0, 0, 0, 0);


    free(test->name);
    free(test);

   
    add_last(item1, list);
    add_last(item2, list);

    print_list(list);
    

    print_list(list);

    return 0;
}