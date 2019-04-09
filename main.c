#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "generation.h"
#include "reader.h"
#include "gconfig.h"
#include "simulate.h"

void help(){
	printf("** lifesim **\n");
	printf("program symulujacy gre w zycie Johna Conwaya\n");
	printf("mozliwe argumenty wywolania:\n");
	printf("--input [filename] -- nazwa pliku zawierajacego dane wejsciowe\n");
	printf("--gen [number] -- liczba generacji do zasymulowania\n");
	printf("--output [filename] -- prefiks pliku .png stanowiacego plik wyjsciowy programu\n");
	printf("--save [number] -- numery generacji do zapisania w postaci pliku .txt; \"all\" -- wszystkie generacje\n");
	printf("=========================================\n");
}

int getArguments(int argc, char** argv, gconfig_t* config){

	for(int i = 1; i < argc; i++){
		if( !strcmp(argv[i], "--input") && argc > i+1 ){
			if( argv[i+1][0] != '-'){ 
				config->filename = malloc( sizeof(argv[i+1]));
				strcpy(config->filename, argv[i+1]);
			}
		}
	}

	if(config->filename == NULL){
		printf("Brak pliku wejsciowego: brak argumentu\n");
		return -1;
	}

	for(int i = 1; i < argc; i++)
	{
		if( !strcmp(argv[i],"--gen") && argc >= i ){
			config->n = atoi(argv[i+1]) + 1;
			if( config->n < 0 ){
				fprintf(stderr, "Argument: --gen %d: nieprawidlowa ilosc generacji \n", config->n);
				return -1;
			}
		}
	}

	config->gen_to_save = calloc( (config->n + 1)*sizeof(int), sizeof(int) ); 	

	for(int i = 0; i < argc; i++){

		if( !strcmp(argv[i],"--output") && argc > i+1 ){
			if(argv[i+1][0] != '-'){
				config->pngconfig->pngoutput = malloc( sizeof(argv[i+1]) );
				strcpy(config->pngconfig->pngoutput, argv[i+1]);
			}
		}

		if( !strcmp(argv[i],"--save") && argc > i+1 ){
			if( !strcmp(argv[i+1],"all") )
				for(int j = 0; j < config->n + 1; j++)
					config->gen_to_save[j] = 1;
			else {	
				while( argc > i + 1 && isdigit(argv[i+1][0]) != 0 ){
					if(atoi(argv[i+1]) <= config->n)
						config->gen_to_save[atoi(argv[i+1])] = 1;
					i++;		
				}
			}

		}
	}

	return 0;

}

int main(int argc, char** argv){

	gen_t* gen0 = malloc(sizeof( gen_t* ));//setGen(); 
	gconfig_t* config = malloc(sizeof( gconfig_t*));//setConfig();

	if( argc == 1 ){
		help();
		return EXIT_SUCCESS;
	}

	if( getArguments(argc, argv, config) != 0 ){
		return EXIT_FAILURE;
	}

	int a = readFile( gen0, config->filename );
	if( a != 0 )
		return EXIT_FAILURE;

	if( simulate( gen0, config ) != 0 )
		return EXIT_FAILURE;      

	printf("Zadanie wykonano pomyslnie!\n");

	free(config);
	free(gen0);

	return EXIT_SUCCESS;
}
