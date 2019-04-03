#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generation.h"
#include "reader.h"
#include "simulate.h"

void help(){
printf("** lifesim **\n");
printf("program symulujacy gre w zycie Johna Conwaya\n");
printf("mozliwe argumenty wywolania:\n");
printf("--input [filename] -- nazwa pliku zawierajacego dane wejsciowe\n");
printf("--gen [number] -- liczba generacji do zasymulowania\n");
printf("--output [filename] -- prefiks pliku .png stanowiacego plik wyjsciowy programu\n");
printf("--save [number] -- numery generacji do zapisania w postaci pliku .txt\n");
printf("=========================================\n");
}

int main(int argc, char** argv){
	
	gen_t gen0;
	int n = 10;
	char* filename = NULL;
	char* output = NULL;

	if( argc == 1 ){
		help();
		return EXIT_SUCCESS;
	}

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
			n = atoi(argv[i+1]) + 1;
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
	printf("\n");
	
	int a = readFile( filename, &gen0 );
	if( a != 0 )
		return EXIT_FAILURE;
	printf("Wczytana generacja\n");
	for(int i = 0; i < gen0.row; i++){
		for(int j = 0; j < gen0.col; j++){
			printf("%d ", gen0.matrix[i][j]);
		}
		printf("\n");
	} 
	printf("\n");
	
	simulate( &gen0, n, output, save);

	free(save);
	return 0;
}
