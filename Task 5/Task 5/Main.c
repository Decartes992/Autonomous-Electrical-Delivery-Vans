/*
 - Main code for TASK5
 - Authors-
 - Will Thornotn - B00881401 
 - Iftekhar Rafi - B00871031
 - ECED 3401
*/


#include "Map.h"
#include "Structure_definition.h"
#include "General.h"



HANDLE Console; /* Identify action and I/O stream */

aedv* start_topark;                            // Start of list
aedv* start_parked;                            // Start of list
aedv* start_topickup;                          // Start of topickup list
aedv* start_todestination;                     // Start of list
aedv* start_tocharge;                          // Start of list
aedv* start_charging;                          // Start of list


int main(void) {

    /*VARIABLE DECLARATION*/
    int street = 0, avenue = 0, check_if_to_run_emulation_of_aedv = 0;
    int i, Numberofbuildings, Text_Position_Y;
    COORD scrsize;

    /* For console output via Windows */
    Console = GetStdHandle(STD_OUTPUT_HANDLE);

    /* Determine screen size */
    scrsize = GetLargestConsoleWindowSize(Console);
    printf("Size: r: %d c: %d\n", scrsize.Y, scrsize.X);

    check_if_to_run_emulation_of_aedv = get_map_size(&street, &avenue);
    if (check_if_to_run_emulation_of_aedv != 0) {
        return -1;
    }
    
    draw_map(street, avenue);
    
    Numberofbuildings = street * avenue;
    Text_Position_Y = buildingz[Numberofbuildings].B_address.Y + Voffset;

    ask_for_current_location(start_parked, buildingz, Numberofbuildings);

    while (check_if_to_run_emulation_of_aedv == 0) {

        /*ASSIGN NEW RIDE ORDER TO PARKED AEDVS*/
        ask_for_source_and_destination(start_parked, buildingz, Numberofbuildings);

        /*MOVE ALL AEDVS AT ONCE*/
        aedv_movement_manager();

        check_if_to_run_emulation_of_aedv_input(&check_if_to_run_emulation_of_aedv, Text_Position_Y);
    }
    return 0;
}
  
