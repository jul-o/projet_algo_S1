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
// Dès qu'on a trouver la largeur max, on regarde la taille du rectangle en utilisant le coin inférieur droit trouvé
// Si sa surface est plus grande que tous ceux trouvé auparavant, on le retient comme candidat
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

      int max_x = tiles->columns-1;

      // TODO : fix inversion cols/rows
      while(y1 < tiles->lines && tiles->values[y1][x1] != 1){
        while(x1 < tiles->columns  && tiles->values[y1][x1] != 1 && x1 < max_x) x1++;
        if(tiles->values[y1][x1] == 1) x1--; // If the last one was a 1, don't count it

        int area = abs(x1 - x0 + 1) * abs(y1 - y0 + 1);
        if(area>max){
          max = area;
          x0_max = x0;
          y0_max = y0;
          x1_max = x1;
          y1_max = y1;
        }

        max_x = x1;

        y1++;
        x1=x0;
      }
    }
  }

  printf("MAX FOUND : \n");
  printf("x0 : %d , y0 : %d     xm : %d , ym : %d \n", x0_max, y0_max, x1_max, y1_max);
  printf("SIZE : %d \n", max);
}

