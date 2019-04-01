#include <stdio.h>
#include <stdlib.h>
#include "generation.h"

void simulate(gen_t* gen0, int n, char* output, int* save){
	
	gen_t* thisGen = gen0;

	while(thisGen->num < n){
		//writePng(thisGen, output);
		if(save[thisGen->num] == 1){
			//writeTxt(thisGen);
		}
		//nextGen(thisGen);
	}
}
