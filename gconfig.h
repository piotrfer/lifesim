#ifndef _gconfig_h
#define _gconfig_h

typedef struct{
    int row;
    int col;
} randomconfig_t;

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
    randomconfig_t* randomconfig;
} gconfig_t;

gconfig_t* setConfig();
void freeConfig( gconfig_t* );

#endif