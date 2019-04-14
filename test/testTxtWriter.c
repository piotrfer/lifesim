#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../generation.h"
#include "../txt_writer.h"

void fillGen1( gen_t* test ){
    test->num = 0;
    test->row = 10;
    test->col = 10;

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
    test->row = 7;
    test->col = 11;

    test->matrix = malloc( test->row * sizeof( int* ));
    for(int i = 0; i < test->row; i++){
        test->matrix[i] = malloc( test->col * sizeof( int ) );
        for(int j = 0; j < test->col; j++){
            test->matrix[i][j] = rand()%2;
        }
    }

}

int compareFile( FILE *in, gen_t test){
    /*
    ** 0 - pliki identyczne
    ** 1 - pliki różnią się
    */
   char c;

    for(int i = 0; i < test.row; i++){
        for(int j = 0; j < test.col; j++){
            c = getc( in );
            if( c == '\n' )
                c = getc( in );
            if( c == EOF || (c - '0') != test.matrix[i][j] ){
                printf("[%d, %d] expected: %d instead of: %d\n", i, j, test.matrix[i][j], c-'0');
                return 1;
            }
        }
    }

    return 0;

}
int main(){

    gen_t test[3];
    gen_t odczyt[3];

    fillGen1( &test[0] );
    fillGen2( &test[1] );
    fillGen3( &test[2] );

    writeTxt( &test[0], NULL );
    writeTxt( &test[1], "teststring" );
    writeTxt( &test[2], "szczescboze"  );
    
    FILE *in;
    
    in = fopen("save/gen0.txt", "r");
    if( compareFile(in, test[0] ) != 0 ){
        printf("Test1: failed\n");
    }
    else{
        printf("Test1: success\n");
    }
    
    in = fopen("save/teststring1.txt", "r");
    if( compareFile(in, test[1] ) != 0 ){
        printf("Test2: failed\n");
    }
    else{
        printf("Test2: success\n");
    }

    in = fopen("save/szczescboze2.txt", "r");
    if( compareFile(in, test[2] ) != 0 ){
        printf("Test3: failed\n");
    }
    else{
        printf("Test3: success\n");
    }

    fclose( in );
    free( test[0].matrix );
    free( test[1].matrix );
    free( test[2].matrix );

    return 0;
}