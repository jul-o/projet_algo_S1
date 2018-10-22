#include "fonctions_reponses.h"

void solution1(Tiling* tiles) {
    int max = 0;
    int x0_max = 0, y0_max = 0;
    int x1_max = 0, y1_max = 0;

    int noBlackFound;

    // x0, y0 is the top left corner
    for (int y0 = 0; y0 < tiles->lines; y0++) {
        for (int x0 = 0; x0 < tiles->columns; x0++) {
            // x1, y1 are the max values that the reactangle can take
            for (int y1 = y0; y1 < tiles->lines; y1++) {
                for (int x1 = x0; x1 < tiles->columns; x1++) {
                    noBlackFound = 1;
                    // ix, iy are the right bottom corner
                    for (int ix = x0; ix <= x1 && noBlackFound; ix++) {
                        for (int iy = y0; iy <= y1 && noBlackFound; iy++) {
                            if (tiles->values[iy][ix] == 1) noBlackFound = 0;
                        }
                    }

                    if (noBlackFound) {
                        // x0 and y0 should be always bigger so no real need no use abs()
                        int area = (x1 - x0 + 1) * (y1 - y0 + 1);
                        if (area > max) {
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
void solution2(Tiling* tiles) {
    // x0, y0 : top left corner
    int max = 0;
    int x0_max = 0, y0_max = 0;
    int x1_max = 0, y1_max = 0;

    for (int x0 = 0; x0 < tiles->columns; x0++) {
        for (int y0 = 0; y0 < tiles->lines; y0++) {
            // x1, y1 : current bottom right corner position
            int x1 = x0;
            int y1 = y0;

            int max_x = tiles->columns - 1;

            // TODO : fix inversion cols/rows
            while (y1 < tiles->lines && tiles->values[y1][x1] != 1) {
                while (x1 < tiles->columns && tiles->values[y1][x1] != 1 && x1 < max_x) x1++;
                if (tiles->values[y1][x1] == 1) x1--;  // If the last one was a 1, don't count it

                int area = abs(x1 - x0 + 1) * abs(y1 - y0 + 1);
                if (area > max) {
                    max = area;
                    x0_max = x0;
                    y0_max = y0;
                    x1_max = x1;
                    y1_max = y1;
                }

                max_x = x1;

                y1++;
                x1 = x0;
            }
        }
    }

    printf("MAX FOUND : \n");
    printf("x0 : %d , y0 : %d     x1 : %d , y1 : %d \n", x0_max, y0_max, x1_max, y1_max);
    printf("SIZE : %d \n", max);
}

void solution3(Tiling* tiles) {
    int x0_max = 0;
    int x1_max = 0;
    int y0_max = 0;
    int y1_max = 0;
    int max = 0;

    int heights[tiles->columns];
    for (int i = 0; i < tiles->lines; i++) {
        // Step 1 . Calcul des hauteurs
        for (int j = 0; j < tiles->columns; j++) {
            if (i == 0) heights[j] = 0;

            if(tiles->values[i][j] == 0) heights[j]++;
            else heights[j] = 0;
        }

        // Step 2 . On regarde quel rectangle sont faisable avec le tableau de hauteurs
        for (int j = 0; j < tiles->columns; j++) {
            if (tiles->values[i][j] != 0) continue;
            
            // Les y coords sont facilement trouvable avec le tableau de hauteur : 
            int y0 = i - heights[j] + 1;
            int y1 = i;

            // Maintenant il faut trouver les coords x le plus grand possible
            int x0 = j;
            int x1 = j;
            while(x1 < tiles->columns - 1 && heights[x1+1] >= heights[j]) x1++;
            while(x0 > 0 && heights[x0-1] >= heights[j]) x0--;

            // Comparons l'air de ce rectangle avec l'air du plus grand trouvé
            int area = (x1 - x0 + 1) * (y1 - y0 + 1);
            if ( area > max ) {
                max = area;
                x0_max = x0;
                y0_max = y0;
                x1_max = x1;
                y1_max = y1;
            }
        }
    }

    printf("MAX FOUND : \n");
    printf("x0 : %d , y0 : %d     x1 : %d , y1 : %d \n", x0_max, y0_max, x1_max, y1_max);
    printf("SIZE : %d \n", max);
}

void solution4(Tiling* tiles) {
    int x0 = 0;
    int x1 = 0;
    int y0 = 0;
    int y1 = 0;
    int heights[tiles->columns];
    int max_size = 0;
    Node* stack = createStack();
    for (int i = 0; i < tiles->lines; i++) {
        for (int j = 0; j < tiles->columns; j++) {
            // initializing the heights' array's cells to 0
            if (i == 0) heights[j] = 0;

            int val = tiles->values[i][j];
            if (val == 0) heights[j]++;
            else heights[j] = 0;

            checkOpenRectangles(tiles, &stack, i, j, heights, &max_size, &x0, &y0, &x1, &y1);
        }
    }
    printf("MAX : %d\n%d:%d, %d:%d\n", max_size, x0, y0, x1, y1);
}

/**
 * params :
     * tiles : the tiles' struct
     * stack : stack containing the open rectangles
     * i : current line
     * j : current column
     * heights : the heights' array
     * max_size : max rectangle yet's size
     * x0, y0, x1, y1 : max rectangle yet's coords
 */
void checkOpenRectangles(Tiling* tiles, Node** stack, int i, int j, int* heights, int* max_size, int* x0, int* y0, int* x1, int* y1) {
    if ((isStackEmpty(*stack) && tiles->values[i][j] == 0) || (!isStackEmpty(*stack) && readStack(*stack).h < heights[j])) {
        // adding a rectangle to the satck
        open_rect r;
        r.h = heights[j];
        r.x = j;
        pushStack(stack, r);
    }
    // int openRectangleOk = isStackEmpty(*stack);
    open_rect curr_rec;
    if (!isStackEmpty(*stack))
        curr_rec = readStack(*stack);
    while (!isStackEmpty(*stack) && (curr_rec.h > heights[j] || j == tiles->columns - 1)) {
        // unstack the current rectangle and check if it's bigger than the biggest rectangle met yet
        int x0t = curr_rec.x;
        int x1t;
        int y0t = i - curr_rec.h + 1;
        int y1t = i;
        if (j != tiles->columns - 1) {
            // don't count the current col : the rectangle has met a black tile
            x1t = j - 1;
        } else {
            // end of line : count the current col
            x1t = j;
        }
        // calculate the width and height of the current rectangle
        int w = x1t - x0t + 1;
        int h = y1t - y0t + 1;
        // check if the current rectangle is bigger than the biggest one met
        if (w * h > *max_size) {
            *max_size = w * h;
            *x0 = x0t;
            *y0 = y0t;
            *x1 = x1t;
            *y1 = y1t;
        }
        // printf("x0 : %d, x1 : %d, y0 : %d, y1 : %d\n", x0t, x1t, y0t, y1t);
        popStack(stack);
        if (!isStackEmpty(*stack))
            curr_rec = readStack(*stack);
    }
}