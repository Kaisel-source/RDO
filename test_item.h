#include <stdio.h>
#include <stdlib.h>
/*
typedef enum eqpmt_type;
typedef enum dmg_type;
typedef enum type_item;
typedef struct stat;
typedef struct eqpmt;
typedef struct ressource;*/

typedef enum eqpmt_type {
    NONE, HEAD, BODY, LEGS, FOOT, RING, WEAPON, SHIELD
} eqpmt_type;

typedef enum dmg_type {
    PHYSICAL,MAGIC,BOTH
} dmg_t;

typedef enum type_item{
    RESSOURCE,EQPMT
} type_it;

typedef struct stat {
    int damage;
    int defence;
    int str;
    int agi;
    int end;
    int luck;
    int intel;
} stat_item;

typedef struct item_eqpmt {
    int id;
    char* name;
    eqpmt_type type;
    dmg_t dmg_type;
    stat_item item_stat;
    int price;
    int poids;
    char* desc;

} item_eqpmt;

typedef struct ressource{
    int id;
    char* name;
    int price;
    int poids;
    char* desc;

} item_ress;

typedef union item_inv{
    item_eqpmt *eqpmt;
    item_ress *ress;
}it_iv;


typedef struct inv_item{
    type_it type;
    it_iv *item_u;
}inv_item_s;



typedef struct item_s{
    inv_item_s *item_inv;
    struct item_s *prec;
    struct item_s *suiv;
}item_t;

typedef struct item_list{
    unsigned int weight;
    item_t *head;
    item_t *queue;
}item_list;




item_list * create_inventory();
int empty_inventory(item_list *list);
void add_last(item_t *item, item_list *list);
void add_first(item_t *item, item_list *list);
void display_inventory(const item_list *list);
void weight_calc(item_list *list);
void destroy_inventory(item_list *list);
void destroy_common(item_t *item);
void display_common(const inv_item_s item);


item_t* eqpmt_creator(int id, char* name, eqpmt_type type, dmg_t dmg_type, int damage, int defence, int str, int agi, int end, int luck, int intel, int price, int poids, char* desc);
void display_eqpmt(const item_eqpmt eqpmt);
char* name_eqpmt(int type);
void item_destructor(inv_item_s* item);

item_t* ress_creator(int id, char* name, int price, int poids, char* desc);
void display_ress(const item_ress ress);
void ress_destructor(inv_item_s* item);
