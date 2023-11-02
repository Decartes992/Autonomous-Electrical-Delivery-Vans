#ifndef AEDV_FUNCTIONS_H
#define AEDV_FUNCTIONS_H

/*MODULE: AEDV_FUNCTIONS
*
* WHAT IT DOES: THIS AEDV_FUNCTIONS.H AND AEDV_FUNCTIONS.C FILES ACHEIVE THE PURPOSE OF HANDLING
* THE REQUIRED FUNCTIONS FOR MOVING THE AEDV ACROSS THE SCREEN.
* -CODE TO MOVE AEDV ONCE IN X DIRECTION
* -CODE TO MOVE AEDV ONCE IN Y DIRECTION
* -ALGORITHM FOR AEDV MANAGER
* - 2ND STEP FOR AEDV MANAGER
* - 3RD STEP FOR AEDV MANAGER
*
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/

#include "Structure_definition.h"
#include "Map.h"
#include "General.h"
#include "Aedv.h"


/*FUNCITONS TO MOVE AEDV*/
void move_aedv_once_in_x(aedvs* aedv, int distancex);
void move_aedv_once_in_y(aedvs* aedv, int distancey);
void aedv_movement_manager();
//void aedv_movement_manager_2nd_step(aedvs* tomove, aedvs* tomovellhead, aedvs* destinationll);
void aedv_movement_manager_3rd_step(aedvs* aedv, COORD destination);
void aedv_ride_manager_2nd_step(aedvs* tomove, aedvs** tomovellhead, aedvs** destinationll, COORD destination);
void aedv_parking_manager(aedvs** tomovellhead, COORD destination, aedvs* tomove);

#define sleeptime 100

#endif //AEDV_FUNCTIONS_H
