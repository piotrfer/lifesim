#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "generation.h"
#include "reader.h"
#include "gconfig.h"
#include "simulate.h"
#include "txt_writer.h"
#include "png_writer.h"
#include "random.h"

void help(){
	printf("** lifesim **\n");
	printf("program symulujacy gre w zycie Johna Conwaya\n");
	printf("mozliwe argumenty wywolania:\n");
	printf("--input [filename] -- nazwa pliku zawierajacego dane wejsciowe; \"random\" -- losowo generowana siatka\n");
	printf("--gen [number] -- liczba generacji do zasymulowania\n");
	printf("--pngoutput [filename] -- prefiks pliku .png stanowiacego plik wyjsciowy programu\n");
	printf("--txtoutput [filename] -- prefiks pliku .txt stanowiacego plik wyjsciowy programu\n");
	printf("--save [number] -- numery generacji do zapisania w postaci pliku .txt; \"all\" -- wszystkie generacje\n");
	printf("=========================================\n");
}

int readArguments(int argc, char** argv, gconfig_t* config){

	for(int i = 1; i < argc; i++){
		if( !strcmp(argv[i], "--input") && argc > i+1 ){
			if( argv[i+1][0] != '-'){ 
				config->filename = malloc( sizeof(argv[i+1]));
				strcpy(config->filename, argv[i+1]);
			}
		}
	}

	if(config->filename == NULL){
		fprintf(stderr, "Brak pliku wejsciowego: brak argumentu\n");
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

		if( !strcmp(argv[i],"--pngoutput") && argc > i+1 ){
			if(argv[i+1][0] != '-'){
				config->pictureconfig->pngoutput = malloc( sizeof(argv[i+1]) );
				strcpy(config->pictureconfig->pngoutput, argv[i+1]);
			}
		}

		if( !strcmp(argv[i],"--txtoutput") && argc > i+1 ){
			if(argv[i+1][0] != '-'){
				config->txtoutput = malloc( sizeof(argv[i+1]) );
				strcpy(config->txtoutput, argv[i+1]);
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

	gen_t* gen0 = setGen( NULL ); 
	gconfig_t* config = setConfig();
 
	

	if( argc == 1 ){
		help();
		return EXIT_SUCCESS;
	}

	if( readArguments(argc, argv, config) != 0 ){
		return EXIT_FAILURE;
	}

	if( !strcmp(config->filename, "random") ){
		if( fillRandom( gen0, config->randomconfig) != 0 ){
			return EXIT_FAILURE;
		}
	}
	else if( readFile( gen0, config->filename ) != 0 ){
		return EXIT_FAILURE;
	}


	if( simulate( gen0, config, writeTxt, writePng, NULL ) != 0 )
		return EXIT_FAILURE;      

	printf("Zadanie wykonano pomyslnie!\n");
	freeConfig( config );
	freeGen( gen0 );

	return EXIT_SUCCESS;
}
