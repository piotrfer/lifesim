#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "generation.h"
#define DEAD 0
#define ALIVE 1

void writeTxt( gen_t* thisGen){
	
	char* file = malloc( 32 * sizeof(char) );	
	sprintf(file, "save/gen%d", thisGen->num);
	struct stat st = {0};
	if( stat("save", &st) == -1 )
		mkdir("save");

	FILE *out = fopen( file, "w" );
	if( out == NULL)
		printf("ajajajaj\n");
	else{
	for(int i = 0; i < thisGen->row; i++){
		for(int j = 0; j < thisGen->col; j++){
			fprintf(out, "%d", thisGen->matrix[i][j]);
		}
		fprintf(out, "\n");
	}
	}
	fclose(out);
}
