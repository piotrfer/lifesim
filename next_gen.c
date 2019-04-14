#include <stdio.h>
#include <stdlib.h>

#include "generation.h"

#define DEAD 0
#define ALIVE 1
#define NBOUR 8

int aliveNeighboursCounter( int* vector, int n ){

	int counter = 0;

	for(int i = 0; i < n; i++)
		if( vector[i] == ALIVE )
			counter++;

	return counter;
}

int* vectorMaker( gen_t* origin, int i, int j){
	
	int* vector = malloc( NBOUR * sizeof(int) );
	
	vector[0] = i - 1 >= 0 ? origin->matrix[i-1][j]: 0; //od góry 
	vector[1] = i + 1 <= origin->row - 1 ? origin->matrix[i+1][j]: 0; //od dołu 
	vector[2] = j - 1 >= 0 ? origin->matrix[i][j-1]: 0; //od lewej 
	vector[3] = j + 1 <= origin->col - 1 ? origin->matrix[i][j+1] : 0; //od prawej
	vector[4] = i - 1 >= 0 && j -1 >= 0 ? origin->matrix[i-1][j-1] : 0; //od góry od lewej
	vector[5] = i - 1 >= 0 && j + 1 <= origin->col - 1 ? origin->matrix[i-1][j+1] : 0; //od góry od prawej
	vector[6] = i + 1 <= origin->row - 1 && j - 1 >= 0 ? origin->matrix[i+1][j-1] : 0; //od dołu od lewej
	vector[7] = i + 1 <= origin->row - 1 && j + 1 <= origin->col - 1 ? origin->matrix[i+1][j+1] : 0; //od dołu od prawej

	return vector;
}

int nextGen( gen_t* thisGen ){

	gen_t* origin = setGen( thisGen );

	for(int i = 0; i < origin-> row; i++){
		for(int j = 0; j < origin->col; j++){
			int* vector = vectorMaker(origin, i, j);
			int alive_neighbours = aliveNeighboursCounter( vector, NBOUR);
			free(vector);
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
