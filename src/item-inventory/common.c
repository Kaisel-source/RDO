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
        case CONSUM:
            printf("Quantité: %d\n", item.quantity);
            display_conso(*item.item_u->conso);
            break;
        default:
            printf("Erreur d'affichage\n");
            break;
    }
}



void destroy_common(perso *p){
    item_t **item=&(p->inventory->current);
    switch ((*item)->item_inv->type){
        case EQPMT:
            if(is_equip(p,*item))
                remove_eqpmt(p, *item);
            eqpmt_destructor(&(*item)->item_inv);
            break;
        case RESSOURCE:
            ress_destructor(&(*item)->item_inv);
            break;
        case CONSUM:
            conso_destructor(&(*item)->item_inv);
            break;
        default:
            printf("Erreur de destruction\n");
            break;
    }
    
    (*item)->prec=NULL;
    (*item)->suiv=NULL;
    free(*item);
    *item=NULL;
    p->inventory->nb_item--;
}


void use_common(perso *p){
    item_t *item=p->inventory->current;
    switch (item->item_inv->type){
        case EQPMT:
            use_eqpmt(p,item->item_inv->item_u->eqpmt);
            break;
        case CONSUM:
            
            break;
        default:
            printf("Erreur d'utilisation\n");
            break;
    }
    item->item_inv->quantity--;
    check_inventory(p);
}

void add_n(perso *p, int nb){
    item_t *item=p->inventory->current;
    item->item_inv->quantity+=nb;
    check_inventory(p);
    
}
void remove_n(perso *p, int nb){
    item_t *item=p->inventory->current;
    item->item_inv->quantity-=nb;
    check_inventory(p);
}