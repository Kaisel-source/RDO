#include "../../include/build/map_build.h"

int build_board(int (*board)[24][24],int value,int x,int y){
    printf("%d\n",(*board)[y][x]);
    (*board)[y][x] = value;
    return 0;
}

int pose_block(int (*board)[24][24],int key,int x,int y){
    int id=key-SDLK_0;
    printf("%d\n",id);
    switch (key)
    {
    case SDLK_0:
        build_board(board,GRASS,x,y);
        break;
    case SDLK_1:
        build_board(board,STONE,x,y);
        break;
    case SDLK_2:
        build_board(board,BUSH,x,y);
        break;
    case SDLK_3:
        build_board(board,CRYSTALL,x,y);
        break;
    case SDLK_4:
        build_board(board,CACTUS,x,y);
        break;
    case SDLK_5:
        build_board(board,WATER,x,y);
        break;
    case SDLK_6:
        build_board(board,DOOR_C,x,y);
        break;
    case SDLK_7:
        build_board(board,TREE,x,y);
        break;
    case SDLK_8:
        build_board(board,TILES,x,y);
        break;
    case SDLK_9:
        build_board(board,SORTIE,x,y);
        break;
    
    default:
        break;
    }
    
    return 0;
}