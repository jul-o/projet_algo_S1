#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "functions.h"

#define MAX_SIZE_LINE 200

void loadTiling(char * filePath){
  // Open the file
  FILE * f;
  f = fopen(filePath, "r");

  if(f==NULL){
    printf("Error reading file %s", filePath);
    return;
  }

  // The first lines are the tiling size
  // The temp is there to read all lines to simplify code later (temp value should be null)
  int lines, columns;
  char * temp;
  fscanf(f, "%d %d %s", &lines, &columns, temp);

  bool tiling [lines][columns];
  // memset(tiling, false, sizeof(tiling[0][0]) * lines * columns); Not usefule to have a default value ?

  char buffer[MAX_SIZE_LINE] = "";
  int current;
  int currentLine=0;
  int currentColumn=0;
  int i;
  while(fgets(buffer, MAX_SIZE_LINE, f) != NULL){
    currentColumn=0;
    for(i=0; i < strlen(buffer)-1; i++){
      current = buffer[i] - '0'; // Simple trick to convert the char to int
      tiling[currentLine][currentColumn] = current;
      currentColumn++;
    }
    currentLine++;
  }

  fclose(f);
}

// void displayTiling(bool **, )