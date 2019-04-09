#include <stdio.h>
#include "../generation.h"
#include "../png_writer.h"
#include "../txt_writer.h"
#include "../reader.h"

int main(int argc, char** argv ){

	gen_t gen;

	for(int i = 1; i < argc; i++){

		if( readFile( argv[i], &gen) == 0 ){
			writeTxt( &gen );
			writePng( &gen, NULL );
		}

	}
}
