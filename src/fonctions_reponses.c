#include "fonctions_reponses.h"

void solution1(Tiling * tiles){
    int max = 0;
    int x0_max=0, y0_max=0;
    int x1_max=0, y1_max=0;

    int noBlackFound;

    // x0, y0 is the top left corner
    for(int y0 = 0; y0 < tiles->lines; y0++){
        for(int x0 = 0; x0 < tiles->columns; x0++){
            // x1, y1 are the max values that the reactangle can take
            for(int y1 = y0; y1 < tiles->lines; y1++){
                for(int x1 = x0; x1 < tiles->columns; x1++){

                    noBlackFound = 1;
                    // ix, iy are the right bottom corner
                    for(int ix = x0; ix <= x1 && noBlackFound; ix++){
                        for(int iy = y0; iy <= y1 && noBlackFound; iy++){
                            if(tiles->values[iy][ix] == 1) noBlackFound = 0;
                        }
                    }

                    if(noBlackFound){
                        // x0 and y0 should be always bigger so no real need no use abs()
                        int area = (x1-x0+1) * (y1-y0+1);
                        if(area > max){
                            max = area;
                            x0_max = x0;
                            y0_max = y0;
                            x1_max = x1;
                            y1_max = y1;
                        }
                    }
                }
            }
        }
    }

    printf("MAX FOUND : \n");
    printf("x0 : %d , y0 : %d     xm : %d , ym : %d \n", x0_max, y0_max, x1_max, y1_max);
    printf("SIZE : %d \n", max);
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

    for(int x0=0; x0 < tiles->columns; x0++){
        for(int y0=0; y0 < tiles->lines; y0++){
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

void solution3(Tiling* tiles) {
    int x0 = 0;
    int x1 = 0;
    int y0 = 0;
    int y1 = 0;
    int hauteurs[tiles->columns];
    int max_size = 0;
    for (int i = 0; i < tiles->lines; i++) {
        for (int j = 0; j < tiles->columns; j++) {
            // initialisation des hauteurs à 0
            if (i == 0)
                hauteurs[j] = 0;

            int val = tiles->values[i][j];
            if (val == 0)
                hauteurs[j]++;
            else
                hauteurs[j] = 0;
            // évaluation du plus grand rectangle de bord bas i
        }
        for (int l = 0; l < tiles->columns; l++) {
            int width = 1;
            // initializing the current rectangle coords
            int x0curr = l;
            int x1curr = l;
            int y0curr = i - hauteurs[l] + 1;
            int y1curr = i;
            if (tiles->values[i][l] == 0) {
                for (int k = l + 1; k < tiles->columns; k++) {
                    if (hauteurs[k] >= hauteurs[l]) {
                        width++;
                        // updating the rectangle's right side coord
                        x1curr = k;
                    } else
                        break;
                }
                for (int k = l - 1; k >= 0; k--) {
                    if (hauteurs[k] >= hauteurs[l]) {
                        width++;
                        // updating the rectangle's left side coord
                        x0curr = k;
                    } else
                        break;
                }
                // updating the max rectangle and its coords if it is bigger than the previous one
                if (width * hauteurs[l] > max_size) {
                    max_size = width * hauteurs[l];
                    x0 = x0curr;
                    x1 = x1curr;
                    y0 = y0curr;
                    y1 = y1curr;
                }
            }
        }
    }
    printf("TAILLE : %i\nx0 : %i, x1 : %i\ny0 : %i, y1 : %i\n", max_size, x0, x1,
           y0, y1);
}
