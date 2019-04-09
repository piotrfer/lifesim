#include <stdio.h>
#include "../generation.h"
#include "../reader.h"

void wypisz( gen_t* gen){

	for(int i = 0; i < gen->row; i++){
		for(int j = 0; j < gen->col; j++){
			printf("%d", gen->matrix[i][j]);
		}
		printf("\n");
	}

}

int main(int argc, char** argv){

	gen_t gen;

	for(int i = 1; i < argc; i++){
		if( readFile( argv[i], &gen ) == 0 )
			wypisz(&gen);
	}
}
