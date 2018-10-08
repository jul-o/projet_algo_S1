#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

#define MAX_SIZE_LINE 200

struct tiling* loadTiling(char * filePath){
  // Open the file
  FILE * f;
  f = fopen(filePath, "r");

  if(f==NULL){
    printf("Error reading file %s", filePath);
    return NULL;
  }

  // The first lines are the tiling size
  // The temp is there to read all lines to simplify code later (temp value should be null)
  int lines, columns;
  char * temp = NULL;
  // TODO : utiliser une autre méthode pour interdire les mauvais caractères
  fscanf(f, "%d %d %s", &lines, &columns, temp);

  if(lines <= 0){
    printf("le nombre de lignes doit être supérieur à 0 \n");
    return NULL;
  }
  if(columns <= 0){
    printf("le nombre de colonnes doit être supérieur à 0 %d\n", columns);
    return NULL;
  }

  // bool tiling [lines][columns];
  bool** tiling = malloc(sizeof(int*)*columns);
  for(int i = 0; i < columns; i++){
    tiling[i] = malloc(sizeof(int)*lines);
  }
  // memset(tiling, false, sizeof(tiling[0][0]) * lines * columns); Not useful to have a default value ?

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
    //vérification de la taille de la ligne
    if(currentColumn != columns){
      printf("Erreur : ligne de mauvaise taille (ligne %d)", currentLine);
      return NULL;
    }
    currentLine++;
  }

  struct tiling* res = malloc(sizeof(tiling));
  res->lines = lines;
  res->columns = columns;
  res->values = tiling;


  fclose(f);
  return res;
}

// void displayTiling(bool **, )
