#include <string.h>
#include <stdio.h>
#include <stdlib.h>



typedef enum type_item{
    RESSOURCE,EQPMT,MODIF,CONSUM
} type_it;
void main(){
    char test[10];
    itoa(RESSOURCE, test);
    printf("%s\n", test);
}