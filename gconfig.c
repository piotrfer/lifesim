#include <stdlib.h>
#include "gconfig.h"

gconfig_t* setConfig(){

    gconfig_t* config = malloc( sizeof (gconfig_t) );
    config->n = 10;
    
    config->pictureconfig = malloc( sizeof (pictureconfig_t) );
    config->pictureconfig->border = 50;
    config->pictureconfig->field = 100;
    config->pictureconfig->mark_alive = 0;
    config->pictureconfig->mark_dead = 255;
    config->pictureconfig->mark_default = 255;

    config->randomconfig = malloc( sizeof (randomconfig_t) );
    config->randomconfig->col = 100;
    config->randomconfig->row = 100;

    return config;
}

void freeConfig( gconfig_t* config )
{
    free( config->pictureconfig->pngoutput);
    free( config->txtoutput);
    free( config->randomconfig );
    free( config->pictureconfig );
    free( config->gen_to_save );
    free( config );
}