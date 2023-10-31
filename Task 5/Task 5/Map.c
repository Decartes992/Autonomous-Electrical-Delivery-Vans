
#include "Map.h"


void move_cursor(int row, int col) {
    /* Move cursor to specified row and column */
    COORD coord;
    coord.X = col;
    coord.Y = row;
    /* Windows function to position cursor */
    SetConsoleCursorPosition(Console, coord);
}

void draw_box(int ulr, int ulc, int scale) {
    /*
     - Draw bot at ulr, ulc
     - Height and width are "scaled"
    */
    int rc; /* Row count */
    int cc; /* Column count */

    /* Top row */
    move_cursor(ulr, ulc);
    DISP(UL);
    for (cc = 0; cc < scale + Hoffset; cc++)
        DISP(HBAR);
    DISP(UR);

    /* Verticals */
    for (rc = 1; rc < scale; rc++) {
        move_cursor(ulr + rc, ulc);
        DISP(VBAR);
        move_cursor(ulr + rc, ulc + scale + Voffset);
        DISP(VBAR);
    }

    /* Bottom row */
    move_cursor(ulr + scale, ulc);
    DISP(LL);
    for (rc = 0; rc < scale + Hoffset; rc++)
        DISP(HBAR);
    DISP(LR);
}


void draw_map(int street, int avenue) {

    int y1 = 7;
    int y2 = y1 + 1;
    int x = 32;
    int i, j;
    int y3 = 5;
    int x3 = 20;
    int p, k;

    int marker = 1;

    for (p = 0; p < street; p++) {

        x3 = 20;

        for (k = 0; k < avenue; k++) {
            draw_box(y3, x3, 5);

            buildingz[marker].B_address.Y = (y3 + 1); // THE Y VALUE OF THE BUILDING
            buildingz[marker].B_address.X = (x3 + Hoffset); // THE X VALUE OF THE BUILDING

            buildingz[marker].B_Number = marker;

            move_cursor(buildingz[marker].B_address.Y, buildingz[marker].B_address.X);

            printf("%d", buildingz[marker].B_Number);
            x3 = x3 + buildoffset;
            marker++;
        }
        y3 = y3 + 10;
    }
}

