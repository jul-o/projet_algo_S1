#include "fonctions_reponses.h"

void solution1(Tiling * tiles){
  
  int maxWidth = 0;
  int maxHeight = 0;

  for(int y0 = 0; y0 < tiles->lines; y0++){
    for(int x0 = 0; x0 < tiles->columns; x0++){
      for(int y1 = y0; y1 < tiles->lines; y1++){
        for(int x1 = x0; x1 < tiles->columns; x1++){

          int blanc = 1;
          for(int ix = x0; ix <= x1 && blanc; ix++){
            for(int iy = y0; iy <= y1 && blanc; iy++){
              if(tiles->values[ix][iy] == 1){
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
// Dès qu'on réduit la largeur on se rapelle du dernier coin, qui pourra servir comme coin inférieur droit
// A la fin on compare la surface qu'on obtient avec tous les coins inférieurs droits, et celui qui permet la plus grande surface
// void solution2(Tiling * tiles){

//   // x0, y0 : top left corner
//   for(int x0=0; x0 < tiles->lines; x0++){
//     for(int y0=0; y0 < tiles->columns; y0++){

//       // x1, y1 : current bottom right corner
//       int x1 = x0;
//       int y1 = y1;

//       while(tiles->values[x1][y1] != true && x1 < tiles->lines - 1) x1++;
//       printf("%d \n", &x1);
//     }
//   }
// }

