#ifndef AEDV_H
#define AEDV_H
/*MODULE: AEDV
* 
* WHAT IT DOES: THIS AEDV.H AND AEDV.C FILES ACHEIVE THE PURPOSE OF HANDLING
* THE REQUIRED FUNCTIONS FOR USING LINKED LISTS OF TYPE AEDV.
* LINKED LIST HEADERS ARE ALSO DEFINED HERE.
* 
* DATE: 10-29-2023
* 
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
* 
*/



#include "General.h"
#include "Map.h"
#include "Structure_definition.h"




void copy_aedv(aedvs* old, aedvs* new);                //FUNCTION TO COPY CONTENTS OF STRUCT AEDV
extern int add_to_aedv_list(aedvs**, aedvs);
extern void delete_from_aedv_list(aedvs**, aedvs);
void copy_aedv_source_destination(aedvs* old, aedvs* new);

extern aedvs* start_active;                                         // Start of list

extern aedvs* start_topark;                                         // Start of list
extern aedvs* start_topark_intersection;                            // Start of list

extern aedvs* start_parked;                                         // Start of list

extern aedvs* start_topickup_intersection;                          // Start of topickup list
extern aedvs* start_topickup;                                       // Start of topickup list

extern aedvs* start_todestination_intersection;                     // Start of list
extern aedvs* start_todestination;                                  // Start of list

extern aedvs* start_tocharge_intersection;                          // Start of list
extern aedvs* start_tocharge;                                       // Start of list

extern aedvs* start_charging;                                       // Start of list

extern aedvs* start_orders;                                       // Start of list


#endif //AEDV_H
