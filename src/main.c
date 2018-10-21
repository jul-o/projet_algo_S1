#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "functions.h"
#include "fonctions_reponses.h"
#include "./test/stack_test.c"


// Param intéréssant pour tester : 
// - pourcentage de tile noirs
// - nb de lignes
// - nb de colonnes
void perfTester(){
  int lines = 50;
  int columns = 50;
  int ratio = 10;
  
  FILE * f;
  f = fopen("perf.res", "w");
  if(f == NULL){
    printf("Error opening file perf.res");
    return;
  }

  double res1 = testSolution(solution1);
  double res2 = testSolution(solution2);
  double res3 = testSolution(solution3);
  double res4 = testSolution(solution4);

  fprintf(f, "nbLignes,nbCols,ratio,solution1,solution2,solution3,solution4\n");
  fprintf(f, "%d,%d,%d,%d,%d,%d,%d", lines, columns, ratio, res1, res2, res3, res4);

  fclose(f);
}

double testSolution(void (*f)(Tiling *)){
  clock_t start, end;
  start = clock();
  Tiling * tiling = randomTiling(500,500,20);
  (*f)(tiling);
  end = clock();
  double res =  ((double) (end - start)) / CLOCKS_PER_SEC;
  return res;
}

int main(int argc, char** argv){
  char * path = "ressources/45-1";
  Tiling * tiles = loadTiling(path);

  perfTester();

  // solution1(tiles);
  // solution2(tiles);
  // solution3(tiles);
  // solution4(tiles);

  // displayTiling(tiles);

  // testStack();





  // For debuging purpose
  printf("Press ENTER key to Continue\n");  
  getchar(); 
  return 0;
}

