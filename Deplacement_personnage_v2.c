
#include "../fichiers_h/Deplacement_personnage2.h"
void HandleEvent(SDL_Event  event,SDL_Renderer *render, personnage_t * perso,SDL_bool *run){
    switch(event.type)
            {  
                case SDL_QUIT:
                    *run = SDL_FALSE;
                    break;
 
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            *run = SDL_FALSE;
                                break;
                        
                        case SDLK_UP:
                            Mouvement(perso, HAUT, render);
                            break;

                        case SDLK_RIGHT:
                            Mouvement(perso, DROITE, render);
                            
                            break;
                        case SDLK_LEFT:
                            Mouvement(perso, GAUCHE, render);
                            
                            break;
 
                        default:
                            break;
                    }
 
                default:
                    break;
 
            } 
}





personnage_t * creation_personnage(SDL_Renderer * render){
    personnage_t *perso = malloc(sizeof(personnage_t));
    SDL_Surface * Surface =IMG_Load("images/1gars_img"); 
    if(Surface == NULL) 
        printf("Erreur lors du chargement de l'image : %s\n",SDL_GetError());

    perso->Texture = SDL_CreateTextureFromSurface(render,Surface);
    
    if(perso->Texture == NULL) 
        printf("Erreur lors du chargement de l'image : %s\n",SDL_GetError());
    
    
    SDL_FreeSurface(Surface);
    
    
    
    perso->Dir_Gauche = malloc(sizeof(SDL_Rect)*NB_FRAME_PERSO);
    for(int i = 0; i < NB_FRAME_PERSO;i++){

        perso->Dir_Gauche[i].y = FRAME_GAUCHE * TAILLE_SPRITE;                  /*Va à la colonne FRAME_GAUCHE*/
        perso->Dir_Gauche[i].x = i * TAILLE_SPRITE;             /*Récupère les différentes frames*/
        perso->Dir_Gauche[i].w = TAILLE_SPRITE;                 /*Taille du perso*/
        perso->Dir_Gauche[i].h = TAILLE_SPRITE;                 /*Taille du perso*/
        SDL_Log("free de la surface du perso %d",i);
    }
    perso->Dir_Droite = malloc(sizeof(SDL_Rect )*NB_FRAME_PERSO);
    
    for(int i = 0; i < NB_FRAME_PERSO;i++){

        perso->Dir_Droite[i].x = i * TAILLE_SPRITE;             /*Récupère les différentes frames*/
        perso->Dir_Droite[i].y = FRAME_DROITE * TAILLE_SPRITE;                  /*Va à la colonne FRAME_DROITE*/
        perso->Dir_Droite[i].w = TAILLE_SPRITE;                 /*Taille du perso*/
        perso->Dir_Droite[i].h = TAILLE_SPRITE;                 /*Taille du perso*/
        SDL_Log("free de la surface du perso %d",i);
    }

    perso->etat_anim = 0;
    perso->position_actuelle = DROITE;
    perso->position.x = 10;
    perso->position.y = 10;
    perso->position.w = TAILLE_SPRITE;
    perso->position.h = TAILLE_SPRITE;

    int etat = SDL_RenderCopy(render, perso->Texture, &(perso->Dir_Droite[ perso->etat_anim ]), &(perso->position));    
    if(etat != 0)
        SDL_Log("Erreur lors de l'affichage à l'écran");
    SDL_RenderPresent(render);
    return perso;
}

void destructionPersonnage(personnage_t ** perso){
    free((*perso)->Dir_Droite); (*perso)->Dir_Droite = NULL;
    free((*perso)->Dir_Gauche); (*perso)->Dir_Gauche = NULL;
    free(*perso);   (*perso) = NULL;
}
 
int gestionPersonnage(SDL_Renderer *render)
{  
 
    personnage_t * perso = NULL;
    perso = creation_personnage(render);
    if(perso == NULL){
        SDL_Log("Création du personnage impossible\n");
        exit(EXIT_FAILURE);
    }
/*-------------------------------------*/
/*------------ Boucle infini ----------*/
/*-------------------------------------*/
    SDL_bool run = SDL_TRUE;
    while(run)
    {  
        SDL_Event event;
        
        while(SDL_PollEvent(&event))
        {
            HandleEvent(event,render,perso,&run);
        }
 
 
    }
    SDL_DestroyRenderer(render);
    SDL_Quit();
    exit(EXIT_FAILURE);
}
    
void Mouvement(personnage_t *perso,int Direction, SDL_Renderer *render)
{
    SDL_Log("Entrée fonction Mouvement");
    switch(Direction)
    {  
        int etat;
        case DROITE:
            perso->position_actuelle = DROITE;
            perso->etat_anim = (1 + perso->etat_anim) % NB_FRAME_PERSO ;
            perso->position.x += DEPLACEMENT_PIXEL_PERSO;
            break;
 
        case GAUCHE:
            perso->position_actuelle = GAUCHE;
            perso->etat_anim = (1 + perso->etat_anim) % NB_FRAME_PERSO ;
            perso->position.x -= DEPLACEMENT_PIXEL_PERSO;
            break;

             
            break;
 
        default:
            break;
    }
 
 
}



int ratio(){
    SDL_Window* fenetre;
    SDL_Renderer* renderer;//Déclaration du renderer

if(SDL_VideoInit(NULL) < 0) // Initialisation de la SDL
{
    printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
    return EXIT_FAILURE;
}

// Création de la fenêtre :
fenetre = SDL_CreateWindow("Une fenetre SDL" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1920 , 1080 , SDL_WINDOW_RESIZABLE);
if(fenetre == NULL) // Gestion des erreurs
{
    printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
    return EXIT_FAILURE;
}

renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer

if(renderer == NULL)//gestion des erreurs
{
    printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
    return EXIT_FAILURE;
}
while(1)
    gestionPersonnage(renderer);


// Destruction du renderer et de la fenêtre :
SDL_DestroyRenderer(renderer); 
SDL_DestroyWindow(fenetre);
SDL_Quit(); // On quitte la SDL



}