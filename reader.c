#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "generation.h"

#define BUFSIZE 32
#define COLUMN 1
#define MESH 2

int readFile( gen_t* gen0, char* filename){
	
	FILE *in = fopen(filename, "r");
	if( in == NULL ){
		fprintf(stderr, "Brak pliku wejsciowego: plik %s nie istnieje\n", filename);	
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
			fprintf(stderr, "Linia 1: Bledne wymiary siatki; podaj liczbe z przedzialu [5,100]\n");
			return 1;
		}
		gen0->col = col;
		gen0->row = row;

		gen0->matrix = malloc( row * sizeof(int *) );

		for(int i = 0; i < row; i++)
		{
			gen0->matrix[i] = calloc(col * sizeof(int), sizeof(int) );
		}
		while( fscanf(in,"%d %d", &x, &y) != EOF ){
			line++;
			if( x > row || x < 1 || y > col || y < 1){ //w pliku komórki macierzy są ponumerowane od 1!!!
				fprintf(stderr, "Linia %d: Bledne wspolrzedne komorki; komorka poza siatka\n", line);
				return 1;
			}
			gen0->matrix[x-1][y-1]++; 
		}
	}
	else if(type == MESH){
		char c;
		int col = 0, row = 1;
		while( (c = getc(in)) != EOF && (c != '\n') )
			col++;
		rewind(in);

		gen0->matrix = malloc( sizeof(int *) );
		gen0->matrix[0] = calloc( col * sizeof(int), sizeof(int) );

		int i = 0;
		while( (c = getc(in) ) != EOF ){
			if(c == '\n'){
				row++;
				gen0->matrix = realloc(gen0->matrix, row * sizeof(int *));
				if( gen0->matrix == NULL ){
					fprintf(stderr, "Blad realokowania pamieci\n");
					return 1;
				}
				gen0->matrix[row-1] = calloc( col * sizeof(int), sizeof(int) );
				i = 0;
			}
			else if( (c == '0' || c == '1') && i < col ){
				gen0->matrix[row-1][i++] = c - '0';
			}
			else if(i >= col){
				fprintf(stderr, "Linia %d: Zbyt wiele liczb w rzedzie\n", row);
				return 1;
			}
			else{
				fprintf(stderr, "Linia %d: Bledna wartosc komorki: %d\n", row, c);
				return 1;
			}
		}

		gen0->matrix = realloc( gen0->matrix, (--row) * sizeof( int *) );
		gen0->col = col;
		gen0->row = row;
	}

	fclose(in);

	return 0;
}
