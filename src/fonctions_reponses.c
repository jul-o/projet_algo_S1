#include "fonctions_reponses.h"
#include <stdbool.h>
void solution_1(struct tiling* tiles){
  /**
  rectangles de hauteur 1 puis 2 puis ... puis height
  */
  int width = 0;
  int height = 0;
  for(int y0 = 0; y0 <= tiles->lines; y0++){
    for(int x0 = 0; x0 < tiles->columns; x0++){
      for(int y1 = y0; y1 < tiles->lines; y1++){
        for(int x1 = x0; x1 < tiles->columns; x1++){
          bool blanc = true;
          for(int ix = x0; ix <= x1&&blanc; ix++){
            for(int iy = y0; iy <= y1&&blanc; iy++){
              if(tiles->values[ix][iy] == true){
                blanc = false;
              }
            }
          }
          if(blanc){
            int w = x1-x0+1;
            int h = y1-y0+1;
            if(w*h > width*height){
            printf("WIDTH : %i\nHEIGHT : %i\nx0: %i, x1: %i\ny0: %i, y1: %i\n", w, h, x0, x1, y0, y1);
              width = w;
              height = h;
            }
          }
        }
      }
    }
  }
  printf("WIDTH : %i\nHEIGHT : %i\n", width, height);
}
