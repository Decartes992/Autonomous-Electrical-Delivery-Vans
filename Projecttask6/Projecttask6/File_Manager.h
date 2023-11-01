/*Header for all relative record files*/


#include <string.h>
#include "Structure_definition.h"
#include "Map.h"
#include "General.h"
#include "Taxi_Functions.h"
#include "UI_Manager.h"
#include "Taxi.h"

/*MODULE: FILE_MANAGER
*
* WHAT IT DOES:THE FILE MANAGER MODULE IS PURPOSED TO HANDLE IO RELATED TO FILES
* AND FOR ASSIGNING ORDERS TO THE TAXIS
*
* DATE: 10-11-2022
*
* NAME:
* IFTEKHAR RAFI
* MAZEN
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
* Taxi record: 
* - Contains taxi information
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



void file_manager(int argc, char* argv[]);
void sequential_access();
void rel_read();
void rel_update();
void rel_delete();
void add_taxi(FILE* tfd);
void init_file();
int open_file(int , char* argv[], int );
void taxi_initiator();
void read_activevehicle(taxis**);
void read_ordersfile(taxis** taxi_);
void getmapsize(int* street, int* avenue);
