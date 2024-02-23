#include <stdio.h>
#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"

// Fonction de chargement de texture
SDL_Texture* loadTexture(const char* filename, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        fprintf(stderr, "Erreur de chargement de l'image (%s)\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        fprintf(stderr, "Erreur de création de la texture (%s)\n", SDL_GetError());
        return NULL;
    }

    return texture;
}

int main(int argc, char** argv){

/* ----------------------------------------------------- Initialisation ----------------------------------------------------- */

	int i,x=0, k, w , h, j=0; // Variable compteurs, axes
    int lastKeyPressed, lkpshift, lkpjump, lastDirection = 1; // Rappel de la dernière frappe, utilisée pour les systèmes de doubles frappes

/* ----------------------------------------------------- Création et gestion de la fenêtre SDL ----------------------------------------------------- */

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    } else {
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

        if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
            fprintf(stderr, "Erreur Init: %s\n", IMG_GetError());#include "mat.h"
            SDL_Renderer *pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

            if (pRenderer) {
                SDL_Texture* Walktest = NULL;
                SDL_Texture* background=NULL;

                Walktest = loadTexture("../img/test(1).png", pRenderer);
                background = loadTexture("../img/Wallhaven.png", pRenderer);
                SDL_RenderPresent(pRenderer);

                if (Walktest != NULL && background != NULL) {
                        SDL_Rect destBackground = {0, 0, 1280, 720}; // Position et taille de l'image de fond
                        SDL_Rect destWalktest = {608, 328, 128, 128}; // Position et taille du personnage

                        /*création et initialisation d'un tableau selectionnant tout les sprites de l'animation de marche*/

                        SDL_Rect src[6] = { 0,0, 32,32};
                        for (i=0;i<6;i++){
                            src[i].x=x;
                            src[i].y=0;
                            src[i].w=32;
                            src[i].h=32;
                            x+=32;
                        }
                        x=0;
                        SDL_RenderCopy(pRenderer, background,0,&destBackground);
                        SDL_RenderCopy(pRenderer,Walktest,src+0,&destWalktest); //copie du personnage dans sa position de base
                        SDL_RenderPresent(pRenderer); // Affichage

                        SDL_Event event;
                        SDL_Event event2;
                        
                        //declaration de quit etant la variable booleen qui met fin a la boucle
                        //declaration keyPressed pour gerer si une touche est maintenu ou relacher
                        int quit = 0, KeyIsPressed=0;
                        
                        //boucle du jeux

/* ----------------------------------------------------- Detection des frappes ----------------------------------------------------- */

                        while (!quit) {
                            
                            // recuperation du clique sur le bouton de fermeture et met fin a la boucle
                            while (SDL_PollEvent(&event) != 0) {
                                if (event.type == SDL_QUIT) {
                                    quit = 1;
                                }


                                if (event.type == SDL_KEYDOWN) {
                                    
                                    /*------------------------------ Run -------------------------------*/

                                    if (event.key.keysym.sym == SDLK_d) {
                                        if (KeyIsPressed == 0 || KeyIsPressed == -1) {
                                            KeyIsPressed = 1;
                                            lastKeyPressed = 1;
                                            lastDirection = 1;
                                        }  
                                    }
                                    else if (event.key.keysym.sym == SDLK_q) {
                                        if (KeyIsPressed == 0 || KeyIsPressed == -1) {
                                            KeyIsPressed = 2;
                                            lastKeyPressed = 2;
                                            lastDirection = 2;
                                        }  
                                    }
                                
                                // Récuperation des touche relachées changement de KeyIsPressed
                                else if (event.type == SDL_KEYUP) {
                                    if (event.key.keysym.sym == SDLK_q){
                                        KeyIsPressed = 0;
                                    }
                                    else if(event.key.keysym.sym == SDLK_d){
                                        KeyIsPressed = -1;
                                        lastKeyPressed = -1;
                                    }
                                    else if(lkpshift == 1){
                                        KeyIsPressed = 0;
                                        j = -1;
                                    }
                                    else if(lkpshift == 2){
                                        KeyIsPressed = -1;
                                        j = -1;
                                    }
                                    else if(lkpjump == 1){
                                        KeyIsPressed = 0;
                                    }
                                    else if(lkpjump == 2){
                                        KeyIsPressed = -1;
                                    }
                                }
                                
                            }
                            
                            

                            //regarde la valeur KeyIsPressed et effectue l'animation de marche change le sens selon le bouton utliser
                            //et si relacher le personnage revient a ça pose d ebase toujours dans le sens du bouton utiliser dernièrement

/* ----------------------------------------------------- Animation ----------------------------------------------------- */
                            /*------------------------------ Run -------------------------------*/

                            if (KeyIsPressed==1) {
                                destWalktest.x+=10;
                                SDL_RenderClear(pRenderer);
                                SDL_RenderCopy(pRenderer,Walktest,src+((++i)%11),&destWalktest);
                                SDL_Delay(50);
                                SDL_RenderPresent(pRenderer); // Affichage run à droite
                            }
                            else if(KeyIsPressed==2){
                                destWalktest.x-=10;
                                SDL_RenderClear(pRenderer);
                                SDL_RenderCopyEx(pRenderer,Walktest,src+((++i)%11),&destWalktest, 0, NULL, SDL_FLIP_HORIZONTAL);
                                SDL_Delay(50);
                                SDL_RenderPresent(pRenderer); // Affichage run à gauche
                            }

                            /*------------------------------ Statique -------------------------------*/

                            else if(KeyIsPressed==0 && lastDirection == 1){
                                SDL_RenderClear(pRenderer);
                                SDL_RenderCopy(pRenderer,Walktest,src+0,&destWalktest);
                                SDL_RenderPresent(pRenderer); // Affichage statique
                            }
                            else if(KeyIsPressed==0 && lastDirection == 2){
                                SDL_RenderClear(pRenderer);
                                SDL_RenderCopyEx(pRenderer,Walktest,src+0,&destWalktest, 0, NULL, SDL_FLIP_HORIZONTAL);
                                SDL_RenderPresent(pRenderer); // Affichage statique
                            }


                            }
                            
                        }

                        SDL_DestroyTexture(Walktest);
                        SDL_DestroyTexture(background);
                } else {
                    fprintf(stdout, "Échec de création de la texture (%s)\n", SDL_GetError());
                }

                SDL_DestroyRenderer(pRenderer);
            } else {
                fprintf(stdout, "Échec de création du renderer (%s)\n", SDL_GetError());
            }

            SDL_Delay(1000);
            SDL_DestroyWindow(pWindow);
        } else {
            fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
        }
    }

    SDL_Quit();
    IMG_Quit();

    return 0;
}
