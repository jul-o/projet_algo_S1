#ifndef FUNCTIONS
#define FUNCTIONS

typedef struct tiling{
    int lines;
    int columns;
    int ** values;
} Tiling;

void get_dimensions(char* buffer, int* i_width, int* i_height);
void displayTiling();

Tiling* loadTiling(char * filePath);

#endif
