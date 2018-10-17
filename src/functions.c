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

  // Get the tiling size form the file
  int lines, columns;
  readTilingDimensions(f, &lines, &columns);

  // Then create the tiling
  int ** tiling = malloc(lines * sizeof(int*));
  for(int i = 0; i < lines; i++) tiling[i] = malloc(columns * sizeof(int));

  readTiling(f, &lines, &columns, tiling);

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

void readTiling(FILE * f, int * lines, int * columns, int ** tiling){
  // Finaly read the file and fill the tiling
  char buffer[MAX_SIZE_LINE];
  int current;
  int lineCounter=0;
  int columnCounter=0;
  while(fgets(buffer, MAX_SIZE_LINE, f) != NULL){
    // Check lines sizes (max)
    if(lineCounter >= *lines){
      printf("loadTiling ERROR : Too much lines in the files \n"); 
      return;
    }

    columnCounter=0;
    for(int i=0; i < strlen(buffer)-1; i++){
      if(buffer[i] != '0' && buffer[i] != '1'){
        printf("loadTiling ERROR : unexpected character in file (should be only 0 and 1) \n");
        return;
      }
      current = buffer[i] - '0'; // Simple trick to convert the char to int
      tiling[lineCounter][columnCounter] = current;
      columnCounter++;
    }

    // Checking column size (min+max)
    if(columnCounter != *columns){
      printf("loadTiling ERROR : bad column size for line : %d \n", lineCounter);
      return;
    }

    lineCounter++;
  }

  // Check lines sizes (min)
  if(lineCounter != *lines){
    printf("loadTiling ERROR : Not enough lines \n");
    return;
  }
}

void displayTiling(Tiling * t){
  for(int i=0; i<t->lines; i++){
    for(int j=0; j<t->columns; j++){
      if(t->values[i][j] == 0) printf("0");
      else if(t->values[i][j] == 1) printf("1");
      else printf("X");
    }
    printf("\n");
  }
}