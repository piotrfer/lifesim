#include <stdio.h>
#include <stdlib.h>

#include "generation.h"

#define DEAD 0
#define ALIVE 1

int aliveNeighboursCounter( gen_t* origin, int i, int j){

	int result = 0;
	if( i - 1 >= 0 && origin->matrix[i-1][j] == ALIVE) //od góry
		result++;
	if( i + 1 <= origin->row - 1 && origin->matrix[i+1][j] == ALIVE) //od dołu
		result++;
	if( j - 1 >= 0 && origin->matrix[i][j-1] == ALIVE) //od lewej
		result++;
	if( j + 1 <= origin->col - 1 && origin->matrix[i][j+1] == ALIVE) //od prawej
		result++;
	if( i - 1 >= 0 && j -1 >= 0 && origin->matrix[i-1][j-1] == ALIVE) //od góry od lewej
		result++;
	if( i - 1 >= 0 && j + 1 <= origin->col - 1 && origin->matrix[i-1][j+1] == ALIVE) //od góry od prawej
		result++;
	if( i + 1 <= origin->row - 1 && j - 1 >= 0 && origin->matrix[i+1][j-1] == ALIVE) //od dołu od lewej
		result++;
	if( i + 1 <= origin->row - 1 && j + 1 <= origin->col - 1 && origin->matrix[i+1][j+1] == ALIVE) //od dołu od prawej
		result++;

	return result;
}

int nextGen( gen_t* thisGen ){

	gen_t* origin = setGen( thisGen );

	for(int i = 0; i < origin-> row; i++){
		for(int j = 0; j < origin->col; j++){
			int alive_neighbours = aliveNeighboursCounter( origin, i, j);
			if( origin->matrix[i][j] == DEAD && alive_neighbours == 3 )
				thisGen->matrix[i][j] = ALIVE;
			else if( origin->matrix[i][j] == ALIVE && alive_neighbours != 3 && alive_neighbours != 2 )
				thisGen->matrix[i][j] = DEAD;
		}
	}

	thisGen->num++;
	free(origin);

	return 0;
}
