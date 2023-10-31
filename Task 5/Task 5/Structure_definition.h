#pragma once
     
#ifndef STRUCTURE_DEFINITION_H
#define STRUCTURE_DEFINITION_H

#include "General.h"
#include "Map.h"


extern FILE* filein;

typedef struct buil {
    int B_Number;                                      // Building Number
    COORD B_address;                                   // Building Address
} buildings;

                                                       
buildings buildingz[MAXSIZE];

typedef struct Loc {                                   //Function to store cartesian location and building number under one struct
    COORD gridl;
    int buildingl;
} loc;


typedef struct AEDV {
    int VIN;                                          
    loc source;
    loc destination;
    loc current;
    struct AEDV* next;
} aedv;

void copy_aedv(aedv* old, aedv* new);                //FUNCTION TO COPY CONTENTS OF STRUCT AEDV



extern aedv* start_topark;                            // Start of list
extern aedv* start_parked;                            // Start of list
extern aedv* start_topickup;                          // Start of topickup list
extern aedv* start_todestination;                     // Start of list
extern aedv* start_tocharge;                          // Start of list
extern aedv* start_charging;                          // Start of list

extern int add_to_aedv_list(aedv**, aedv);

extern void delete_from_aedv_list(aedv**, aedv);

void move_aedv_once(aedv* aedv, COORD destination);

void ask_for_source_and_destination(aedv* head, buildings * buildingz, int Numberofbuildings);
void ask_for_current_location(aedv* head, buildings* buildingz, int Numberofbuildings);
void aedv_movement_manager();
void aedv_movement_manager_2nd_step(aedv* tomove, aedv* tomovellhead, aedv* destinationll);
int get_map_size(int* street, int* avenue);
void check_if_to_run_emulation_of_aedv_input(int* check_if_to_run_emulation_of_aedv, int Text_Position_Y);
void print_current_destination(aedv* tomove, aedv* tomovellhead);


#endif STRUCTURE_DEFINITION_H
