#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "generation.h"
#define BUFSIZE 32
#define COLUMN 1
#define MESH 2

int readFile(char* filename, gen_t* gen0){
	FILE *in = fopen(filename, "r");
	if( in == NULL ){
		printf("Brak pliku wejsciowego: plik %s nie istnieje\n", filename);	
		return 1;
	}
	
	int type = MESH;
	gen0->num = 0;

	// określenie typu pliku wejściowego (dwa możliwe rodzaje podawania danych)
	size_t bufsize = BUFSIZE;
	char* line = (char *)malloc( bufsize * sizeof(char) );
	getline(&line, &bufsize, in);
	for(int i = 0; i < sizeof(line) / sizeof (char); i++){
		if( isdigit(line[i]) != 0 ){
			while( isdigit(line[i]) != 0 && i < sizeof(line) / sizeof (char) )
				i++;
			while( line[i] == ' ' && i < sizeof(line) / sizeof (char) )
				i++;
			if( i < sizeof(line) / sizeof(char) && isdigit(line[i]) != 0 ) 
				type = COLUMN;
		}
	}
	rewind(in);
	
	if(type == COLUMN){
		int col, row, x, y;
		int line = 0;
		fscanf(in, "%d", &row);
		fscanf(in, "%d", &col);
		line++;
		if( row < 5  || col < 5){
			printf("Linia 1: Bledne wymiary siatki; podaj liczbe z przedzialu [5,100]\n");
			return 1;
		}
		gen0->col = col;
		gen0->row = row;

		gen0->matrix = malloc( row * sizeof(int *) );
		
		for(int i = 0; i < row; i++)
		{
			gen0->matrix[i] = malloc(col * sizeof(int) );
		}
		while( fscanf(in,"%d %d", &x, &y) != EOF ){
			line++;
			if( x > row || x < 1 || y > col || y < 1){ //w pliku komórki macierzy są ponumerowane od 1!!!
				printf("Linia %d: Bledne wspolrzedne komorki; komorka poza siatka\n", line);
				return 1;
			}
			gen0->matrix[x-1][y-1]++; 
		}
	}
	else if(type == MESH){

	;

	}
	
	return 0;
}
