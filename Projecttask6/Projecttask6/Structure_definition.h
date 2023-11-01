#pragma once
/*MODULE: STRUCTURE_DEFINITION
*
* WHAT IT DOES: THE STRUCTURE_DEFINITION.H FILE IS USED TO DECLARE ALL THE STRUCTURES AND
* USER DEFINED DATA TYPES USED IN THIS PROJECT.
*
* DATE: 10-11-2022
*
* NAME:
* IFTEKHAR RAFI
* MAZEN
*
*/
#ifndef STRUCTURE_DEFINITION_H
#define STRUCTURE_DEFINITION_H

#include "General.h"
#include "Map.h"


extern FILE* filein;

enum buildingsides {                                      //NW IS NORTH-WEST, NE IS NORTH-EAST, SW IS SOUTH-WEST, SE IS SOUTH-EAST
    NW, N, NE, W, DEFAULT, E, SW, S, SE
};

enum REC_STATUS { ACTIVE, DELETED };

enum MOVEMENT_STATUS { TOPICKUP, TODESTINATION, PARKED, CHARGING };


//enum parking{zero, one, two};
                                                          //enum charging { zero, one, two };



typedef struct buil {
    int B_Number;                                         // Building Number
    COORD B_address;                                      // Building Address
    COORD P_address;                                        //Parking Address
    int numberoftaxisparked;
    COORD C_address;                                        //Charging Address
    int numberoftaxischarging;

} buildings;


buildings buildingz[MAXSIZE];

typedef struct Loc {                                      //Function to store cartesian location and building number under one struct
    COORD intersection_location;
    COORD gridl;                                          //final location of taxi
    int buildingl;
    enum buildingsides buildingside;
} loc;


typedef struct taxi {
    enum REC_STATUS status;
    int ordertime;
    int VIN;
    loc source;
    loc destination;
    loc current;
    int battery;
    struct taxi* next;
} taxis;

typedef struct ORDER {
    int time;
    taxis taxi_;
    struct taxi* next;
} ORDERS;

typedef struct orderstyle {
    int passengernumber;
    loc pickup;
    loc destination;
}order;




struct header
{
    long del_rec_list;	/* Deleted record list */
    long first_VIN;		/* First available sid */
};
typedef struct header HEADER;

typedef struct deleted_taxi
{
    enum REC_STATUS status;
    long  next_deleted;
}DEL_TAXI;




union taxi_file
{
    taxis taxirec;
    HEADER hrec;
    DEL_TAXI drec;
};
typedef union taxi_file SFREC;



#endif STRUCTURE_DEFINITION_H
