#include <time.h>
#include <stdlib.h>

#include "generation.h"
#include "gconfig.h"

int fillRandom( gen_t* gen0, randomconfig_t* randomconfig){
    
    srand(time(NULL));

    gen0->row = randomconfig->row;
    gen0->col = randomconfig->col;
    gen0->num = 0;

    gen0->matrix = malloc( gen0->row * sizeof( int* ) );
    for(int i = 0; i < gen0->row; i++){
        gen0->matrix[i] = malloc( gen0->col * sizeof( int ) );
        for(int j = 0; j < gen0->col; j++){
            gen0->matrix[i][j] = rand()%2;
        }
    }

    return 0;
}