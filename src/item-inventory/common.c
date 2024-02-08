#include "../../include/item-inventory/common.h"


void display_common(const inv_item_s item){
    switch (item.type){
        case EQPMT:
            printf("Quantité: %d\n", item.quantity);
            display_eqpmt(*item.item_u->eqpmt);
            break;
        case RESSOURCE:
            printf("Quantité: %d\n", item.quantity);
            display_ress(*item.item_u->ress);
            break;
        default:
            printf("Erreur d'affichage\n");
            break;
    }
}



void destroy_common(item_t **item){
    switch ((*item)->item_inv->type){
        case EQPMT:
            eqpmt_destructor(&(*item)->item_inv);
            break;
        case RESSOURCE:
            ress_destructor(&(*item)->item_inv);
            break;
        default:
            printf("Erreur de destruction\n");
            break;
    }
    
    (*item)->prec=NULL;
    (*item)->suiv=NULL;
    free(*item);
    *item=NULL;
}

