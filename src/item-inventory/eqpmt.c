#include "../../include/common/common.h"

item_t* eqpmt_creator(int id, char* name, eqpmt_type type, dmg_t dmg_type,int dgt, int def, int end, int agi, int str, int luck,int intel,int price, int poids, char* desc,int quantity) {
    //Creation of the item and allocation of memory
    item_eqpmt* eqpmt = malloc(sizeof(item_eqpmt)); 
    it_iv* item_union= malloc(sizeof(it_iv));  
    inv_item_s *inv_item = malloc(sizeof(inv_item));  
    item_t* inv = malloc(sizeof(item_t));

    //Item id, name and type of equipement
    eqpmt->id = id;
    eqpmt->name = malloc(strlen(name) + 1);
    strcpy(eqpmt->name, name);
    eqpmt->type = type;

    //Item damage type
    eqpmt->dmg_type = dmg_type;

    //Item damage and defence
    eqpmt->item_stat.defence = def;
    eqpmt->item_stat.damage = dgt;
    //Item stats modifiers
    eqpmt->item_stat.agi = agi;
    eqpmt->item_stat.str = str;
    eqpmt->item_stat.end = end;
    eqpmt->item_stat.luck = luck;
    eqpmt->item_stat.intel = intel;

    //Item price and weight
    eqpmt->price = price;
    eqpmt->poids = poids;

    //Item description
    eqpmt->desc = malloc(strlen(desc) + 1);
    strcpy(eqpmt->desc, desc);

    //Attribution to the union and the inventory item
    item_union->eqpmt = eqpmt;
    inv_item->type = EQPMT;
    inv_item->item_u = item_union;
    inv_item->quantity=quantity;

    //
    inv->item_inv=inv_item;
    inv->prec=NULL;
    inv->suiv=NULL;

    return inv;
}



void display_eqpmt(const item_eqpmt item) {
    printf("Id : %d \nNom: %s\nType: %s\nPrix item: %d\nPoids: %d\n", item.id, item.name, name_eqpmt(item.type), item.price, item.poids);
    printf("Dommage : %d\nDefense : %d\n", item.item_stat.damage, item.item_stat.defence);
    printf("Agilite : %d\nForce : %d\nEndurance : %d\nChance : %d\nIntelligence : %d\n", item.item_stat.agi, item.item_stat.str, item.item_stat.end, item.item_stat.luck, item.item_stat.intel);
    printf("Description : %s \n\n", item.desc);
}



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



void eqpmt_destructor(inv_item_s** item){ //Passer **
    //Unnalocation of memory for the text items
    free((*item)->item_u->eqpmt->desc);
    free((*item)->item_u->eqpmt->name);
    
    (*item)->item_u->eqpmt->desc=NULL;
    (*item)->item_u->eqpmt->name=NULL;

    //Unnalocation of memory for the item
    free((*item)->item_u->eqpmt);
    (*item)->item_u->eqpmt=NULL;

    //Unnalocation of memory for the union
    free((*item)->item_u);
    (*item)->item_u=NULL;


    //Unnalocation of memory for the inventory item
    free(*item);
    *item=NULL;
}


void use_eqpmt(perso *p,item_eqpmt *eqpmt){
    switch (eqpmt->type){
        case HEAD:
            p->eqpmt[0]=eqpmt;
            break;
        case BODY:
            p->eqpmt[1]=eqpmt;
            break;
        case LEGS:
            p->eqpmt[2]=eqpmt;
            break;
        case FOOT:
            p->eqpmt[3]=eqpmt;
            break;
        case RING:
            p->eqpmt[4]=eqpmt;
            break;
        case WEAPON:
            p->eqpmt[5]=eqpmt;
            break;
        case SHIELD:
            p->eqpmt[6]=eqpmt;
            break;
        default:
            printf("Erreur d'utilisation\n");
            break;
    }
}

void remove_eqpmt(perso *p, item_t *item){
    switch (item->item_inv->item_u->eqpmt->type){
        case HEAD:
            p->eqpmt[0]=NULL;
            break;

        case BODY:
            p->eqpmt[1]=NULL;
            break;

        case LEGS:
            p->eqpmt[2]=NULL;
            break;

        case FOOT:
            p->eqpmt[3]=NULL;
            break;

        case RING:
            p->eqpmt[4]=NULL;
            break;

        case WEAPON:
            p->eqpmt[5]=NULL;
            break;

        case SHIELD:
            p->eqpmt[6]=NULL;
            break;

        default:
            printf("Erreur de suppression\n");
            break;
    }
}


int is_equip(perso *p, item_t *item){
    int id= item->item_inv->item_u->eqpmt->id;
    eqpmt_type type_equip= item->item_inv->item_u->eqpmt->type;
    switch (type_equip){
        case HEAD:
            if(p->eqpmt[0]==NULL)
                return 0;
            else
                return p->eqpmt[0]->id==id;
            break;

        case BODY:
            if(p->eqpmt[1]==NULL)
                return 0;
            else
                return p->eqpmt[1]->id==id;
            break;
        case LEGS:
            if(p->eqpmt[2]==NULL)
                return 0;
            else
                return p->eqpmt[2]->id==id;
            break;

        case FOOT:
            if(p->eqpmt[3]==NULL)
                return 0;
            else
                return p->eqpmt[3]->id==id;
            break;

        case RING:
            if(p->eqpmt[4]==NULL)
                return 0;
            else
                return p->eqpmt[4]->id==id;
            break;

        case WEAPON:
            if(p->eqpmt[5]==NULL)
                return 0;
            else
                return p->eqpmt[5]->id==id;
            break;
        case SHIELD:
            if(p->eqpmt[6]==NULL)
                return 0;
            else
                return p->eqpmt[6]->id==id;
            break;

        default:
            printf("Erreur de verification\n");
            break;
    }

    return -1;
    
}