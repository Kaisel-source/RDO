#include "../../include/common/common.h"

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
void itoa(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0) /* record sign */
        n = -n;         /* make n positive */
    i = 0;
    do
    {                          /* generate digits in reverse order */
        s[i++] = n % 10 + '0'; /* get next digit */
    } while ((n /= 10) > 0);   /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void display_common(const inv_item_s item)
{
    switch (item.type)
    {
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

void destroy_common_item_stock(item_list *inv)
{
    item_t **item = &(inv->current);
    switch ((*item)->item_inv->type)
    {
    case EQPMT:
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

    (*item)->prec = NULL;
    (*item)->suiv = NULL;
    free(*item);
    *item = NULL;
    inv->nb_item--;
}

void use_common(perso *p)
{
    item_t *item = p->inventory->current;
    switch (item->item_inv->type)
    {
    case EQPMT:
        use_eqpmt(p, item->item_inv->item_u->eqpmt);
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

void add_n(perso *p,item_t it, int nb)
{
    item_t *item = p->inventory->head;
    if(in_inventory(p, it.item_inv->type, it.item_inv->item_u->eqpmt->id) > 0)
    {
        item->item_inv->quantity += nb;
    }
    else
    {
        take_item(p, &it);
        add_n(p, it, nb-1);
    }
    
    check_inventory(p);
}
void remove_n(perso *p,item_t it, int nb)
{
    item_t *item = p->inventory->head;
    if(in_inventory(p, it.item_inv->type, it.item_inv->item_u->eqpmt->id) >= nb)
    {
        item->item_inv->quantity -= nb;
    }
    else
    {
        printf("Erreur de suppression\n");
    }
    
    check_inventory(p);
}