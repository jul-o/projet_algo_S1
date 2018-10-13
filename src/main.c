#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"
#include "fonctions_reponses.h"

int main(int argc, char** argv){
  char * path = "ressources/45-1";
  if(argc == 2){
    path = argv[1];
  }
  struct tiling* tiles = loadTiling(path);
  solution_1(tiles);
  displayTiling(tiles);

  // For debuging purpose
  printf("Press ENTER key to Continue\n");  
  getchar(); 
  return 0;
}
