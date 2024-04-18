#include "../../include/common/common.h"
#include <unistd.h>




int import(perso **p) {
    if (p == NULL || *p == NULL) {
        printf("Erreur: Le pointeur vers le personnage est NULL.\n");
        return 0;
    }

    FILE *fp = fopen("inv.txt", "r");
    if (!fp) {
        printf("Erreur: Impossible d'ouvrir le fichier.\n");
        return 0;
    }

    int id[7], nb_item;
    item_t *elm;
    item_eqpmt *eqpmt;
    item_ress *ress;
    item_conso *conso;

    /* Lecture des données du personnage */
    fscanf(fp, "Nom du personnage: %[^\n]%*c", (*p)->name);
    printf("Nom du personnage: %s\n", (*p)->name);

    fscanf(fp, "Statistiques: Intel:%d, Str:%d, Luck:%d, Agi:%d, End:%d%*c", &(*p)->stat->intel, &(*p)->stat->str, &(*p)->stat->luck, &(*p)->stat->agi, &(*p)->stat->end);
    printf("Statistiques: Intel:%d, Str:%d, Luck:%d, Agi:%d, End:%d\n", (*p)->stat->intel, (*p)->stat->str, (*p)->stat->luck, (*p)->stat->agi, (*p)->stat->end);

    fscanf(fp, "HP: %d/%d, MP: %d/%d, XP: %d/%d, Level: %d%*c", &(*p)->hp, &(*p)->hp_max, &(*p)->mp, &(*p)->mp_max, &(*p)->xp, &(*p)->xp_max, &(*p)->level);
    printf("HP: %d/%d, MP: %d/%d, XP: %d/%d, Level: %d\n", (*p)->hp, (*p)->hp_max, (*p)->mp, (*p)->mp_max, (*p)->xp, (*p)->xp_max, (*p)->level);

    fscanf(fp, "Poids maximal supporté: %d, Argent: %d%*c", &(*p)->weight_max, &(*p)->money);
    printf("Poids maximal supporté: %d, Argent: %d\n", (*p)->weight_max, (*p)->money);

    fscanf(fp, "Pos x: %d, y: %d%*c", &(*p)->x, &(*p)->y);
    printf("Pos x: %d, y: %d\n", (*p)->x, (*p)->y);

    fscanf(fp, "Map x: %d, y: %d%*c", &(*p)->map_x, &(*p)->map_y);
    printf("Map x: %d, y: %d\n", (*p)->map_x, (*p)->map_y);

    fscanf(fp, "Équipements équipés:%*c");

    /* Lecture des équipements équipés */
    for (int i = 0; i < 7; i++) {
        fscanf(fp, "Emplacement %d: ID de l'équipement: %d%*c", &i, &id[i]);
        printf("Emplacement %d: ID de l'équipement: %d\n", i+1, id[i]);
        // Charger l'équipement correspondant à l'ID id[i]
        // Assurez-vous que les éléments de l'inventaire sont correctement initialisés avant d'utiliser cette fonction
    }

    /* Lecture de l'inventaire */
    /* Lecture de l'inventaire */
    fscanf(fp, "Nombre d'objets dans l'inventaire: %d%*c", &nb_item);
    printf("Nombre d'objets dans l'inventaire: %d\n", nb_item);
    for (int i = 0; i < nb_item; i++) {
        int type;
        // Lecture du type d'objet correctement
        fscanf(fp, "Type d'objet: %d%*c", &type);
        printf("Type d'objet: %d\n", type);
        elm = malloc(sizeof(item_t)); // Allouer de la mémoire pour un nouvel élément d'inventaire
        switch (type) {
            case RESSOURCE:
                ress = malloc(sizeof(item_ress));
                fscanf(fp, "Ressource - ID: %d, Nom: %[^\n], Prix: %d, Poids: %d, Description: %[^\n], Quantité: %d%*c", &ress->id, ress->name, &ress->price, &ress->poids, ress->desc, &elm->item_inv->quantity);
                printf("Ressource - ID: %d, Nom: %s, Prix: %d, Poids: %d, Description: %s, Quantité: %d\n", ress->id, ress->name, ress->price, ress->poids, ress->desc, elm->item_inv->quantity);
                // Ajouter l'objet ressource à l'inventaire du personnage
                break;
            case EQPMT:
                eqpmt = malloc(sizeof(item_eqpmt));
                fscanf(fp, "Équipement - ID: %d, Nom: %[^\n], Type: %d, Type de dégâts: %d, Dégâts: %d, Défense: %d, Force: %d, Agilité: %d, Endurance: %d, Chance: %d, Intelligence: %d, Prix: %d, Poids: %d, Description: %[^\n], Quantité: %d%*c",
                    &eqpmt->id, eqpmt->name, &eqpmt->type, &eqpmt->dmg_type, &eqpmt->item_stat.damage, &eqpmt->item_stat.defence, &eqpmt->item_stat.str, &eqpmt->item_stat.agi, &eqpmt->item_stat.end, &eqpmt->item_stat.luck, &eqpmt->item_stat.intel,
                    &eqpmt->price, &eqpmt->poids, eqpmt->desc, &elm->item_inv->quantity);
                printf("Équipement - ID: %d, Nom: %s, Type: %d, Type de dégâts: %d, Dégâts: %d, Défense: %d, Force: %d, Agilité: %d, Endurance: %d, Chance: %d, Intelligence: %d, Prix: %d, Poids: %d, Description: %s, Quantité: %d\n",
                    eqpmt->id, eqpmt->name, eqpmt->type, eqpmt->dmg_type, eqpmt->item_stat.damage, eqpmt->item_stat.defence, eqpmt->item_stat.str, eqpmt->item_stat.agi, eqpmt->item_stat.end, eqpmt->item_stat.luck, eqpmt->item_stat.intel,
                    eqpmt->price, eqpmt->poids, eqpmt->desc, elm->item_inv->quantity);
                // Ajouter l'objet équipement à l'inventaire du personnage
                break;
            case CONSUM:
                conso = malloc(sizeof(item_conso));
                fscanf(fp, "Consommable - ID: %d, Nom: %[^\n], Poids: %d, Prix: %d, HP: %d, MP: %d, Exp: %d, Disponible: %d, Description: %[^\n], Quantité: %d%*c",
                    &conso->id, conso->name, &conso->poids, &conso->price, &conso->hp, &conso->mp, &conso->exp, &conso->available, conso->desc, &elm->item_inv->quantity);
                printf("Consommable - ID: %d, Nom: %s, Poids: %d, Prix: %d, HP: %d, MP: %d, Exp: %d, Disponible: %d, Description: %s, Quantité: %d\n",
                    conso->id, conso->name, conso->poids, conso->price, conso->hp, conso->mp, conso->exp, conso->available, conso->desc, elm->item_inv->quantity);
                // Ajouter l'objet consommable à l'inventaire du personnage
                break;
            case MODIF:
                break;
        }
    }

    weight_calc((*p)->inventory);
    

    fclose(fp);
    return 1;
}







