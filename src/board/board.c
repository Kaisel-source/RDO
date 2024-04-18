#include "../../include/board/board.h"
int import_board(int (*board)[24][24],char *path){
    FILE *file = fopen(path,"r");
    if(file == NULL){
        for(int i=0;i<24;i++){
            for(int j=0;j<24;j++){
                (*board)[i][j] = 0;
            
            }
        }
        return -1;
    }
    for(int i=0;i<24;i++){
        for(int j=0;j<24;j++){
            fscanf(file,"%d",&(*board)[i][j]);
        }
    }
    fclose(file);
    return 0;
}

int export_board(int (*board)[24][24],char *path){
    FILE *file = fopen(path,"w");
    if(file == NULL){
        printf("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }
    for(int i=0;i<24;i++){
        for(int j=0;j<24;j++){
            fprintf(file,"%d ",(*board)[i][j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
}