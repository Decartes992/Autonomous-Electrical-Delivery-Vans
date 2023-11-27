#ifndef UI_MANAGER_H
#define UI_MANAGER_H
/*MODULE: UI_MANAGER 
*
* WHAT IT DOES:THE UI MANAGER MODULE IS PURPOSED TO HANDLE IO TO THE CONSOLE
* AND FOR ASSIGNING ORDERS TO THE AEDVS
*
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILIAM THORNTON
*
*/


#include "Structure_definition.h"
#include "Map.h"
#include "General.h"
#include "Aedv_Functions.h"
#include "AEDV_FileManager.h"
#include "Aedv.h"

/*FUNCTIONS TO TAKE USER INPUT*/

void UI_Manager(int argc, char* argv[]);
void GetUserInput();
void GetAddress(aedvs* head, buildings* buildingz, int Numberofbuildings);
void GetCurrentLocation(aedvs* head, buildings* buildingz, int Numberofbuildings);
int GetMapSize(int* street, int* avenue);
void RunAedvsInputEmulation(int* check_if_to_run_emulation_of_aedvs, int Text_Position_Y);
void PrintDestination(aedvs* tomove, aedvs* tomovellhead);
void SetLocation(aedvs* curr_parked);
void GetOffset(int comparator, int* x_offset, int* y_offset);
void GetFileInput(int argc, char* argv[]);
void SetAddress(aedvs* head, buildings* buildingz, int Numberofbuildings);

#define Indent_location 0


#define x_NE 4 //12
#define y_NE -2 //-2

#define x_N 1 //5
#define y_N -2 //-2

#define x_E 4 //12
#define y_E 0 // 2

#define x_W -1 //5
#define y_W 0 //2

#define x_S 2 //5
#define y_S 1 //6

#define x_NW 0 //-2
#define y_NW -2 //-2

#define x_SE 2 //12
#define y_SE 2 //6

#define x_SW -1 //-2
#define y_SW 2 //6


#define intersection_increment_x 2

extern int activeVIN[ACTIVEVEHICLECOUNT];




#endif // UI_MANAGER_H
