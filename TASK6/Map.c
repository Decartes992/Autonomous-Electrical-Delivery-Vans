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
#define ROWS 25
#define COLUMNS 25
Cell map[ROWS][COLUMNS]; // Global map

// Function prototypes (these should be in Map.h)
void draw_colored_box(int upperLeftX, int upperLeftY, char* boxLabel, int boxColor);
void draw_map(int numStreets, int numAvenues);

// Function to determine if a cell is on the edge of the map
int is_edge(int row, int col) {
    return row == 0 || row == ROWS - 1 || col == 0 || col == COLUMNS - 1;
}

// Function to initialize the map with cell statuses
void initialize_map() {
    // Loop to assign statuses to each cell in the map
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (is_edge(i, j)) {
                map[i][j].status = CORNER;
            }
            else if ((i % 2 == 0) && (j % 2 == 0)) {
                map[i][j].status = INTERSECTION;
            }
            else {
                map[i][j].status = BUILDING; // Assume all other cells are buildings
            }
        }
    }
}

void draw_colored_box(int upperLeftX, int upperLeftY, char* boxLabel, int boxColor) {
    /*
     - Draws a 3 rows high by 4 columns wide box at coordinates (upperLeftX, upperLeftY).
     - The box will not display any diagnostics if it is not on the screen.
     - Sets the box color as specified.
     - The boxLabel is a string with a maximum length of 2 characters.
    */
    printf(CSI "%dm", boxColor);          // Set the foreground color for the box
    printf(ESC "(0");                     // Switch to DEC line drawing character set
    CUP(upperLeftX, upperLeftY);
    printf("lqqk");                   // Draw top edge of the box
    CUP(upperLeftX, upperLeftY + 1);
    printf("x%sx", boxLabel);         // Draw middle part with label
    CUP(upperLeftX, upperLeftY + 2);
    printf("mqqj");                   // Draw bottom edge of the box
    printf(ESC "(B");                     // Switch back to ASCII character set
    printf(CSI "0m");                     // Reset foreground and background colors to default
}

void draw_map(int numStreets, int numAvenues) {
    int streetRow = 3; // Starting row for the first street
    int avenueCol = 5; // Starting column for the first avenue
    int buildingMarker = 1; // Identifier for each building
    int roadWidth = 1; // Width of the road

    for (int street = 0; street < numStreets; street++) {
        for (int avenue = 0; avenue < numAvenues; avenue++) {

            draw_colored_box(avenueCol, streetRow, "  ", BGBLUE);
            buildingz[buildingMarker].B_address.Y = streetRow + 1;
            buildingz[buildingMarker].B_address.X = avenueCol + 1;

            buildingz[buildingMarker].B_Number = buildingMarker;
            printf(CSI "44m");
            CUP(buildingz[buildingMarker].B_address.X, buildingz[buildingMarker].B_address.Y);
            printf("%d", buildingz[buildingMarker].B_Number);
            printf(ESC "(B"); // Switch back to ASCII character set
            printf(CSI "0m"); // Reset foreground and background colors to default  

            avenueCol = (avenue == numAvenues - 1) ? 5 : avenueCol + buildoffset + roadWidth; // Adjust for the building width and road width
        }

        streetRow += 4; // Move to the next row of streets
    }
}


