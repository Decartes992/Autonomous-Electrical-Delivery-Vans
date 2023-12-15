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
#define ACTIVEVEHICLECOUNT 10

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
void set_location(aedvs* curr_parked);

#define Indent_location 0


#define x_NE 12
#define y_NE -2

#define x_N 5
#define y_N -2

#define x_E 12
#define y_E 2

#define x_W 5
#define y_W 2

#define x_S 5
#define y_S 6

#define x_NW -2
#define y_NW -2

#define x_SE 12
#define y_SE 6

#define x_SW -2
#define y_SW 6


#define intersection_increment_x 2

extern int activeVIN[ACTIVEVEHICLECOUNT];




#endif // UI_MANAGER_H
