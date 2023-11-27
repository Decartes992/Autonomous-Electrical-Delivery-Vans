#ifndef MAP_H
#define MAP_H
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



#include "General.h"
#include "Structure_definition.h"


//void dud_map(int street, int avenue);

#define Street_length 5
#define Avenue_length 4
#define Length_of_building 10
#define Width_of_building 5



#define buildingnumberoffset 5
#define parkingandchargingnumberoffset 2



#pragma once



typedef enum {
    CORNER,
    INTERSECTION,
    NODE,
    BUILDING // Status for building cells
} Status;

typedef struct {
    Status status;  // The status of the cell
} Cell;


void draw_colored_box(int upperLeftX, int upperLeftY, char* boxLabel, int boxColor);     //FUNCTION TO DRAW BOX ON CONSOLE WINDOW
void draw_map(int numStreets, int numAvenues);                                          //FUNCTION TO DRAW THE MAP ON CONSOLE WINDOW





#endif //MAP_H