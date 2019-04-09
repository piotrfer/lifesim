typedef struct{
    char* pngoutput;
    int border;
    int field;
    int mark_dead;
    int mark_alive;
    int mark_default;
} pngconfig_t;

typedef struct{
    int n;
    char* filename;
    char* txtoutput;
    int* gen_to_save;
    pngconfig_t* pngconfig;
} gconfig_t;

gconfig_t* setConfig();