//
//#ifndef debug-map
//
//void draw_map(int street, int avenue) {
//
//    int avenuecounter, streetcounter, i = 0;
//    int Building_Upper_Left_Y = ULY_of_first_building;
//    int Building_Upper_Left_X = ULX_of_first_building;
//    int marker = 0;
//
//    printf(CSI "2J"); /* Clear screen */
//
//    for (avenuecounter = 0; avenuecounter < avenue; avenuecounter++) { // COUNTER FOR DRAWING BUILDINGS VERTICALLY
//
//        Building_Upper_Left_X = ULX_of_first_building;
//
//        for (streetcounter = 0; streetcounter < street; streetcounter++) { // COUNTER FOR DRAWING BUILDINGS HORIZONTALLY
//            box(Building_Upper_Left_X, Building_Upper_Left_Y, " ", BGGREEN);
//            //draw_box(Building_Upper_Left_Y, Building_Upper_Left_X,  (Building_Upper_Left_Y+ Width_of_building), (Building_Upper_Left_X + Length_of_building));
//            marker++;
//
//            buildingz[marker].B_address.Y = (Building_Upper_Left_Y); // THE Y VALUE OF THE BUILDING
//            buildingz[marker].B_address.X = (Building_Upper_Left_X); // THE X VALUE OF THE BUILDING
//
//            buildingz[marker].B_Number = marker;
//            i = 1;
//            printf(CSI "42m");
//            CUP(buildingz[marker].B_address.X+1, buildingz[marker].B_address.Y+1)
//                //move_cursor(buildingz[marker].B_address.Y, buildingz[marker].B_address.X);
//                printf("%d", buildingz[marker].B_Number);
//            //printf("%d", buildingz[marker].B_Number);
//            printf(ESC "(B");
//            printf(CSI "0m");
//            //CUP(buildingz[marker].B_address.X, buildingz[marker].B_address.Y);
//            //move_cursor(buildingz[marker].B_address.Y + i, buildingz[marker].B_address.X + buildingnumberoffset);
//              //  printf("%d", buildingz[marker].B_Number);
//            i++;
//            //CUP(buildingz[marker].B_address.X + parkingandchargingnumberoffset, buildingz[marker].B_address.Y + i);
//            //move_cursor(buildingz[marker].B_address.Y + i, buildingz[marker].B_address.X + parkingandchargingnumberoffset);
//              //  printf("P:");
//            buildingz[marker].P_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE PARKING
//            buildingz[marker].P_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE PARKING
//
//            i++;
//            //CUP(buildingz[marker].B_address.X + parkingandchargingnumberoffset, buildingz[marker].B_address.Y + i);
//            //move_cursor(buildingz[marker].B_address.Y + i, buildingz[marker].B_address.X + parkingandchargingnumberoffset);
//              //  printf("C:");
//
//            buildingz[marker].C_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE CHARGING
//            buildingz[marker].C_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE CHARGING
//
//            buildingz[marker].numberofaedvscharging = ZERO;
//            buildingz[marker].numberofaedvsparked = ZERO;
//
//
//            Building_Upper_Left_X = Building_Upper_Left_X + Street_length;
//        }
//        Building_Upper_Left_Y = Building_Upper_Left_Y+ Avenue_length;
//    }
//    //draw_box(buildingz[1].B_address.Y + outerboxulroffset, buildingz[1].B_address.X + outerboxulcoffset, buildingz[marker].B_address.Y + outerboxurroffset, buildingz[marker].B_address.X + outerboxurcoffset);
//
//}
//
//*FUNCTION TO POPULATE BUILDINGZ ARRAY WITHOUT DRAWING THE MAP*/
//void dud_map(int street, int avenue) {
//
//    int avenuecounter, streetcounter, i = 0;
//    int Building_Upper_Left_Y = ULY_of_first_building;
//    int Building_Upper_Left_X = ULX_of_first_building;
//    int marker = 0;
//
//
//
//    for (avenuecounter = 0; avenuecounter < avenue; avenuecounter++) {
//
//        Building_Upper_Left_X = ULX_of_first_building;
//
//        for (streetcounter = 0; streetcounter < street; streetcounter++) {
//            marker++;
//
//            buildingz[marker].B_address.Y = (Building_Upper_Left_Y); // THE Y VALUE OF THE BUILDING
//            buildingz[marker].B_address.X = (Building_Upper_Left_X); // THE X VALUE OF THE BUILDING
//
//            buildingz[marker].B_Number = marker;
//            i = 1;
//         
//            i++;
//          
//            buildingz[marker].P_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE PARKING
//            buildingz[marker].P_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE PARKING
//
//            i++;
//           
//
//            buildingz[marker].C_address.Y = buildingz[marker].B_address.Y + i; // THE Y VALUE OF THE CHARGING
//            buildingz[marker].C_address.X = buildingz[marker].B_address.X + parkingandchargingnumberoffset; // THE X VALUE OF THE CHARGING
//
//            buildingz[marker].numberofaedvscharging = ZERO;
//            buildingz[marker].numberofaedvsparked = ZERO;
//
//
//            Building_Upper_Left_X = Building_Upper_Left_X + Street_length;
//        }
//        Building_Upper_Left_Y = Building_Upper_Left_Y + Avenue_length;
//    }
//}
//#endif // !debug-map
