/*Header for all relative record files*/

#ifndef AEDV_File_Manager
#define AEDV_File_Manager

#include <string.h>
#include "Structure_definition.h"
#include "Map.h"
#include "General.h"
#include "Aedv_Functions.h"
#include "UI_Manager.h"
#include "Aedv.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <fcntl.h>     /* for _O_TEXT and _O_BINARY */

/*MODULE: FILE_MANAGER
*
* WHAT IT DOES:THE FILE MANAGER MODULE IS PURPOSED TO HANDLE IO RELATED TO FILES
* AND FOR ASSIGNING ORDERS TO THE AEDVS
*
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/

#define NL	'\n'
#define NUL	'\0'
#define NAMELEN	16
#define TRUE	1
#define FALSE	0
#define DEL_END -1l
#define VINADJUST 999
#define ACTIVEVEHICLECOUNT 10


/*
* AEDV record: 
* - Contains AEDV information
* - Indicates record is ACTIVE
* 
* header record:
   - Record 0 containing metadata pertaining to file
   - Includes first available sid and deleted record list
*/



#define TRUNCATE(name)	name[strlen(name)-1] = '\0'

extern FILE* tfd; 
extern FILE* activevehicle;
extern FILE* orders;
extern FILE* map;
extern FILE* chargingandparking;



void manageAedvFiles(int argc, char* argv[]);
void sequentialAccessAedv();
void readAedv();
void updateAedv();
void deleteAedv();
void addAedv(FILE* tfd);
void initializeAedvFile();
int openAedvFile(int, char* argv[], int);
void initiateAedv();															

void read_activevehicle(aedvs**);
void read_ordersfile(aedvs** aedv_);
void getmapsize(int* street, int* avenue);

#endif // !AEDV_File_Manager