#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "fonctions_reponses.h"
#include "./test/stack_test.c"

int main(int argc, char** argv){
  char * path = "ressources/45-1";
  Tiling * tiles = loadTiling(path);

  // solution1(tiles);
  // solution2(tiles);
  // solution3(tiles);
  solution4(tiles);

  // displayTiling(tiles);

  // testStack();


  // For debuging purpose
  printf("Press ENTER key to Continue\n");  
  getchar(); 
  return 0;
}
