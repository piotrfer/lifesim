#include <stdlib.h>
#include "gconfig.h"

gconfig_t* setConfig(){

    gconfig_t* config = malloc( sizeof (gconfig_t) );
    config->n = 10;
    
    config->pngconfig = malloc( sizeof (pngconfig_t) );
    config->pngconfig->border = 50;
    config->pngconfig->field = 100;
    config->pngconfig->mark_alive = 0;
    config->pngconfig->mark_dead = 255;
    config->pngconfig->mark_default = 255;

    return config;
}