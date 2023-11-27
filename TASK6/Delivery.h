///*MODULE: DELIVERY
//*
//* WHAT IT DOES:THE DELIVERY MODULE IS PURPOSED TO HANDLE DELIVERY FILES AND PROCESSING
//* AND FOR ASSIGNING ORDERS TO THE AEDVS
//*
//* DATE: 10-29-2023
//*
//* NAME:
//* IFTEKHAR RAFI
//* WILLIAM THORNTON
//*
//*/
//
//#include <string.h>
//#include "Structure_definition.h"
//#include "Map.h"
//#include "General.h"
//#include "Aedv_Functions.h"
//#include "UI_Manager.h"
//#include "Aedv.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <io.h>
//#include <fcntl.h>     /* for _O_TEXT and _O_BINARY */
//
//
//
//
//#define NL	'\n'
//#define NUL	'\0'
//#define NAMELEN	16
//#define TRUE	1
//#define FALSE	0
//#define DEL_END -1l
//#define VINADJUST 999
//#define ACTIVEVEHICLECOUNT 10
//
//
///*
//* AEDV record:
//* - Contains AEDV information
//* - Indicates record is ACTIVE
//*
//* header record:
//   - Record 0 containing metadata pertaining to file
//   - Includes first available sid and deleted record list
//*/
//
//
//
//#define TRUNCATE(name)	name[strlen(name)-1] = '\0'
//
//
//extern FILE* orders;
//
//
//
//void createDeliveryFile();
//void readDeliveryFile();
//void updateDeliveryFile();
//void deleteDeliveryFile();
//
//
