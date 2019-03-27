#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generation.h"

int main(int argc, char** argv){
	
	gen_t* gen0 = malloc( sizeof(gen_t) );
	int n = 10;
	char* filename = NULL;
	char* output = NULL;

	for(int i = 1; i < argc; i++){
		if( !strcmp(argv[i], "--input") && argc > i+1 ){
			if( argv[i+1][0] != '-'){ 
			filename = malloc( sizeof(argv[i+1]));
			strcpy(filename, argv[i+1]);
			}
		}
	}
	if(filename == NULL){
		printf("Brak pliku wejsciowego: brak argumentu\n");
		return EXIT_FAILURE;
	}

	for(int i = 1; i < argc; i++)
	{
		if( !strcmp(argv[i],"--gen") && argc >= i ){
			n = atoi(argv[i+1]);
			if( n < 0 ){
				fprintf(stderr, "Argument: --gen %d: nieprawidlowa ilosc generacji \n", n);
				return EXIT_FAILURE;
			}
		}
	}
	
	int* save = calloc( (n+1)*sizeof(int), sizeof(int) ); 	
	
	for(int i = 0; i < argc; i++){
		
		if( !strcmp(argv[i],"--output") && argc > i+1 ){
			if(argv[i+1][0] != '-'){
			output = malloc( sizeof(argv[i+1]) );
			strcpy(output, argv[i+1]);
			}
		}
		
		if( !strcmp(argv[i],"--save") && argc > i+1 ){
			if( !strcmp(argv[i+1],"all") )
				for(int j = 0; j < n+1; j++)
					save[j] = 1;
			else {	
				while( argc > i + 1 && isdigit(argv[i+1][0]) != 0 ){
					if(atoi(argv[i+1]) <= n)
						save[atoi(argv[i+1])] = 1;
					i++;		
				}
			}
			
		}
	}

	printf("filename: %s \noutput: %s \ngeneration: %d \n", filename, output, n);

	printf("save: \n");
	for(int i = 0; i < n + 1; i++){
		printf("%d ",save[i]);
	}
	printf("\n\n");

	/*

	gen_t* obiekt = malloc( sizeof(gen_t) );
	obiekt->num = 0;
	int * tab = malloc( 10 * sizeof(int) );
	obiekt->matrix = malloc(10*sizeof(tab) );
	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			tab[j] = i * j;
		}
		obiekt->matrix[i]=tab;
	}

	for(int i = 0; i < 10; i++){
		for(int j = 0; j < 10; j++){
			printf("%d ", obiekt->matrix[i][j]);
		}
		printf("\n");
	} */
	
	//free(obiekt);
	free(gen0);
	free(save);
	return 0;
}
