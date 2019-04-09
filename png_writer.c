#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <png.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "generation.h"
#include "gconfig.h"

#define DEAD 0
#define ALIVE 1
#define BUFSIZE 32

int process_file();
int write_png_file( char * );

int writePng( gen_t* thisGen, pictureconfig_t* pictureconfig){

	int errcnt = 0;
	char* file = malloc( BUFSIZE * sizeof(char) );
	sprintf(file, "save/gen%d.png", thisGen->num);
	struct stat st = {0};
	if( stat("save", &st) == -1 )
		mkdir("save", 0700);

	if( process_file(thisGen, pictureconfig) != 0 )
		errcnt++;
	if( write_png_file(file) != 0 )
		errcnt++;	

	free(file);

	if( errcnt > 0 )
		return 1;
	else return 0;
}

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

int write_png_file(char* file_name) {
	FILE *fp = fopen(file_name, "wb");
	if (!fp){
		fprintf(stderr, "[write_png_file] File %s could not be opened for writing", file_name);
		return 1;
	}
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr){
		fprintf(stderr, "[write_png_file] png_create_write_struct failed");
		return 1;
	}
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr){
		fprintf(stderr, "[write_png_file] png_create_info_struct failed");
		return 1;
	}
	if (setjmp(png_jmpbuf(png_ptr))){
		fprintf(stderr, "[write_png_file] Error during init_io");
		return 1;
	}
	png_init_io(png_ptr, fp);

	if (setjmp(png_jmpbuf(png_ptr))){
		fprintf(stderr, "[write_png_file] Error during writing header");
		return 1;
	}
	png_set_IHDR(png_ptr, info_ptr, width, height,
			bit_depth, color_type, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	if (setjmp(png_jmpbuf(png_ptr))){
		fprintf(stderr, "[write_png_file] Error during writing bytes");
		return 1;
	}
	png_write_image(png_ptr, row_pointers);

	if (setjmp(png_jmpbuf(png_ptr))){
		fprintf(stderr, "[write_png_file] Error during end of write");
		return 1;
	}
	png_write_end(png_ptr, NULL);

	for (y=0; y<height; y++)
		free(row_pointers[y]);
	free(row_pointers);

	fclose(fp);

	return 0;
}

int process_file(gen_t* thisGen, pictureconfig_t* pictureconfig) {
	width = thisGen->col * pictureconfig->field + 2*pictureconfig->border;
	height = thisGen->row * pictureconfig->field + 2*pictureconfig->border;
	bit_depth = 8;
	color_type = PNG_COLOR_TYPE_GRAY;

	number_of_passes = 7;
	row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
	if( row_pointers == NULL )
		return 1;

	for (y=0; y<height; y++){
		row_pointers[y] = (png_byte*) malloc(sizeof(png_byte) * width);
		if(row_pointers[y] == NULL)
			return 1;
	}
	for (y=0; y<height; y++) {
		png_byte* row = row_pointers[y];
		for (x=0; x<width; x++) {
			if( x > pictureconfig->border && x < width-pictureconfig->border && y > pictureconfig->border && y < height-pictureconfig->border){

				int mrow = (y - pictureconfig->border) / (pictureconfig->field+1);
				int mcol = (x - pictureconfig->border) / (pictureconfig->field+1);

				row[x] = thisGen->matrix[mrow][mcol] == ALIVE ? pictureconfig->mark_alive: pictureconfig->mark_dead;
			}
			else{
				row[x] = pictureconfig->mark_default;
			}
		}
	}

	return 0;
}
