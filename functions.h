#ifndef FUNCTIONS
#define FUNCTIONS
#include <stdbool.h>

typedef struct tiling{
    int lines;
    int columns;
    bool ** values;
} Tiling;

void get_dimensions(char* buffer, int* i_width, int* i_height);
void displayTiling();

Tiling* loadTiling(char * filePath);

#endif
