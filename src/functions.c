#define _GNU_SOURCE
#include "functions.h"

#define MAX_SIZE_LINE 200

struct tiling* loadTiling(char * filePath){
  // Open the file
  FILE * f;
  f = fopen(filePath, "r");

  if(f==NULL){
    printf("Error reading file %s", filePath);
    exit(EXIT_FAILURE);
  }

  // Get the tiling sizz form the file
  int lines, columns;
  readTilingDimensions(f, &lines, &columns);

  // Then create the tiling
  int** tiling = malloc(sizeof(int*)*columns);
  for(int i = 0; i < columns; i++) tiling[i] = malloc(sizeof(int)*lines);
  
  // Finaly read the file and fill the tiling
  char buffer[MAX_SIZE_LINE] = "";
  int current;
  int currentLine=0;
  int currentColumn=0;
  int i;
  while(fgets(buffer, MAX_SIZE_LINE, f) != NULL){
    currentColumn=0;
    for(i=0; i < strlen(buffer)-1; i++){
      if(buffer[i] != '0' && buffer[i] != '1'){
        printf("[ERREUR] : le dallage ne doit être composé que de '0' et de '1'\n");
        return NULL;
      }
      current = buffer[i] - '0'; // Simple trick to convert the char to int
      tiling[currentLine][currentColumn] = current;
      currentColumn++;
    }
    // Checking lines size while reading
    if(currentColumn != columns){
      printf("[ERREUR] : ligne de mauvaise taille (ligne %d)", currentLine);
      return NULL;
    }
    currentLine++;
  }

  fclose(f);

  Tiling * res = malloc(sizeof(tiling));
  res->lines = lines;
  res->columns = columns;
  res->values = tiling;

  return res;
}

void readTilingDimensions(FILE * f, int * lines, int * columns){
  char* line = NULL;
  size_t len=0;
  getline(&line, &len, f);
  int readed = sscanf(line, "%d %d", lines, columns);
  if(readed < 2){
    printf("Error : The dimensions in the file are incorrect.");
    exit(1);
  }
}

void displayTiling(Tiling * t){
  for(int i=0; i<t->lines; i++){
    for(int j=0; j<t->columns; j++){
      if(t->values[i][j] == 0) printf("0");
      if(t->values[i][j] == 1) printf("1");
    }
    printf("\n");
  }
}