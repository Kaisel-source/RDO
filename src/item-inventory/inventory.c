#include "../../include/item-inventory/common.h"

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
        list->queue = NULL;
        list->current = list->head;
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
    if (empty_inventory(list))
    {
        add_first(item, list);
    }
    else
    {
        add_last(item, list);
    }
    list->nb_item++;
    weight_calc(list);
}
/*
void add_current(item_t *item, item_list *list)
{
    printf("1\n");
    if (empty_inventory(list))
    {
        printf("2\n");
        add_first(item, list);
    }
    else{
        if(list->current==list->queue){
            printf("3\n");
            add_last(item,list);
        }
        else if(list->current==list->head){
            printf("4\n");
            add_first(item,list);
        }
        else{
            printf("5\n");
            item->prec = list->current;
            printf("5-1\n");
            item->suiv = list->current->suiv;
            printf("5-2\n");
            list->current->suiv = item;
            
            printf("5-3\n");
            printf("%p\n",list->current->suiv->prec);
            printf("%p\n",list->current);
            list->current->suiv->suiv->prec = item;
        }
        
        
    }
    list->nb_item++;
    weight_calc(list);
}
*/

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
    printf("Poids Total : %d\n", list->weight);
}

void destroy_current(item_list *list)
{
    item_t *item = list->current;
    if (item == list->head)
    {
        list->head = item->suiv;
        list->head->prec = NULL;
        list->queue->suiv = NULL;
        list->current = list->head;
        destroy_common(&item,&list->nb_item);
    }
    else if (item == list->queue)
    {
        list->queue = item->prec;
        list->queue->suiv = NULL;
        list->head->prec = NULL;
        list->current = list->queue;
        destroy_common(&item,&list->nb_item);
    }
    else
    {
        item->prec->suiv = item->suiv;
        item->suiv->prec = item->prec;
        list->current = item->prec;
       destroy_common(&item,&list->nb_item);
    }
    if (list->nb_item == 0)
    {
        destroy_inventory(&list);
    }
}

void destroy_inventory(item_list **list)
{
    item_t *item = (*list)->head;
    item_t *suiv;
    printf("Nombre d'item : %d\n",(*list)->nb_item);
    for(int i=0;i<(*list)->nb_item;i++)
    {
        
        suiv = item->suiv;
        destroy_common(&item,&(*list)->nb_item);
        item = suiv;
    }
    (*list)->head = NULL;
    (*list)->queue = NULL;
    (*list)->current = NULL;
    free(*list);
    *list = NULL;
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