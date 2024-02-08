#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum eqpmt_type {
    NONE, HEAD, BODY, LEGS, FOOT, RING, WEAPON, SHIELD
} eqpmt_type;

typedef enum dmg_type {
    PHYSICAL,MAGIC,BOTH
} dmg_t;

typedef enum type_item{
    RESSOURCE,EQPMT,MODIF
} type_it;

typedef enum modif_type{
    CONSUM,PERMANENT
} modif_t;

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
    int quantity;
}inv_item_s;



typedef struct item_s{
    inv_item_s *item_inv;
    struct item_s *prec;
    struct item_s *suiv;
}item_t;

typedef struct item_list{
    unsigned int weight;
    item_t *head;
    item_t *current;
    item_t *queue;
    int nb_item;
}item_list;

#endif
