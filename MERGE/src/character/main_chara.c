#include "../../include/common/common.h"

#include <string.h> // Pour utiliser strcpy

void init_perso(perso *p, const char *name, int end, int agi, int str, int luck, int intel, int x, int y, direction_t direction, SDL_Renderer **render) {
    if (p == NULL || name == NULL || render == NULL || *render == NULL) {
        // Gestion des pointeurs nuls
        return;
    }

    // Allocation de mémoire pour le nom du personnage
    p->name = malloc(sizeof(char) * (strlen(name) + 1)); // Ajout de 1 pour le caractère nul
    if (p->name == NULL) {
        // Gestion de l'échec de l'allocation de mémoire
        return;
    }
    strcpy(p->name, name);

    // Allocation de mémoire pour les statistiques du personnage
    p->stat = malloc(sizeof(stat_s));
    if (p->stat == NULL) {
        // Gestion de l'échec de l'allocation de mémoire
        free(p->name); // Libérer la mémoire allouée précédemment
        return;
    }
    // Initialisation des statistiques du personnage
    p->stat->intel = intel;
    p->stat->str = str;
    p->stat->luck = luck;
    p->stat->agi = agi;
    p->stat->end = end;
    p->stat->available = 0;

    // Initialisation des autres attributs du personnage
    p->hp_max = p->stat->end * 10;
    p->mp_max = p->stat->intel * 10;
    p->hp = p->hp_max;
    p->mp = p->mp_max;
    p->level = 1;
    p->xp = 0;
    p->xp_max = 100 * p->level; // Initialisation de xp_max
    p->weight_max = p->stat->str * 10;

    // Initialisation de p->inventory avant d'utiliser ses membres
    p->inventory = create_inventory(); // Supposons que create_inventory() retourne un pointeur valide

    // Initialisation du poids de l'inventaire
    p->inventory->weight = 0;

    p->money = 100;
    p->nb_quest = 0;
    for (int i = 0; i < NB_MAX_QUEST; i++) {
        p->quest[i] = NULL;
    }

    for(int i=0;i<7;i++){
        p->eqpmt[i]=NULL;
    }
    init_personnage_render(p, x, y, direction, render);
}


