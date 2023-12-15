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
#include "File_Manager.h"
#include "Aedv.h"

/*FUNCTIONS TO TAKE USER INPUT*/

void UI_Manager(int argc, char* argv[]);
void take_user_input();
void ask_for_source_and_destination_and_assign_parking_location(aedvs* head, buildings* buildingz, int Numberofbuildings);
void ask_for_current_location(aedvs* head, buildings* buildingz, int Numberofbuildings);
int get_map_size(int* street, int* avenue);
void check_if_to_run_emulation_of_aedvs_input(int* check_if_to_run_emulation_of_aedvs, int Text_Position_Y);
void print_current_destination(aedvs* tomove, aedvs* tomovellhead);
void set_location(aedvs* curr_parked);
void get_offset(int comparator, int* x_offset, int* y_offset);
int squareOfNumber(int num);
void take_file_input(int argc, char* argv[]);
void set_source_and_destination_and_assign_parking_location(aedvs* head, buildings* buildingz, int Numberofbuildings);
//void set_location(aedvs* curr_parked);

#define Indent_location 0


#define x_NE 3 //12, 4
#define y_NE -1 //-2, -2

#define x_N 1 //5, 1
#define y_N -1 //-2, -2

#define x_E 4 //12, 4
#define y_E -1 // 2, -1

#define x_W -1 //5, -1
#define y_W 1 //2, 0

#define x_S 2 //5, 2
#define y_S 3 //6, 1

#define x_NW 0 //-2, 0
#define y_NW -1 //-2, -2

#define x_SE 4 //12, 2, 4
#define y_SE 3 //6, 2, 3

#define x_SW -1 //-2, -1
#define y_SW 3 //6, 2


#define intersection_increment_x 2

extern int activeVIN[ACTIVEVEHICLECOUNT];




#endif // UI_MANAGER_H
