#ifndef FUNCTIONS
#define FUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tiling{
    int lines;
    int columns;
    int ** values;
} Tiling;

void readTilingDimensions(FILE * f, int * rows, int * columns);
void readTiling(FILE * f, int * lines, int * columns, int ** tiling);

void displayTiling();

Tiling* loadTiling(char * filePath);

#endif
