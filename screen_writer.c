#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "generation.h"

#define DEAD 0
#define ALIVE 1

int writeOnScreen( gen_t* thisGen ){

    usleep(25000);
    static int uses = 0;
    if( uses != 0 ){
        printf("\x1B[%dA", thisGen->row);
    }
    uses++;
    for(int i = 0; i < thisGen->row; i++ ){
        for(int j = 0; j < thisGen->col; j++){
            char c = thisGen->matrix[i][j] == ALIVE? 'X': '-';
            printf("%c ", c);
        }
        printf("\n");
    }

    return 0;
}