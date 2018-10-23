#ifndef FONCTIONS_REPONSES
#define FONCTIONS_REPONSES
#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "stack.h"

void solution1(Tiling* tiles);
void solution2(Tiling* tiles);
void solution3(Tiling* tiles);
void solution4(Tiling* tiles);
void solution4bis(Tiling * tiles);

void checkOpenRectangles(Tiling* tiles, Node** stack, int i, int j, int* hauteurs, int* max_size,int* x0,int* y0,int* x1,int* y1);

#endif
