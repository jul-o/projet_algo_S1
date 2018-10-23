#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "functions.h"
#include "fonctions_reponses.h"
#include "./test/stack_test.c"
#include "./test/loading_test.c"


double testSolution(void (*f)(Tiling *), int lines, int columns, int ratio){
  clock_t start, end;
  Tiling * tiling = randomTiling(lines,columns,ratio);
  // displayTiling(tiling);
  start = clock();
  (*f)(tiling);
  end = clock();
  double res =  ((double) (end - start)) / CLOCKS_PER_SEC;
  
  printf("ELASPED TIME : %lf \n", res*1000); // * 1000 to get MS

  return res;
}

int main(int argc, char** argv){
  char * path = "ressources/wtf";
  Tiling * tiles = loadTiling(path);
  displayTiling(tiles);
  solution3(tiles);

  // testSolution(solution4, 50, 50, 20);
  // testSolution(solution4, 100, 100, 20);
  // testSolution(solution4, 150, 150, 20);
  // testSolution(solution4, 150, 150, 90);
  // testSolution(solution4, 250, 250, 20);
  // testSolution(solution4, 600, 600, 20);
  // testSolution(solution4, 600, 600, 90);
  // testSolution(solution4, 3000, 4000, 20);
  // testSolution(solution4, 5000, 6000, 20);
  // testSolution(solution3, 10000, 10000, 20);

  testSolution(solution4bis, 600, 600, 20);


  // For debuging purpose
  printf("Press ENTER key to Continue\n");  
  getchar(); 
  return 0;
}

