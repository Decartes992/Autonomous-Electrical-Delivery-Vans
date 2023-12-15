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


void move_cursor(int row, int col);         //FUNCTION TO MOVE CURSOR ON THE CONSOLE WINDOW
void draw_box(int ulr, int ulc, int urr, int urc);//FUNCTION TO DRAW BOX ON CONSOLE WINDOW
void draw_map(int street, int avenue);      //FUNCTION TO DRAW THE MAP ON CONSOLE WINDOW
void dud_map(int street, int avenue);

#define Street_length 5
#define Avenue_length 4

//UL means upper left
#define ULX_of_first_building 3
#define ULY_of_first_building 3


#define Length_of_building 10
#define Width_of_building 5



#define buildingnumberoffset 5
#define parkingandchargingnumberoffset 2

#define outerboxulroffset - 3
#define outerboxulcoffset -7
#define outerboxurroffset 8
#define outerboxurcoffset 17






#endif //MAP_H