int export(const perso *p) {
    system("rm inv.txt");
    if (p == NULL) {
        printf("Erreur: Le personnage est NULL.\n");
        return 0;
    }

    FILE *fp = fopen("inv.txt", "w");
    if (!fp) {
        printf("Erreur: Impossible d'ouvrir ou de créer le fichier.\n");
        return 0;
    }

    int id[7], nb_item = p->inventory->nb_item;
    item_t *elm = p->inventory->head;
    item_eqpmt *eqpmt;
    item_ress *ress;
    item_conso *conso;

    /* Enregistrement des données du personnage */
    fprintf(fp, "Nom du personnage: %s\n", p->name);
    fprintf(fp, "Statistiques: Intel:%d, Str:%d, Luck:%d, Agi:%d, End:%d\n", p->stat->intel, p->stat->str, p->stat->luck, p->stat->agi, p->stat->end);
    fprintf(fp, "HP: %d/%d, MP: %d/%d, XP: %d/%d, Level: %d\n", p->hp, p->hp_max, p->mp, p->mp_max, p->xp, p->xp_max, p->level);
    fprintf(fp, "Poids maximal supporté: %d, Argent: %d\n", p->weight_max, p->money);
    fprintf(fp, "Pos x: %d, y: %d\n", p->x, p->y);
    fprintf(fp, "Map x: %d, y: %d\n", p->map_x, p->map_y);
    /* Enregistrement des équipements équipés */
    fprintf(fp, "Équipements équipés:\n");
    for (int i = 0; i < 7; i++) {
        id[i] = -1;
        if (p->eqpmt[i]) 
            id[i] = p->eqpmt[i]->id;
        fprintf(fp, "Emplacement %d: ID de l'équipement: %d\n", i+1, id[i]);
    }

    /* Enregistrement de l'inventaire */
    fprintf(fp, "Nombre d'objets dans l'inventaire: %d\n", nb_item);
    fprintf(fp, "Inventaire:\n");
    for (int i = 0; i < nb_item; i++) {
        switch (elm->item_inv->type) {
            case RESSOURCE: // id,name,price,poids,desc,quantity
                ress = elm->item_inv->item_u->ress;
                fprintf(fp, "Ressource - ID: %d, Nom: %s, Prix: %d, Poids: %d, Description: %s, Quantité: %d\n", 
                        ress->id, ress->name, ress->price, ress->poids, ress->desc, elm->item_inv->quantity);
                break;
            case EQPMT: // id,name,type,dmg_type,item_stat,price,poids,desc,quantity
                eqpmt = elm->item_inv->item_u->eqpmt;
                fprintf(fp, "Équipement - ID: %d, Nom: %s, Type: %d, Type de dégâts: %d, Dégâts: %d, Défense: %d, Force: %d, Agilité: %d, Endurance: %d, Chance: %d, Intelligence: %d, Prix: %d, Poids: %d, Description: %s, Quantité: %d\n",
                        eqpmt->id, eqpmt->name, eqpmt->type, eqpmt->dmg_type, eqpmt->item_stat.damage, eqpmt->item_stat.defence, eqpmt->item_stat.str, eqpmt->item_stat.agi, eqpmt->item_stat.end, eqpmt->item_stat.luck, eqpmt->item_stat.intel,
                        eqpmt->price, eqpmt->poids, eqpmt->desc, elm->item_inv->quantity);
                break;
            case CONSUM: // id,name,poids,price,hp,mp,exp,available,desc,quantity
                conso = elm->item_inv->item_u->conso;
                fprintf(fp, "Consommable - ID: %d, Nom: %s, Poids: %d, Prix: %d, HP: %d, MP: %d, Exp: %d, Disponible: %d, Description: %s, Quantité: %d\n",
                        conso->id, conso->name, conso->poids, conso->price, conso->hp, conso->mp, conso->exp, conso->available, conso->desc, elm->item_inv->quantity);
                break;
            case MODIF:
                break;
        }
        elm = elm->suiv;
    }
    

    fclose(fp);
    return 1;
}

int erase_save() {
    system("rm inv.txt");
    return 1;
}