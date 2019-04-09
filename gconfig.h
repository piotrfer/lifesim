#ifndef _gconfig_h
#define _gconfig_h

typedef struct{
    char* pngoutput;
    int border;
    int field;
    int mark_dead;
    int mark_alive;
    int mark_default;
} pictureconfig_t;

typedef struct{
    int n;
    char* filename;
    char* txtoutput;
    int* gen_to_save;
    pictureconfig_t* pictureconfig;
} gconfig_t;

gconfig_t* setConfig();

#endif