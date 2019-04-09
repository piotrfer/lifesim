#include <stdlib.h>
#include "generation.h"

gen_t* setGen(gen_t* thisGen){

    gen_t* origin = malloc( sizeof( gen_t* ));
    if( thisGen != NULL ){
        origin->num = thisGen->num;
        origin->col = thisGen->col;
        origin->row = thisGen->row;
        origin->matrix = malloc( origin->row * sizeof(int*) );
        for(int i = 0; i < origin->row; i++){
            origin->matrix[i] = calloc( origin->col * sizeof(int), sizeof(int) );
        }
        for(int i = 0; i < origin->row; i++){
            for(int j = 0; j < origin->col; j++){
                origin->matrix[i][j] = thisGen->matrix[i][j];
            }
        }
    }
    return origin;
}