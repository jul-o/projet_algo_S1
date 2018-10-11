#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "fonctions_reponses.h"

int main(int argc, char** argv){
  char * path = "ressources/45-1";
  struct tiling* tiles = loadTiling(path);
  solution_1(tiles);
  return 0;
}
