#ifndef TAXI_H
#define TAXI_H
/*MODULE: TAXI
* 
* WHAT IT DOES: THIS TAXI.H AND TAXI.C FILES ACHEIVE THE PURPOSE OF HANDLING
* THE REQUIRED FUNCTIONS FOR USING LINKED LISTS OF TYPE TAXI.
* LINKED LIST HEADERS ARE ALSO DEFINED HERE.
* 
* DATE: 10-10-2022
* 
* NAME:
* IFTEKHAR RAFI
* MAZEN
* 
*/



#include "General.h"
#include "Map.h"
#include "Structure_definition.h"




void copy_taxi(taxis* old, taxis* new);                //FUNCTION TO COPY CONTENTS OF STRUCT TAXI
extern int add_to_taxi_list(taxis**, taxis);
extern void delete_from_taxi_list(taxis**, taxis);
void copy_taxi_source_destination(taxis* old, taxis* new);

extern taxis* start_active;                                         // Start of list

extern taxis* start_topark;                                         // Start of list
extern taxis* start_topark_intersection;                            // Start of list

extern taxis* start_parked;                                         // Start of list

extern taxis* start_topickup_intersection;                          // Start of topickup list
extern taxis* start_topickup;                                       // Start of topickup list

extern taxis* start_todestination_intersection;                     // Start of list
extern taxis* start_todestination;                                  // Start of list

extern taxis* start_tocharge_intersection;                          // Start of list
extern taxis* start_tocharge;                                       // Start of list

extern taxis* start_charging;                                       // Start of list

extern taxis* start_orders;                                       // Start of list


#endif //TAXI_H
