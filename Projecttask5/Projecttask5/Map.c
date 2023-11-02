/*MODULE: MAP
*
* WHAT IT DOES: THE MAP.H AND MAP.C FILES ACHIEVE THE PURPOSE OF DRAWING THE MAP
* AND STORING THE BUILDING LOCATION, PARKING LOCATION AND CHARGING LOCATION
*
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/



#include "Map.h"


void move_cursor(int row, int col) {
    /* Move cursor to specified row and column */
    COORD coord;
    coord.X = col;
    coord.Y = row;
    /* Windows function to position cursor */
    SetConsoleCursorPosition(Console, coord);
}



void draw_box(int ulr, int ulc, int urr, int urc) {
    /*
     - Draw bot at ulr, ulc
     - Height and width are "scaled"
    */
    int rc; /* Row count */
    int cc; /* Column count */
   // urr = urr - ulr;
    urc = urc - ulc;


    /* Top row */
    move_cursor(ulr, ulc);
    DISP(UL);
    for (cc = 0; cc < urc; cc++)
        DISP(HBAR);
    DISP(UR);

    /* Verticals */
    for (rc = 1; rc < urr - ulr; rc++) {
        move_cursor(ulr + rc, ulc);
        DISP(VBAR);
        move_cursor(ulr + rc, ulc + urc + 1); //THE CURSOR NEEDS TO BE INCREMENTED BY 1 IN THE X DIRECTION TO DRAW PROPORTIONAL BOX
        DISP(VBAR);
    }

    /* Bottom row */
    move_cursor(urr, ulc);
    DISP(LL);
    for (rc = 0; rc < urc; rc++)
        DISP(HBAR);
    DISP(LR);
}


void draw_map(int street, int avenue) {

    int avenuecounter, streetcounter, i = 0;
    int Building_Upper_Left_Y = ULY_of_first_building;
    int Building_Upper_Left_X = ULX_of_first_building;
    int marker = 0;



    for (avenuecounter = 0; avenuecounter < avenue; avenuecounter++) { // COUNTER FOR DRAWING BUILDINGS VERTICALLY

        Building_Upper_Left_X = ULX_of_first_building;

        for (streetcounter = 0; streetcounter < street; streetcounter++) { // COUNTER FOR DRAWING BUILDINGS HORIZONTALLY
            draw_box(Building_Upper_Left_Y, Building_Upper_Left_X,  (Building_Upper_Left_Y+ Width_of_building), (Building_Upper_Left_X + Length_of_building));
            marker++;

            buildingz[marker].B_address.Y = (Building_Upper_Left_Y); // THE Y VALUE OF THE BUILDING
            buildingz[marker].B_address.X = (Building_Upper_Left_X); // THE X VALUE OF THE BUILDING

            buildingz[marker].B_Number = marker;
            i = 1;
            move_cursor(buildingz[marker].B_address.Y + i, buildingz[marker].B_address.X + buildingnumberoffset);
            printf("%d", buildingz[marker].B_Number);
            i++;
            move_cursor(buildingz[marker].B_address.Y + i, buildingz[marker].B_address.X + parkingandchargingnumberoffset);
            printf("P:");
            buildingz[marker].P_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE PARKING
            buildingz[marker].P_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE PARKING

            i++;
            move_cursor(buildingz[marker].B_address.Y + i, buildingz[marker].B_address.X + parkingandchargingnumberoffset);
            printf("C:");

            buildingz[marker].C_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE CHARGING
            buildingz[marker].C_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE CHARGING

            buildingz[marker].numberofaedvscharging = ZERO;
            buildingz[marker].numberofaedvsparked = ZERO;


            Building_Upper_Left_X = Building_Upper_Left_X + Street_length;
        }
        Building_Upper_Left_Y = Building_Upper_Left_Y+ Avenue_length;
    }
    draw_box(buildingz[1].B_address.Y + outerboxulroffset, buildingz[1].B_address.X + outerboxulcoffset, buildingz[marker].B_address.Y + outerboxurroffset, buildingz[marker].B_address.X + outerboxurcoffset);

}

/*FUNCTION TO POPULATE BUILDINGZ ARRAY WITHOUT DRAWING THE MAP*/
void dud_map(int street, int avenue) {

    int avenuecounter, streetcounter, i = 0;
    int Building_Upper_Left_Y = ULY_of_first_building;
    int Building_Upper_Left_X = ULX_of_first_building;
    int marker = 0;



    for (avenuecounter = 0; avenuecounter < avenue; avenuecounter++) {

        Building_Upper_Left_X = ULX_of_first_building;

        for (streetcounter = 0; streetcounter < street; streetcounter++) {
            marker++;

            buildingz[marker].B_address.Y = (Building_Upper_Left_Y); // THE Y VALUE OF THE BUILDING
            buildingz[marker].B_address.X = (Building_Upper_Left_X); // THE X VALUE OF THE BUILDING

            buildingz[marker].B_Number = marker;
            i = 1;
         
            i++;
          
            buildingz[marker].P_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE PARKING
            buildingz[marker].P_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE PARKING

            i++;
           

            buildingz[marker].C_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE CHARGING
            buildingz[marker].C_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE CHARGING

            buildingz[marker].numberofaedvscharging = ZERO;
            buildingz[marker].numberofaedvsparked = ZERO;


            Building_Upper_Left_X = Building_Upper_Left_X + Street_length;
        }
        Building_Upper_Left_Y = Building_Upper_Left_Y + Avenue_length;
    }
}