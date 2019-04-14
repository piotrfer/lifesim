#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../generation.h"
#include "../gconfig.h"
#include "../png_writer.h"

#define BUFSIZE 32

void fillGen1( gen_t* test ){
    test->num = 0;
    test->row = 43;
    test->col = 12;

    test->matrix = malloc( test->row * sizeof( int* ));
    for(int i = 0; i < test->row; i++){
        test->matrix[i] = malloc( test->col * sizeof( int ) );
        for(int j = 0; j < test->col; j++){
            test->matrix[i][j] = (i+3*j)%2;
        }
    }
}

void fillGen2( gen_t* test ){
    test->num = 1;
    test->row = 5;
    test->col = 5;
    
    test->matrix = malloc( test->row * sizeof( int* ));
    for(int i = 0; i < test->row; i++){
        test->matrix[i] = malloc( test->col * sizeof( int ) );
        for(int j = 0; j < test->col; j++){
            test->matrix[i][j] = (5*i+j)%2;
        }
    }

}

void fillGen3( gen_t* test ){
    srand(time(NULL));
    
    test->num = 2;
    test->row = 24;
    test->col = 9;

    test->matrix = malloc( test->row * sizeof( int* ));
    for(int i = 0; i < test->row; i++){
        test->matrix[i] = malloc( test->col * sizeof( int ) );
        for(int j = 0; j < test->col; j++){
            test->matrix[i][j] = rand()%2;
        }
    }

}

int main(){
    gen_t test[3];
    pictureconfig_t config;

    config.border = 50;
    config.field = 100;
    config.mark_dead = 255;
    config.mark_alive = 0; 
    config.mark_default = 255;

    fillGen1( &test[0] );
    fillGen2( &test[1] );
    fillGen3( &test[2] );

    if( writePng( &test[0], &config ) != 0  ){
        printf("Test1: fail\n");
    }
    else{
            printf("Test1: success\n");
    }

    config.pngoutput = malloc( BUFSIZE * sizeof( char ) );
    config.pngoutput = "teststring";

    if( writePng( &test[1], &config ) != 0  ){
        printf("Test2: fail\n");
    }
    else{
            printf("Test2: success\n");
    }
    
    config.pngoutput = "dowolnystring";


    if( writePng( &test[2], &config ) != 0  ){
        printf("Test3: fail\n");
    }
    else{
            printf("Test3: success\n");
    }
    
    free( test[0].matrix );
    free( test[1].matrix );
    free( test[2].matrix );
}