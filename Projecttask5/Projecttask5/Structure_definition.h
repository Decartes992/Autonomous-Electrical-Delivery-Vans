#pragma once
/*MODULE: STRUCTURE_DEFINITION
*
* WHAT IT DOES: THE STRUCTURE_DEFINITION.H FILE IS USED TO DECLARE ALL THE STRUCTURES AND
* USER DEFINED DATA TYPES USED IN THIS PROJECT.
*
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/
#ifndef STRUCTURE_DEFINITION_H
#define STRUCTURE_DEFINITION_H

#include "General.h"
#include "Map.h"


extern FILE* filein;

enum buildingsides {                                      //NW IS NORTH-WEST, NE IS NORTH-EAST, SW IS SOUTH-WEST, SE IS SOUTH-EAST
    NW = 1,N,NE,W,E,SW,S,SE
};

enum REC_STATUS { ACTIVE, DELETED };

enum MOVEMENT_STATUS { TOPICKUP, TODESTINATION, PARKED, CHARGING };


//enum parking{zero, one, two};
                                                          //enum charging { zero, one, two };



typedef struct buil {
    int B_Number;                                         // Building Number
    COORD B_address;                                      // Building Address
    COORD P_address;                                        //Parking Address
    int numberofaedvsparked;
    COORD C_address;                                        //Charging Address
    int numberofaedvscharging;

} buildings;


buildings buildingz[MAXSIZE];

typedef struct Loc {                                      //Function to store cartesian location and building number under one struct
    COORD intersection_location;
    COORD gridl;                                          //final location of AEDV
    int buildingl;
    enum buildingsides buildingside;
} loc;


typedef struct AEDV {
    enum REC_STATUS status;
    int ordertime;
    int VIN;
    loc source;
    loc destination;
    loc current;
    int battery;
    struct aedv* next;
} aedvs;

typedef struct ORDER {
    int time;
    aedvs aedv_;
    struct aedv* next;
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

typedef struct deleted_aedv
{
    enum REC_STATUS status;
    long  next_deleted;
}DEL_AEDV;




union aedv_file
{
    aedvs aedvrec;
    HEADER hrec;
    DEL_AEDV drec;
};
typedef union aedv_file SFREC;



#endif STRUCTURE_DEFINITION_H
