#ifndef TAXI_FUNCTIONS_H
#define TAXI_FUNCTIONS_H

/*MODULE: TAXI_FUNCTIONS
*
* WHAT IT DOES: THIS TAXI_FUNCTIONS.H AND TAXI_FUNCTIONS.C FILES ACHEIVE THE PURPOSE OF HANDLING
* THE REQUIRED FUNCTIONS FOR MOVING THE TAXI ACROSS THE SCREEN.
* -CODE TO MOVE TAXI ONCE IN X DIRECTION
* -CODE TO MOVE TAXI ONCE IN Y DIRECTION
* -ALGORITHM FOR TAXI MANAGER
* - 2ND STEP FOR TAXI MANAGER
* - 3RD STEP FOR TAXI MANAGER
*
* DATE: 10-11-2022
*
* NAME:
* IFTEKHAR RAFI
* MAZEN
*
*/

#include "Structure_definition.h"
#include "Map.h"
#include "General.h"
#include "Taxi.h"


/*FUNCITONS TO MOVE TAXI*/
void move_taxi_once_in_x(taxis* taxi, int distancex);
void move_taxi_once_in_y(taxis* taxi, int distancey);
void taxi_movement_manager();
//void taxi_movement_manager_2nd_step(taxis* tomove, taxis* tomovellhead, taxis* destinationll);
void taxi_movement_manager_3rd_step(taxis* taxi, COORD destination);
void taxi_ride_manager_2nd_step(taxis* tomove, taxis** tomovellhead, taxis** destinationll, COORD destination);
void taxi_parking_manager(taxis** tomovellhead, COORD destination, taxis* tomove);

#define sleeptime 100

#endif //TAXI_FUNCTIONS_H
