#include "fonctions_reponses.h"

void solution1(Tiling* tiles) {
    // x0, y0 : top left corner
    // x1, y1 : bottom left corner
    int max = 0;
    int x0_max = 0, y0_max = 0;
    int x1_max = 0, y1_max = 0;

    int noBlackFound;
    for (int y0 = 0; y0 < tiles->lines; y0++) {
        for (int x0 = 0; x0 < tiles->columns; x0++) {
            for (int y1 = y0; y1 < tiles->lines; y1++) {
                for (int x1 = x0; x1 < tiles->columns; x1++) {
                    noBlackFound = 1;
                    // ix, iy are the current right bottom corner
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
    // x1, y1 : bottom left corner
    int max = 0;
    int x0_max = 0, y0_max = 0;
    int x1_max = 0, y1_max = 0;

    for (int x0 = 0; x0 < tiles->columns; x0++) {
        for (int y0 = 0; y0 < tiles->lines; y0++) {
            // x1, y1 : current bottom right corner position
            int x1 = x0;
            int y1 = y0;

            int max_x = tiles->columns - 1;
            //
            while (y1 < tiles->lines && tiles->values[y1][x1] != 1) {
                // Regardons jusqu'à ou peut aller sur la droite sans tomber sur une case ET sans dépasser la largeur de la dernière itération
                while (x1 < tiles->columns && tiles->values[y1][x1] != 1 && x1 < max_x) x1++;
                if (tiles->values[y1][x1] == 1) x1--;  // If the last one was a 1, don't count it

                // Comparons l'air de ce rectangle avec l'air du plus grand trouvé
                int area = (x1 - x0 + 1) * (y1 - y0 + 1);
                if (area > max) {
                    max = area;
                    x0_max = x0;
                    y0_max = y0;
                    x1_max = x1;
                    y1_max = y1;
                }

                // Set the max size in function of the max x found, go on the next line and reset the x1 position : 
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

void solution4(Tiling * tiles){
    // Res : 
    int x0_max = 0;
    int x1_max = 0;
    int y0_max = 0;
    int y1_max = 0;
    int max = 0;

    int heights[tiles->columns];
    Node* stack = createStack();
    for(int i=0; i < tiles->lines; i++){
        // Step 1 . Calcul des hauteurs
        for (int j = 0; j < tiles->columns; j++) {
            if (i == 0) heights[j] = 0;

            if(tiles->values[i][j] == 0) heights[j]++;
            else heights[j] = 0;
        }

        // Step 2 . On check les différents rectangles
        int currentHeight = 0;
        int maxHeight = 0;

        int mustPopAll=0;
        int mustPopHigherRect=0;
        int popPosition=0;
        open_rect  * r;
        for(int j = 0; j < tiles -> columns; j++){
            mustPopAll=0;
            mustPopHigherRect=0;
            currentHeight = heights[j];

            if (tiles->values[i][j] != 0){
                popPosition = j-1;
                mustPopAll = 1;
                maxHeight = 0;
            }
            else if(currentHeight > maxHeight){
                r = malloc(sizeof(open_rect));
                r->x = j; r->h  = currentHeight;
                pushStack(&stack, r);
                maxHeight = currentHeight;
            }
            else if(currentHeight < maxHeight){
                // popPosition = j-1;
                maxHeight = currentHeight;
                mustPopHigherRect = 1;
            }

            if(!mustPopAll && j == tiles->columns -1){
                mustPopAll = 1;
                popPosition = j;
            }

            if(mustPopHigherRect){
                int x0, x1;
                int y0, y1;

                open_rect * rect, * last;
                rect = readStack(stack);
                while(rect != NULL && rect->h > maxHeight){
                    x0 = rect->x; 
                    x1 = popPosition-1;
                    y0 =  i - rect->h + 1; 
                    y1 = i;

                    int area = (x1 - x0 + 1) * (y1 - y0 + 1);
                    if ( area > max ) {
                        max = area;
                        x0_max = x0;
                        y0_max = y0;
                        x1_max = x1;
                        y1_max = y1;
                    }

                    last = rect;
                    popStack(&stack);
                    rect = readStack(stack);
                }

                if(last != NULL){
                    last->x = last->x;
                    last->h = currentHeight;
                    pushStack(&stack, last);
                }
            }

            if(mustPopAll){
                open_rect * rect;

                int x0, x1;
                int y0, y1;
                while(!isStackEmpty(stack)){
                    rect = readStack(stack);

                    x0 = rect->x; 
                    x1 = popPosition;
                    y0 =  i - rect->h + 1; 
                    y1 = i;
                    popStack(&stack);

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
        }
    }

    printf("MAX FOUND : \n");
    printf("x0 : %d , y0 : %d     x1 : %d , y1 : %d \n", x0_max, y0_max, x1_max, y1_max);
    printf("SIZE : %d \n", max);
}