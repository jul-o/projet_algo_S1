#include "fonctions_reponses.h"

void solution1(Tiling * tiles){
  
  int maxWidth = 0;
  int maxHeight = 0;

  for(int y0 = 0; y0 <= tiles->lines; y0++){
    for(int x0 = 0; x0 <= tiles->columns; x0++){
      for(int y1 = y0; y1 < tiles->lines; y1++){
        for(int x1 = x0; x1 < tiles->columns; x1++){

          int blanc = 1;
          for(int ix = x0; ix <= x1 && blanc; ix++){
            for(int iy = y0; iy <= y1 && blanc; iy++){
              if(tiles->values[iy][ix] == 1){
                blanc = 0;
              }
            }
          }

          if(blanc){
            int w = x1-x0+1;
            int h = y1-y0+1;
            if(w*h > maxWidth*maxHeight){
            printf("WIDTH : %i\nHEIGHT : %i\nx0: %i, x1: %i\ny0: %i, y1: %i\n", w, h, x0, x1, y0, y1);
              maxWidth = w;
              maxHeight = h;
            }
          }
        }
      }
    }
  }
  printf("WIDTH : %i\nHEIGHT : %i\n", maxWidth, maxHeight);
}



// Principe de l'algo : 
// (Info en plus du sujet)
// On parcours chaque case du dallage
// Pour chaque case du dallage, on regarde tous les plus grand rectangles qu'on puisse faire en utilisant la case de dallage actuel comme coin supérieur gauche
// Dès qu'on a trouver la largeur max, on se rapelle de ce point, il pourra servir comme coint inférieur droit
// A la fin on compare la surface qu'on obtient avec tous les coins inférieurs droits, et on garde celui qui permet la plus grande surface
void solution2(Tiling * tiles){

  // x0, y0 : top left corner
  int max = 0;
  int x0_max=0, y0_max=0;
  int x1_max=0, y1_max=0;

  for(int x0=0; x0 < 1; x0++){
    for(int y0=0; y0 < 1; y0++){

      // x1, y1 : current bottom right corner position
      int x1 = x0;
      int y1 = y0;

      int x_found[50]; // TODO : find better than 50
      int y_found[50];
      int nb_found=0;

      int max_x =  tiles->columns-1;

      // TODO : fix inversion cols/rows
      while(y1 < tiles->lines && tiles->values[x1][y1] != 1){
        while(x1 < tiles->columns  && tiles->values[x1][y1] != 1 && x1 < max_x) x1++;
        if(tiles->values[x1][y1] == 1) x1--; // If the last one was a 1, don't count it
        x_found[nb_found] = x1;
        y_found[nb_found] = y1;
        nb_found++;
        
        max_x = x1;

        y1++;
        x1=x0;
      }


      int v;
      for(int i=0; i < nb_found; i++){
        v = abs(x_found[i] - x0 + 1) * abs(y_found[i] - y0 + 1);
        if(v > max){  
          max = v;
          x0_max = x0;
          y0_max = y0;
          x1_max = x_found[i];
          y1_max = y_found[i];
        }
      }
    }
  }

  printf("MAX FOUND : \n");
  printf("x0 : %d , y0 : %d     xm : %d , ym : %d \n", x0_max, y0_max, x1_max, y1_max);
  printf("SIZE : %d \n", max);
}

void solution3(Tiling *tiles)
{
  int x0 = 0;
  int x1 = 0;
  int y0 = 0;
  int y1 = 0;
  int hauteurs[tiles->columns];
  int max_size = 0;
  for (int i = 0; i < tiles->lines; i++)
  {
    for (int j = 0; j < tiles->columns; j++)
    {
      // initialisation des hauteurs à 0
      if (i == 0)
        hauteurs[j] = 0;

      int val = tiles->values[i][j];
      if (val == 0)
        hauteurs[j]++;
      else
        hauteurs[j] = 0;
      int h = hauteurs[j];
      printf("%i", h);
      // évaluation du plus grand rectangle de bord bas i
      
      printf("\n");
    }
    for (int l = 0; l < tiles->columns; l++)
      {
        int width = 1;
        if (tiles->values[i][l] == 0)
        {
          for (int k = l + 1; k < tiles->columns; k++)
          {
            if (hauteurs[k] >= hauteurs[l])
            {
              width++;
            }
            else break;
          }
          for (int k = l - 1; k >= 0; k--)
          {
            if (hauteurs[k] >= hauteurs[l])
            {
              width++;
            }
            else break;
          }
          printf("WEED : %i, val : %i, size : %i\n", width, hauteurs[l], width * hauteurs[l]);
          if (width * hauteurs[l] > max_size)
          {
            max_size = width * hauteurs[l];
          }
        }
      }
  }
  printf("TAILLE : %i\n", max_size);
}
