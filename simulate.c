#include <stdio.h>
#include <stdlib.h>

#include "generation.h"
#include "gconfig.h"
#include "next_gen.h"

int simulate(gen_t* gen0, gconfig_t* config, int saveFile (gen_t* thisGen, char* output), int writeFile( gen_t* thisGen, pictureconfig_t*), int writeOnScreen (gen_t*) ){

	int errcnt = 0;
	gen_t* thisGen = gen0;

	while(thisGen->num < config->n){
		if( writeFile != NULL)
			if( writeFile(thisGen, config->pictureconfig) != 0 )
				errcnt++;

		if( writeOnScreen != NULL)
			if( writeOnScreen(thisGen) != 0)
				errcnt++;

		if(config->gen_to_save[thisGen->num] == 1){
			if( saveFile != NULL)
				if( saveFile(thisGen, config->txtoutput) != 0 )
					errcnt++;
		}
		if( nextGen(thisGen) != 0 )
			errcnt++;
	}

	if(errcnt > 0)
		return 1;
	else return 0;
}
