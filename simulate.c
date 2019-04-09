#include <stdio.h>
#include <stdlib.h>
#include "generation.h"
#include "gconfig.h"
#include "next_gen.h"
#include "txt_writer.h"
#include "png_writer.h"

int simulate(gen_t* gen0, gconfig_t* config){

	int errcnt = 0;
	gen_t* thisGen = gen0;

	while(thisGen->num < config->n){
		if( writePng(thisGen, config->pngconfig) != 0 )
			errcnt++;

		if(config->gen_to_save[thisGen->num] == 1){
			if( writeTxt(thisGen) != 0 )
				errcnt++;
		}
		if( nextGen(thisGen) != 0 )
			errcnt++;
	}

	if(errcnt > 0)
		return 1;
	else return 0;
}
