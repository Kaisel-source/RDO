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

item_eqpmt* item_creator(int id, char* name, equip type, int price, int poids, int dgt, int def, int end, int agi, int str, int luck) {
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

int add_inventory(inventory *bag,inv_item *item){
    bag->end->suiv=item;
    bag=bag->end->suiv;
    bag->end->suiv=bag->head;
    

    return 0;

}

int main() {
    item_eqpmt* test,*test1;
    test = item_creator(0, "epee", WEAPON, 10, 10, 5, 0, 0, 0, 0, 0);
    test1 = item_creator(1, "bouclier", SHIELD, 100, 15, 5, 0, 0, 0, 0, 0);
    affich_item(*test);
    affich_item(*test1);

    free(test->name);
    free(test);

    return 0;
}
