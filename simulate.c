#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include "next_gen.h"

void simulate(gen_t* gen0, int n, char* output, int* save){
	
	gen_t* thisGen = gen0;

	while(thisGen->num < n){
		//writePng(thisGen, output);
		if(save[thisGen->num] == 1){
			//writeTxt(thisGen);
		}
		nextGen(thisGen);

	for(int i = 0; i < thisGen->row; i++){
		for(int j = 0; j < thisGen->col; j++){
			printf("%d ", thisGen->matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	}
}
