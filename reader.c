#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "generation.h"
#define BUFSIZE 32

int readFile(char* filename, gen_t* gen0){
	FILE *in = fopen(filename, "r");
	if( in == NULL ){
		printf("Brak pliku wejsciowego: plik %s nie istnieje\n", filename);	
		return 1;
	}
	
	int type = 2; //1, 2 - typy zapisu danych do pliku
	size_t bufsize = BUFSIZE;
	char* line = (char *)malloc( bufsize * sizeof(char) );
	getline(&line, &bufsize, in);
	
	printf("%s \n", line);
	

	return 0;
}	
