#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "functions.h"

int main(int argc, char** argv){
  char * path = "ressources/45-1";
  struct tiling* test = loadTiling(path);
  return 0;
}
