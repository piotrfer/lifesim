#include <stdio.h>
#include <stdlib.h>

#include "../generation.h"
#include "../reader.h"
#include "../txt_writer.h"

void fillTest1( gen_t* test1 ){

	test1->row = 5;
	test1->col = 5;
	test1->matrix = malloc( test1->row * sizeof( int* ) );
	for(int i = 0; i < test1->row; i++ ){
		test1->matrix[i] = malloc( test1->col * sizeof( int ) );
		for(int j = 0; j < test1->col; j++){
			test1->matrix[i][j] = (i+j) % 2;
		}
	}

}

void fillTest2( gen_t* test2 ){

	test2->row = 10;
	test2->col = 10;
	test2->matrix = malloc( test2->row * sizeof( int* ) );
	for(int i = 0; i < test2->row; i++)
		test2->matrix[i] = calloc( test2->col * sizeof( int ) , sizeof( int) );

	for(int i = 0; i < test2->row; i++)
		test2->matrix[i][i] = 1;
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


int main(int argc, char** argv){

	gen_t test[2];
	gen_t odczyt_siatki[5];
	int errcnt = 0;

	fillTest1( &test[0] );
	fillTest2( &test[1] );

	freopen("/dev/null", "w", stderr);

	printf("Test1: ");
	if( readFile( &(odczyt_siatki[0]), "t1.txt" ) != 0 ){
		printf("\nBledna obsluga bledow");
		errcnt++;
	}
	if( compareMatrix( test[0], odczyt_siatki[0]) != 0 ){
		printf("\nBledne wczytanie wartosci");
	}
	if( errcnt == 0 ){
		printf("success\n");
	}
	else{
		printf("\n fail\n");
	}
	errcnt = 0;

	printf("Test2: ");
	if( readFile( &(odczyt_siatki[1]), "t2.txt" ) != 0 ){
		printf("\nBledna obsluga bledow");
		errcnt++;
	}
	if( compareMatrix( test[1], odczyt_siatki[1]) != 0 ){
		printf("\nBledne wczytanie wartosci");
	}
	if( errcnt == 0 ){
		printf("success\n");
	}
	else{
		printf("\n fail\n");
	}
	errcnt = 0;


	if( readFile( &(odczyt_siatki[2]), "t3.txt" ) != 0 ){
		printf("Test3: success\n");
	}
	else{
		printf("Test3: fail\n");
	}
	
	if( readFile( &odczyt_siatki[3], "t4.txt" ) != 0 ){
		printf("Test4: success\n");
	}
	else{
		printf("Test4: fail\n");
	}
	
	
	if( readFile( &odczyt_siatki[4], "t5.txt" ) != 0 ){
		printf("Test5: success\n");
	}
	else{
		printf("\rTest5: fail\n");
	}

}