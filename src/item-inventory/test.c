#include "../../include/item-inventory/main.h"
#include <assert.h>

int main(){

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        return -1;
    }

    // Création de la fenêtre
    window = SDL_CreateWindow("SDL Image", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Erreur lors de la création de la fenêtre : %s\n", SDL_GetError());
        return -1;
    }

    // Création du renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Erreur lors de la création du renderer : %s\n", SDL_GetError());
        return -1;
    }

    // Initialisation de SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erreur lors de l'initialisation de SDL_image : %s\n", IMG_GetError());
        return -1;
    }
    /**
     * Test for the item creation
     * Test 1: Verify the item type
     * Test 2: Verify the item id
     * Test 3: Verify the item name
    */
    item_t *item ;
    item = eqpmt_creator(1,"epee", WEAPON, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "une epee",1);
    assert(item->item_inv->type == EQPMT);
    assert(item->item_inv->item_u->eqpmt->id == 1);
    assert(strcmp(item->item_inv->item_u->eqpmt->name, "epee") == 0);

    /**
     * Test for the item creation
     * Test 1: Verify the damage type
     * Test 2: Verify the agility
     * Test 3: Verify the item name
    */
    item_t *item2 ;
    item2 = eqpmt_creator(2,"Casque", HEAD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un casque",1);
    assert(item2->item_inv->item_u->eqpmt->dmg_type == PHYSICAL);
    assert(item2->item_inv->item_u->eqpmt->item_stat.agi == 10);
    assert(strcmp(item2->item_inv->item_u->eqpmt->name, "epee") != 0);

    /**
     * Test for the item creation
     * Test 1: Verify the item type
     * Test 2: Verify the item id
     * Test 3: Verify the item description
    */
    item_t *item3 ;
    item3 = eqpmt_creator(3,"Bouclier", SHIELD, PHYSICAL, 10, 10, 10, 10, 10, 10, 10, 10, 10, "un bouclier",1);
    assert(item3->item_inv->type == EQPMT);
    assert(!(item3->item_inv->item_u->eqpmt->id == 1));
    assert(strcmp(item3->item_inv->item_u->eqpmt->desc, "un bouclier") == 0);

    /**
     * Test for the item creation
     * Test: Verify the item type
    */
    item_t *ress;
    ress = ress_creator(1,"ressource",10,10,"Test",1);
    assert(ress->item_inv->type == RESSOURCE);

    /**
     * Test for the quest creation
     * Test 1: Verify the quest name
     * Test 2: Verify the quest status
    */
    quest_t *q;
    q=quest_create("Un pas a la fois","Tuer 10 Monstres",1,NOT_STARTED,100,10,item,1,ress);
    assert(strcmp(q->name, "Un pas a la fois") == 0);
    assert(q->status == NOT_STARTED);

    /**
     * Test for the perso creation
     * Test : Verify the perso name
    */
    perso *p = malloc(sizeof(perso));
    init_perso(p,"toto", 10, 10,10, 10, 10, 0, 0, UP, &renderer);
    assert(strcmp(p->name, "toto") == 0);
    
    /**
     * Test Taking item
     * Test 1: Verify the item is in the inventory
     * Test 2: Verify the item is in the inventory with the right quantity
    */
    take_item(p, ress);
    assert(in_inventory(p, 1, RESSOURCE) >= 1);
    take_item(p, ress);
    assert(in_inventory(p, 1, RESSOURCE) == 2);

    /**
     * Test Accepting quest
     * Test 1: Verify the quest is in the perso quest list
     * Test 2: Verify the quest status
     * Test 3: Verify the perso xp
    */
    accept_quest(p,q);
    assert(p->nb_quest == 1);
    assert(p->quest[0]->status == ON_GOING);
    accept_quest(p,q);
    assert(p->xp == 100);

    printf("All tests passed\n");

    free(item->item_inv->item_u->eqpmt->desc);
    free(item->item_inv->item_u->eqpmt->name);
    free(item->item_inv->item_u->eqpmt);
    free(item->item_inv->item_u);
    free(item->item_inv);
    free(item);

    free(item2->item_inv->item_u->eqpmt->desc);
    free(item2->item_inv->item_u->eqpmt->name);
    free(item2->item_inv->item_u->eqpmt);
    free(item2->item_inv->item_u);
    free(item2->item_inv);
    free(item2);

    free(item3->item_inv->item_u->eqpmt->desc);
    free(item3->item_inv->item_u->eqpmt->name);
    free(item3->item_inv->item_u->eqpmt);
    free(item3->item_inv->item_u);
    free(item3->item_inv);
    free(item3);

    free(ress->item_inv->item_u->ress->desc);
    free(ress->item_inv->item_u->ress->name);
    free(ress->item_inv->item_u->ress);
    free(ress->item_inv->item_u);
    free(ress->item_inv);
    free(ress);
    
    destroy_quest(&q);
    destroy_perso(&p);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}
