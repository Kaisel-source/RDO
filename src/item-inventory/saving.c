#include "../../include/common/common.h"

/*int lireFichier(char *nomFichier, table *t){
    printf("Ouverture du fichier\n");
    FILE *fp;
    fp=fopen(nomFichier,"r");
    t->nbJoueurs=0;
    if(fp){

        printf("Lecture et initialisation des joueurs\n");

        for(int i=0;i<NB_JOUEURS && fscanf(fp,"%d;%f;%f;%f;%f;%f;%f;%f;%f;%[^\n]",&t->joueurs[i].age,&t->joueurs[i].fg,&t->joueurs[i].fga,&t->joueurs[i].p3,&t->joueurs[i].p3a,&t->joueurs[i].ft,&t->joueurs[i].fta,&t->joueurs[i].orb,&t->joueurs[i].drb,t->joueurs[i].nom);i++)
            t->nbJoueurs++;

       }
    else{
        printf("Le fichier est vide,fermeture du fichier\n");
        fclose(fp);

        return 0;
    }
    printf("Fin de l'initialisation des joueurs\n");
    fclose(fp);
    return 1;

}fscanf(fp,"%[^\n\0];",temp);*/
int import(perso *p)
{
    
    FILE *fp = fopen("inventory.csv", "r");
    int type, intel, str, luck, agi, end, nb_item;
    int id,dmg,defence,price,poids,quantity,hp,mp,exp,available,dmg_t,eqpmt_t;
    int id_equipped[7]={-1,-1,-1,-1,-1,-1,-1};
    char name[50],desc[500];
    char input[100];
    item_t *item;
    if(!fp){
        fclose(fp);
        return 0;
    }
    if (fp)
    {
        /*init SAVE*/
        printf("Import\n");
        printf("PERSO\n");
        fscanf(fp, "%s[^\n]", input );
        sscanf(input, "%s[^;];%d;%d;%d;%d;%d;", name, &intel, &str, &luck, &agi, &end);
        printf("%s;%d;%d;%d;%d;%d;\n", name, intel, str, luck, agi, end);
        printf("p1\n");
        init_perso(p, name, end, agi, str, luck, intel);
        printf("p2\n");
        fscanf(fp, "%d;%d;%d;%d;%d;%d;%d;%d;%d", &p->hp, &p->hp_max, &p->mp, &p->mp_max, &p->xp, &p->xp_max, &p->level, &p->weight_max, &p->money);
        fscanf(fp,"%d;%d;%d;%d;%d;%d;%d",&id_equipped[0],&id_equipped[1],&id_equipped[2],&id_equipped[3],&id_equipped[4],&id_equipped[5],&id_equipped[6]);
        display_perso(*p);
        fscanf(fp, "%d", &nb_item);
        p->inventory->nb_item = nb_item;
        printf("INVENTORY\n");
        for(int i=0;i<nb_item;i++){
            fscanf(fp, "%d", &type);
            switch (type){
            case RESSOURCE:
                fscanf(fp, "%d;%s[^;];%d;%d;%s[^;];%d", &id, name, &price, &poids, desc, &quantity);
                item=ress_creator(id,name,price,poids,desc,quantity);
                break;
            case EQPMT:
                fscanf(fp, "%d;%s[^;];%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%s[^;];%d", &id ,name, &eqpmt_t, &dmg_t,&dmg, &defence, &str, &agi, &end, &luck,&intel,&price,&poids, desc, &quantity);
                item=eqpmt_creator(id,name,eqpmt_t,dmg_t,dmg,defence,str,agi,end,luck,intel,price,poids,desc,quantity);
                break;
            case CONSUM:
                fscanf(fp, "%d;%s[^;];%d;%d;%d;%d;%d;%d;%s;%d", &id, name, &poids, &price, &hp, &mp, &exp, &available, desc, &quantity);
                item=conso_create(name,id,poids,price,hp,mp,exp,available,desc,quantity);
                break;
            }
            display_common(*(item->item_inv));
            take_item(p, item);
        }
    }
    fclose(fp);
    return 1;
}

int export(const perso *p){
    if (p == NULL)
    {
        return 0;
    }
    FILE *fp = fopen("inventory.csv", "w+");
    
    int id[5],nb_item=p->inventory->nb_item;
    item_t *elm = p->inventory->head;
    item_eqpmt *eqpmt;
    item_ress *ress;
    item_conso *conso;

    if (fp)
    {
        /*SAVE PERSO*/
        fprintf(fp, "%s;%d;%d;%d;%d;%d;\n", p->name, p->stat->intel, p->stat->str, p->stat->luck, p->stat->agi, p->stat->end);
        
        fprintf(fp, "%d;%d;%d;%d;%d;%d;%d;%d;%d\n", p->hp, p->hp_max, p->mp, p->mp_max, p->xp, p->xp_max, p->level, p->weight_max, p->money);
        for (int i = 0; i < 7; i++)
        {
            id[i] = -1;
            if (p->eqpmt[i]) 
                id[i] = p->eqpmt[i]->id;
            
        }
        fprintf(fp,"%d;%d;%d;%d;%d;%d;%d\n",id[0],id[1],id[2],id[3],id[4],id[5],id[6]);
        /*SAVE INVENTORY*/
        fprintf(fp, "%d\n", nb_item);
        for (int i = 0; i < nb_item; i++){
            switch (elm->item_inv->type){
                case RESSOURCE: // id,name,price,poids,desc,quantity
                    ress=elm->item_inv->item_u->ress;
                    fprintf(fp, "%d;%s;%d;%d;%s;%d\n", ress->id, ress->name, ress->price, ress->poids, ress->desc, elm->item_inv->quantity);
                    break;
                 case EQPMT: // id,name,type,dmg_type,item_stat,price,poids,desc,quantity
                    eqpmt = elm->item_inv->item_u->eqpmt;
                    fprintf(fp, "%d;%s;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%s;%d\n", eqpmt->id, eqpmt->name, eqpmt->type, eqpmt->dmg_type,\
                        eqpmt->item_stat.damage, eqpmt->item_stat.defence, eqpmt->item_stat.str, eqpmt->item_stat.agi, eqpmt->item_stat.end, eqpmt->item_stat.luck, eqpmt->item_stat.intel,\
                        eqpmt->price, eqpmt->poids, eqpmt->desc, elm->item_inv->quantity);
                    break;
                case CONSUM: // id,name,poids,price,hp,mp,exp,available,desc,quantity
                    conso = elm->item_inv->item_u->conso;
                    fprintf(fp, "%d;%s;%d;%d;%d;%d;%d;%d;%s;%d\n", conso->id, conso->name, conso->poids, conso->price, conso->hp, conso->mp, conso->exp, conso->available, conso->desc, elm->item_inv->quantity);
                    break;
                case MODIF:
                    break;
            }
            elm = elm->suiv;
        }
    }
    else
    {
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return 1;
}