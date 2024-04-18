#ifndef STRUCT_H
#define STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "SDL2/SDL_ttf.h"
#include <math.h>
#include <unistd.h>

#define NB_MAX_QUEST 10
#define TOTAL_QUEST 10
#define TOTAL_PERS 10

#define NB_MAP_X 3
#define NB_MAP_Y 2
typedef enum eqpmt_type {
    NONE, HEAD, BODY, LEGS, FOOT, RING, WEAPON, SHIELD
} eqpmt_type;

typedef enum dmg_type {
    PHYSICAL,MAGIC,BOTH
} dmg_t;

typedef enum type_item{
    RESSOURCE,EQPMT,MODIF,CONSUM
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

typedef struct conso {
    char* name;
    int id;
    int poids;
    int price;

    int hp;
    int mp;

    int exp;
    int available;

    char *desc;
} item_conso;

typedef union item_inv{
    item_eqpmt *eqpmt;
    item_ress *ress;
    item_conso *conso;
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


/*-------------- QUETE -------------- */
typedef enum {ON_GOING, COMPLETED, NOT_STARTED} quest_status;

typedef struct quest_s{
        char *name;
        char *desc;
        int id;

        quest_status status;

        int reward_xp;
        int reward_gold;
        item_t *reward_item;

        int required_item_quant;
        item_t *required_item; //ONLY EQPMT OR RESSOURCE

}quest_t;

typedef struct quest_npc_s{
    char *accept;
    char *refuse;
    char *on_going;
    char *completed;
    quest_t *quest;
}quest_npc_t;


/*-------------- PERSO -------------- */
typedef struct img_s{
    int nb_sprite;
    int num_ref;
    SDL_Rect **texture;
}img_t;

typedef struct{
    int x;
    int y;
    int map[NB_MAP_Y][NB_MAP_X][24][24];
    char* path[NB_MAP_Y][NB_MAP_X];
}map_t;

typedef enum{
    WALK_R,
    WALK_L,
    WALK_U,
    WALK_D,
    INTERACT,
    HIDE,
    IDLE
}state_t;

typedef enum{
    DOWN,
    RIGHT,
    LEFT,
    UP
    
}direction_t;

typedef struct stat_p{
    int intel;
    int str;
    int luck;
    int agi;
    int end;

    int available; //point to spend
}stat_s;

typedef struct pers{
    char *name;

    stat_s *stat;

    int hp;
    int hp_max;

    int mp;
    int mp_max;

    int xp;
    int xp_max;

    int level;

    unsigned int weight_max;
    int money;

    item_eqpmt *eqpmt[7]; //0: head, 1: body, 2: legs, 3: foot, 4:ring , 5: weapon, 6: shield
    item_list *inventory;

    int nb_quest;
    quest_t *quest[NB_MAX_QUEST];
    //image ref
    int x;
    int y;
    direction_t direction;
    state_t state;
    SDL_Texture *Texture;
    img_t **sprite_move;
    SDL_Rect *position;
    
    int map_x;
    int map_y;
} perso;


/*-------------- NPC -------------- */

typedef struct npc_t{
    char *name;
    char *dialog;

    int money;
    item_list *inventory;

    int nb_quest;
    quest_npc_t **quest;

    direction_t direction;
    SDL_Texture *Texture;
    img_t *sprite_move;
} npc_s;


/*-------------- STRUCTURE DE JEU -------------- */

/**
 * @brief Structure pour représenter une position sur le plateau
 */
typedef struct {
    int x; /**< Coordonnée en X */
    int y; /**< Coordonnée en Y */
} pos_t;

// Structure représentant une entité
typedef struct {
    char prenom[50];
    char classe[50];
    int pv;
    int pv_max;
    int attaque;
    int alive;
    void *img; // Pointeur vers l'image de l'entité, à définir selon votre utilisation
    int equipe;
    int mouv;
    int initiative;
    int range;
} entite_t;

// Structure représentant un bouton
typedef struct {
    SDL_Rect rect;       // Rectangle définissant la position et la taille du bouton
    SDL_Texture* texture; // Texture du bouton (à générer avec SDL_CreateTextureFromSurface())
} Button;


typedef struct game_t{
    perso *main_perso;
    npc_s *npc[TOTAL_PERS];
    quest_t *quest[TOTAL_QUEST];
    int nb_quest_saved;
    int nb_pers_saved;
    item_list *item;
    map_t *map;
    SDL_Texture **area;
    SDL_Texture *TextureOut;
    SDL_Texture *TextureMonster;

}game_s;

#endif
