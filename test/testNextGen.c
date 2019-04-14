#include <stdio.h>
#include <stdlib.h>

#include "../generation.h"
#include "../next_gen.h"

void fillTest( gen_t* test){
    
    test->num = 0;
    test->row = 5;
    test->col = 5;

    test->matrix = malloc( test->row * sizeof( int* ));
    for(int i = 0; i < test->row; i++){
        test->matrix[i] = calloc( test->col * sizeof( int ), sizeof (int) );
    }

    test->matrix[0][2] = 1;
    test->matrix[1][1] = 1;
    test->matrix[1][2] = 1;
    test->matrix[1][3] = 1;
    test->matrix[2][0] = 1;
    test->matrix[2][1] = 1;
    test->matrix[2][3] = 1;
    test->matrix[2][4] = 1;
    test->matrix[3][1] = 1;
    test->matrix[3][2] = 1;
    test->matrix[3][3] = 1;
    test->matrix[4][2] = 1;
}

void fillOdczyt1( gen_t* odczyt ){
    
    odczyt->num = 4;
    odczyt->row = 5;
    odczyt->col = 5;

    odczyt->matrix = malloc( odczyt->row * sizeof( int* ));
    for(int i = 0; i < odczyt->row; i++){
        odczyt->matrix[i] = calloc( odczyt->col * sizeof( int ), sizeof (int) );
    }

    odczyt->matrix[0][1] = 1;
    odczyt->matrix[0][2] = 1;
    odczyt->matrix[0][3] = 1;
    odczyt->matrix[1][0] = 1;
    odczyt->matrix[1][2] = 1;
    odczyt->matrix[1][4] = 1;
    odczyt->matrix[2][0] = 1;
    odczyt->matrix[2][1] = 1;
    odczyt->matrix[2][3] = 1;
    odczyt->matrix[2][4] = 1;
    odczyt->matrix[3][0] = 1;
    odczyt->matrix[3][2] = 1;
    odczyt->matrix[3][4] = 1;
    odczyt->matrix[4][1] = 1;
    odczyt->matrix[4][2] = 1;
    odczyt->matrix[4][3] = 1;
}

void fillOdczyt2( gen_t* odczyt ){
    
    odczyt->num = 9;
    odczyt->row = 5;
    odczyt->col = 5;

    odczyt->matrix = malloc( odczyt->row * sizeof( int* ));
    for(int i = 0; i < odczyt->row; i++){
        odczyt->matrix[i] = calloc( odczyt->col * sizeof( int ), sizeof (int) );
    }

    odczyt->matrix[0][1] = 1;
    odczyt->matrix[0][2] = 1;
    odczyt->matrix[0][3] = 1;
    odczyt->matrix[1][0] = 1;
    odczyt->matrix[1][4] = 1;
    odczyt->matrix[2][0] = 1;
    odczyt->matrix[2][4] = 1;
    odczyt->matrix[3][0] = 1;
    odczyt->matrix[3][4] = 1;
    odczyt->matrix[4][1] = 1;
    odczyt->matrix[4][2] = 1;
    odczyt->matrix[4][3] = 1;
}

int compareMatrix( gen_t test, gen_t odczyt){
	/*
	** 0 - identyczne macierze
	** 1 - różne macierze
	*/

	if( test.row != odczyt.row || test.col != odczyt.col ){
		printf("RÓŻNE! - row: odczyt %d vs test %d i col: odczyt %d vs test %d \n", odczyt.row, test.row, odczyt.col, test.col);
		return 1;
	}

	for(int i = 0; i < test.row; i++){
		for(int j = 0; j < test.col; j++){
			if( test.matrix[i][j] != odczyt.matrix[i][j] ){
				printf("RÓŻNE! - row:%d col:%d wartosc: odczyt: %d test: %d\n", i, j, odczyt.matrix[i][j], test.matrix[i][j]);
				return 1;
			}
		}
	}
	return 0;
}

int main(){

    gen_t test, odczyt[2];

    fillTest( &test );
    fillOdczyt1( &odczyt[0] );
    fillOdczyt2( &odczyt[1] );
    
    for(int i = 0; i < 10 + 1; i++){
        if( nextGen( &test ) != 0 ){
            printf("Test1: fail\n");
            return 1;
        }
        if( test.num == 4 ){
            if( compareMatrix( test, odczyt[0]) != 0){
                printf("Test1: fail\n");
                return 1;
            }
        }
        if( test.num == 9 ){
           if( compareMatrix( test, odczyt[1]) != 0){
                printf("Test1: fail\n");
                return 1;
            }
        }
    }

    printf("Test1: success\n");

    return 0;
}