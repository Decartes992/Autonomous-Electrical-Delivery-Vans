/*
 - Main code for AEDV
 - Authors-
 - William Thornton - B00881401
 - Iftekhar Rafi - B00871031
 - ECED 3401
*/


#include "Map.h"
#include "Structure_definition.h"
#include "General.h"
#include "Aedv_Functions.h"
#include "UI_Manager.h"

clock_t start, currenttime, end;


int main(int argc, char* argv[]) {
    start = clock();
    UI_Manager(argc,  argv);
    return 0;
}
  