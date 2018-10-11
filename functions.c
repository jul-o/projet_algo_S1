#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"

#define MAX_SIZE_LINE 200

void get_dimensions(char* l, int* lines, int* cols){
  int nb_char_lines = 0;
  int nb_char_cols = 0;
  int i = 0;
  for(; l[i] != ' '; i++){
    if(!isdigit(l[i])){
      //verification qu'on a bien un chiffre
      printf("[ERREUR] : le nombre de lignes doit être uniquement composé de chiffres : %d", l[i]);
      return;
    }
    nb_char_lines++;
  }i++;
  for(; l[i] != '\0' && l[i] != '\n'; i++){
    if(!isdigit(l[i])){
      //verification qu'on a bien un chiffre
      printf("[ERREUR] : le nombre de colonnes doit être uniquement composé de chiffres : %d", l[i]);
      return;
    }
    nb_char_cols++;
  }
  i = 0;
  char* str_lines = malloc(nb_char_lines+1);
  char* str_cols = malloc(nb_char_cols+1);
  for(; l[i] != ' '; i++){
    str_lines[i] = l[i];
  }
  i++;
  int j=0;
  for(; l[i] != '\0'; i++){
    str_cols[j++] = l[i];
  }
  *lines = atoi(str_lines);
  *cols = atoi(str_cols);
}

struct tiling* loadTiling(char * filePath){
  // Open the file
  FILE * f;
  f = fopen(filePath, "r");

  if(f==NULL){
    printf("Error reading file %s", filePath);
    exit(EXIT_FAILURE);
  }

  // The first lines are the tiling size
  // The temp is there to read all lines to simplify code later (temp value should be null)
  int lines, columns;
  // TODO : utiliser une autre méthode pour interdire les mauvais caractères
  char* line0 = NULL;
  size_t len=0;
  getline(&line0, &len, f);
  get_dimensions(line0, &lines, &columns);
  // fscanf(f, "%d %d %s", &lines, &columns, temp);

  if(lines <= 0){
    printf("[ERREUR] : le nombre de lignes doit être supérieur à 0 \n");
    exit(EXIT_FAILURE);
  }
  if(columns <= 0){
    printf("[ERREUR] : le nombre de colonnes doit être supérieur à 0 %d\n", columns);
    exit(EXIT_FAILURE);
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
      if(buffer[i] != '0' && buffer[i] != '1'){
        printf("[ERREUR] : le dallage ne doit être composé que de '0' et de '1'\n");
        exit(EXIT_FAILURE);
      }
      current = buffer[i] - '0'; // Simple trick to convert the char to int
      tiling[currentLine][currentColumn] = current;
      currentColumn++;
    }
    //vérification de la taille de la ligne
    if(currentColumn != columns){
      printf("[ERREUR] : ligne de mauvaise taille (ligne %d)", currentLine);
      exit(EXIT_FAILURE);
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

void displayTiling(Tiling * t){
  for(int i=0; i<t->lines; i++){
    for(int j=0; j<t->columns; j++){
      if(t->values[i][j] == 0) printf("0");
      if(t->values[i][j] == 1) printf("1");
    }
    printf("\n");
  }
}