#include <stdio.h>
#include "../generation.h"
#include "../reader.h"
#include "../next_gen.h"
#include "../txt_writer.h"

int main(int argc, char** argv){

	if( argc < 1 ){
		printf("Brak argumentu\n");
		return 1;
	}

	gen_t gen;

	if( readFile(argv[1], &gen) != 0 ){
		return 1;
	}
	for(int i = 0; i <= 10; i++){
		if( i == 1 || i == 5 || i == 10 )
			writeTxt( &gen );
		nextGen( &gen );
	}
}
