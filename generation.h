#ifndef _generation_h
#define _generation_h

typedef struct{
	int num;
	int col;
	int row;
	int** matrix;
} gen_t;

gen_t* setGen();

#endif