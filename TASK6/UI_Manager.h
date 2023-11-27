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

// Function to manage the User Interface. It takes command line arguments as input.
void UI_Manager(int argc, char* argv[]);

// Function to get user input from the console.
void GetUserInput();

// Function to get the address of the building. It takes the head of the aedvs list, the buildings list and the number of buildings as input.
void GetAddress(aedvs* head, buildings* buildingz, int Numberofbuildings);

// Function to get the current location of the aedvs. It takes the head of the aedvs list, the buildings list and the number of buildings as input.
void GetCurrentLocation(aedvs* head, buildings* buildingz, int Numberofbuildings);

// Function to get the size of the map. It takes pointers to street and avenue as input and returns the size of the map.
int GetMapSize(int* street, int* avenue);

// Function to run the aedvs input emulation. It takes a pointer to check if to run emulation of aedvs and the text position Y as input.
void RunAedvsInputEmulation(int* check_if_to_run_emulation_of_aedvs, int Text_Position_Y);

// Function to print the destination of the aedvs. It takes the aedvs to move and the head of the aedvs list as input.
void PrintDestination(aedvs* tomove, aedvs* tomovellhead);

// Function to set the location of the aedvs. It takes the currently parked aedvs as input.
void SetLocation(aedvs* curr_parked);

// Function to get the offset. It takes the comparator and pointers to x_offset and y_offset as input.
void GetOffset(int comparator, int* x_offset, int* y_offset);

// Function to get file input. It takes command line arguments as input.
void GetFileInput(int argc, char* argv[]);

// Function to set the address of the building. It takes the head of the aedvs list, the buildings list and the number of buildings as input.
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
