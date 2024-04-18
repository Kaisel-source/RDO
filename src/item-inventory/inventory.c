#include "../../include/common/common.h"

item_list *create_inventory()
{
    item_list *list = malloc(sizeof(item_list));
    list->head = NULL;
    list->queue = NULL;
    list->current = NULL;
    list->nb_item = 0;
    return list;
}


int empty_inventory(item_list *list)
{
    return (list->head == NULL);
}


void add_first(item_t *item, item_list *list)
{

    if (empty_inventory(list))
    {
        list->head = item;
        printf("1\n");
        list->queue = NULL;
        printf("2\n");
        list->current = list->head;
        printf("3\n");
    }
    else
    {
        item->prec = NULL;
        item->suiv = list->head;
        list->head = item;
    }
}


void add(item_t *item, item_list *list)
{  
    printf("Ajout d'un item\n");
    empty_inventory(list);
    if (empty_inventory(list))
    {
        printf("Ajout en tete\n");
        add_first(item, list);
    }
    else
    {
        printf("Ajout en queue\n");
        add_last(item, list);
    }
    list->nb_item++;
    printf("Poids avant : %d\n", list->weight);
    weight_calc(list);
}


item_t *find_queue(item_list *list)
{
    item_t *item = list->head;
    for(int i=0;i<list->nb_item-1;i++)
    {
        item = item->suiv;
    }
    return item;
}


void add_last(item_t *item, item_list *list)
{
    item_t *tmp;
    if (empty_inventory(list))
    {
        add_first(item, list);
    }
    else
    {
        tmp=find_queue(list);
        item->prec=tmp;
        item->suiv = NULL;
        tmp->suiv = item;
        list->queue = item;
    }

}


void display_inventory(const item_list *list)
{
    item_t *item = list->head;
    for(int i=0;i<list->nb_item;i++)
    {   
        printf("N: %d\n",list->nb_item);
        printf("Item: %p\n", item);
        display_common(*item->item_inv);
        item = item->suiv;
    }
    weight_calc(list);
    printf("Poids Total : %d\n", list->weight);
}


void destroy_stockage(item_list **inv)
{
    (*inv)->current=NULL;
    (*inv)->head=NULL;
    (*inv)->queue=NULL;
    free((*inv));
    (*inv) = NULL;
}


void destroy_game_stockage(item_list **inv)
{
    int nb_item = (*inv)->nb_item;
    item_t *suiv;
    (*inv)->current=(*inv)->head;
    printf("Nombre d'item : %d\n",nb_item);
    for(int i=0;i<nb_item;i++)
    {   
        suiv=(*inv)->current->suiv;
        printf("Item: %p\n", (*inv)->current);
        printf("Item->suiv: %p\n", (*inv)->current->suiv);
        printf("Destruction...\n");
        destroy_common_item_stock((*inv));
        printf("End of destruction...\n");
        (*inv)->current=suiv;
    }
    (*inv)->current=NULL;
    (*inv)->head=NULL;
    (*inv)->queue=NULL;
    free((*inv));
    (*inv) = NULL;

}


void suiv_current(item_list *list)
{
    if (list->current != NULL)
        if (list->current->suiv != NULL)
            list->current = list->current->suiv;
        else
            list->current = list->head;
    else if (empty_inventory(list) == 0)
        list->current = list->head;
    else
        printf("Erreur de parcours\n");
}


void prec_current(item_list *list)
{
    if (list->current != NULL)
    {
        printf("Prec: %p\n", list->current->prec);
        if (list->current->prec != NULL)
        {
            printf("Way: 1\n\n");
            list->current = list->current->prec;
        }
        else
        {
            printf("Way: 2\n\n");
            list->current = find_queue(list);
        }
    }
    else if (!empty_inventory(list)){
        printf("Way : Error\n\n");
        list->current = list->head;
    }
        
    else
        printf("Erreur de parcours\n");
}


void weight_calc(item_list *list)
{
    item_t *item = list->head;
    list->weight = 0;
    
    for(int i=0;i<list->nb_item;i++)
    {
        
        switch (item->item_inv->type)
        {
            case EQPMT:
                list->weight += item->item_inv->item_u->eqpmt->poids * item->item_inv->quantity;
                break;
            case RESSOURCE:
                list->weight += item->item_inv->item_u->ress->poids * item->item_inv->quantity;
                break;
            default:
                printf("Erreur de calcul de poids\n");
                break;
        }
        item = item->suiv;
    }
    printf("Poids Total : %d\n", list->weight);
}


void display_current(const item_list *list)
{
    display_common(*list->current->item_inv);
}


void display_head(const item_list *list)
{
    display_common(*list->head->item_inv);
}


void display_queue(const item_list *list)
{
    display_common(*list->queue->item_inv);
}


void erase_item(item_list *list){
    item_t *item =list->current;
    if(item->prec==NULL){
       list->head=item->suiv;
       list->current=item->suiv;
       list->current->prec=NULL;
    }
    else if(item->suiv==NULL){
       list->queue=item->prec;
       list->current=item->prec;
       list->current->suiv=NULL;
    }
    else{
        item->prec->suiv=item->suiv;
        item->suiv->prec=item->prec;
       list->current=item->suiv;
    }
   list->nb_item--;
}

void check_inventory(perso *p){
    p->inventory->current=p->inventory->head;
    for(int i=0;i<p->inventory->nb_item;i++){
        if(p->inventory->current->item_inv->quantity<=0){
            erase_item(p->inventory);
        }
        else{
            suiv_current(p->inventory);
        }
    }
    weight_calc(p->inventory);
} 