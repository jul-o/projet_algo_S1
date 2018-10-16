#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "fonctions_reponses.h"

int main(int argc, char** argv){
  char * path = "ressources/45-1";
  Tiling * tiles = loadTiling(path);

  // solution1(tiles);
  solution2(tiles);

  displayTiling(tiles);

  // For debuging purpose
  printf("Press ENTER key to Continue\n");  
  getchar(); 
  return 0;
}