void init_personnage_render(perso *p,int x,int y,direction_t direction,SDL_Renderer **render){
    
    
    SDL_Surface *Surface = IMG_Load("data/image/perso.png"); 
    if (Surface == NULL) {
        printf("Erreur lors du chargement de l'image : %s\n", SDL_GetError());
        return ; // Retourner NULL en cas d'échec du chargement de l'image
    }
    
    p->Texture = SDL_CreateTextureFromSurface(*render, Surface);
    if (p->Texture == NULL) {
        printf("Erreur lors de la création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(Surface); // Libérer la surface si la création de la texture échoue
        free(p); // Libérer la mémoire allouée pour le personnage
        return ;
    }

    SDL_FreeSurface(Surface);
    
    p->x = x;
    p->y = y;
    p->direction = direction;
    p->state = IDLE;
    p->sprite_move = malloc(sizeof(img_t *)*4);
    for(int i=0;i<4;i++){
        p->sprite_move[i] = malloc(sizeof(img_t *));
        p->sprite_move[i]->texture = malloc(sizeof(SDL_Rect *)*9);  
        p->sprite_move[i]->num_ref=0;
        p->sprite_move[i]->nb_sprite = 9;
    }
    direction_t dir[4] = {FRAME_HAUT,FRAME_BAS,FRAME_GAUCHE,FRAME_DROITE};
    for(int ligne=0;ligne<4;ligne++){
        for(int colonne = 0; colonne < 9;colonne++){
            p->sprite_move[ligne]->texture[colonne] = malloc(sizeof(SDL_Rect));
            p->sprite_move[ligne]->texture[colonne]->y = dir[ligne] * TAILLE_SPRITE;
            p->sprite_move[ligne]->texture[colonne]->x = colonne * TAILLE_SPRITE;             /*Récupère les différentes frames*/
            p->sprite_move[ligne]->texture[colonne]->w = TAILLE_SPRITE;                 /*Taille du perso*/
            p->sprite_move[ligne]->texture[colonne]->h = TAILLE_SPRITE;              /*Taille du perso*/
        }
    }
    p->position = malloc(sizeof(SDL_Rect));
    p->position->y = (p->y * (WINDOW_HEIGHT / BOARD_SIZE_Y)) % WINDOW_HEIGHT;
    p->position->x = (p->x * (WINDOW_WIDTH / BOARD_SIZE_X)) % WINDOW_WIDTH;
    p->position->w = CELL_WIDTH;
    p->position->h = CELL_HEIGHT;

    SDL_RenderCopy(*render, p->Texture, p->sprite_move[0]->texture[0], p->position);
    SDL_RenderPresent(*render);
    
}


void take_item(perso *p,item_t *item){
    item_t *tmp = p->inventory->head;
    int id=item->item_inv->type==EQPMT?item->item_inv->item_u->eqpmt->id:item->item_inv->item_u->ress->id;
    display_common(*item->item_inv);
    if(in_inventory(p,id,item->item_inv->type)>0){
        printf("item deja dans l'inventaire\n\n");
        
        tmp->item_inv->quantity++;
    }
    else{
        printf("Ajout de l'item\n\n");
        add(item,p->inventory);

    }
}



int in_inventory(perso *p, int id, type_it type){
    item_t *tmp = p->inventory->head;
    printf("Type:%d\n",type);
    for(int i=0;i<p->inventory->nb_item;i++){
        display_common(*tmp->item_inv);
        printf("Type:%d\n",tmp->item_inv->type);
        if(type==RESSOURCE && tmp->item_inv->type==RESSOURCE){
            printf("%d == %d\n",tmp->item_inv->item_u->ress->id,id);
            if(tmp->item_inv->item_u->ress->id == id)
                return tmp->item_inv->quantity;
            tmp = tmp->suiv;
        }
        else if (type==EQPMT && tmp->item_inv->type==EQPMT) {
            printf("%d == %d\n",tmp->item_inv->item_u->eqpmt->id,id);
            if(tmp->item_inv->item_u->eqpmt->id == id)
                return tmp->item_inv->quantity;
            tmp = tmp->suiv;
        }
        else if (type==CONSUM && tmp->item_inv->type==CONSUM){
            printf("%d == %d\n",tmp->item_inv->item_u->conso->id,id);
            if(tmp->item_inv->item_u->conso->id == id)
                return tmp->item_inv->quantity;
            tmp = tmp->suiv;
        }
        else tmp = tmp->suiv;
    }
    return 0;
}

void display_perso(const perso p){
    printf("Nom: %s\n", p.name);
    printf("Niveau: %d\n\n", p.level);
    printf("XP: %d / %d\n", p.xp,p.xp_max);
    printf("HP: %d / %d\n", p.hp, p.hp_max);
    printf("MP: %d / %d\n", p.mp, p.mp_max);
    printf("Poids max: %d\n\n", p.weight_max);
    printf("Argent: %d\n\n", p.money);
    printf("Statistiques:\n");
    printf("Endurance: %d\n", p.stat->end);
    printf("Agilité: %d\n", p.stat->agi);
    printf("Force: %d\n", p.stat->str);
    printf("Chance: %d\n", p.stat->luck);
    printf("Intelligence: %d\n\n", p.stat->intel);
    display_equipement(p);
    printf("\n\nInventaire:\n");
    display_inventory(p.inventory);
    printf("\n\nQuêtes:\n");
    quest_list_display(p.quest);
}

void display_equipement(const perso p){
    printf("Equipement:\n");
    for(int i=0;i<7;i++){
        if(p.eqpmt[i]!=NULL){
            display_eqpmt(*p.eqpmt[i]);
        }
        else{
            printf("Emplacement vide\n");
        
        }
    }
}

void destroy_perso(perso **p){
    if(*p!=NULL){
        free((*p)->name);
        (*p)->name=NULL;
        free((*p)->stat);
        (*p)->stat=NULL;
        destroy_stockage(&(*p)->inventory);
        //quest_list_destructor(&(*p)->quest);
        free_personnage_render(p);
        free(*p);

    }
}
int free_personnage_render(perso **perso){
    for(int i=0;i<4;i++){
        for(int j=0;j<9;j++){
            free((*perso)->sprite_move[i]->texture[j]);
        }
        free((*perso)->sprite_move[i]->texture);
        free((*perso)->sprite_move[i]);
    }
    free((*perso)->sprite_move);
    free((*perso)->position);
    return 0;
}

void level_up(perso *p){
    while(p->xp>=p->xp_max){
        p->level++;
        p->xp_max*=2;
        p->xp=p->xp-p->xp_max;
        p->stat->available+=5;
    }
}