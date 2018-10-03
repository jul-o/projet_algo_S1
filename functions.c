#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void get_dimensions(char* buffer, int* i_width, int* i_height){
  long i = 0;
  int size_w = 0;
  int size_h = 0;
  while(buffer[i] != ' '){
    size_w++;
    i++;
  }
  i++;
  while(buffer[i] != '\n'){
    size_h++;
    i++;
  }

  char* width = malloc(size_w);
  char* height = malloc(size_h);
  i = 0;
  long j = 0;
  while(buffer[i] != ' '){
    width[j] = buffer[i];
    i++;
    j++;
  }
  width[j] = '\0';
  i++;
  j = 0;
  while(buffer[i] != '\n'){
    height[j] = buffer[i];
    i++;
    j++;
  }
  height[j] = '\0';

  *i_width = atoi(width);
  *i_height = atoi(height);
}

void read_files(argv){
  //verifier 1 argument et bien un fichier

  char* buffer = 0;
  long length;
  char* filename = argv[1];
  FILE* f = fopen(filename, "r");
  if(f){
    fseek(f, 0, SEEK_END);
    length = ftell (f);
    fseek (f, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
      fread (buffer, 1, length, f);
    }
    fclose (f);
  }

  if(buffer){
    int i_width;
    int i_height;
    get_dimensions(buffer, &i_width, &i_height);

    printf("%i, %i", i_width, i_height);



    /*for(long i=0;i<length;i++){
      printf("%c", buffer[i]);
      if(buffer[i] == '\n'){
        printf("*****");
      }
    }*/
}