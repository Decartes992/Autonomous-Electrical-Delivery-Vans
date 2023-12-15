#include "Aedv_Functions.h"
#include "2DArray.h"
/*MODULE: AEDV_FUNCTIONS
*
* WHAT IT DOES: THIS AEDV_FUNCTIONS.H AND AEDV_FUNCTIONS.C FILES ACHEIVE THE PURPOSE OF HANDLING
* THE REQUIRED FUNCTIONS FOR MOVING THE AEDV ACROSS THE SCREEN.
* -CODE TO MOVE AEDV ONCE IN X DIRECTION
* -CODE TO MOVE AEDV ONCE IN Y DIRECTION
* -ALGORITHM FOR AEDV MANAGER
* - 2ND STEP FOR AEDV MANAGER
* - 3RD STEP FOR AEDV MANAGER
* 
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/





/*FUNCTION TO MOVE AEDV ONCE IN X DIRECTION*/
void move_aedv_once_in_x(aedvs* aedv, int distancex) {




	if (distancex > ZERO) {                                                                     // MOVE RIGHT
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//+yoffset
			printf(" ");
		aedv->current.gridl.X++;
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//+yoffset
			printf("%d", (aedv->VIN - offsetid));                                           // print the aedv onto screen
		printf(CSI "?25l");	/* Hide cursor */		
	}

	else if (distancex < ZERO) {                                                                                   // MOVE LEFT
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//+yoffset
			printf("  ");
		aedv->current.gridl.X--;
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//+yoffset
			printf("%d", (aedv->VIN - offsetid));                                            // print the aedv onto screen
		//printf(CSI "?25l");	/* Hide cursor */	
	}


}

/*FUNCTION TO MOVE AEDV ONCE IN Y DIRECTION*/
void move_aedv_once_in_y(aedvs* aedv, int distancey) {

	// MOVE DOWN
	if (distancey > ZERO) {
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//+YOFFSET
			printf(" ");
		//printf(CSI "?25l");	/* Hide cursor */
		//move_cursor(aedv->current.gridl.Y + yoffset, aedv->current.gridl.X);             // increment cursor up every loop before printing
		//printf("  ");
		aedv->current.gridl.Y++;
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//+CURSOROFFSET
			printf("%d", (aedv->VIN - offsetid));
		//printf(CSI "?25l");	/* Hide cursor */
		//move_cursor(aedv->current.gridl.Y + cursoroffset, aedv->current.gridl.X);        // increment cursor up every loop before printing
		//printf("V%d", (aedv->VIN - offsetid));                                           // print the aedv onto screen
	}

	else if (distancey < ZERO) {                                                                               // MOVE UP

		//move_cursor(aedv->current.gridl.Y, aedv->current.gridl.X);                       // postition cursor
		//printf("V%d", (aedv->VIN - offsetid));                                           // print the aedv onto screen
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//+YOFFSET
			printf(" ");
		aedv->current.gridl.Y--;
		//printf(CSI "?25l");	/* Hide cursor */
		CUP(aedv->current.gridl.X, aedv->current.gridl.Y)//-yoffset
			printf("%d", (aedv->VIN - offsetid));
		//printf(CSI "?25l");	/* Hide cursor */
		//move_cursor(aedv->current.gridl.Y + yoffset, aedv->current.gridl.X);             // increment cursor down every loop before printing
		//printf("  ");
		
	}

}


void aedv_movement_manager()
{
	int transferflag = 0;
	aedvs* curr_parked, * prev, * curr_topickup, * curr_todestination, * curr_intersection_for_pickup, * curr_intersection_for_destination;

	while (start_topickup || start_todestination || start_topickup_intersection || start_todestination_intersection) {

		curr_topickup = start_topickup;
		curr_todestination = start_todestination;
		curr_parked = start_parked;
		curr_intersection_for_pickup = start_topickup_intersection;
		curr_intersection_for_destination = start_todestination_intersection;

		while (curr_topickup || curr_todestination || curr_intersection_for_pickup || curr_intersection_for_destination || curr_parked) {




			if (curr_intersection_for_pickup) {
				aedv_ride_manager_2nd_step(curr_intersection_for_pickup, &start_topickup_intersection, &start_topickup, curr_intersection_for_pickup->source.intersection_location);
			}


			if(curr_topickup){
				aedv_ride_manager_2nd_step(curr_topickup, &start_topickup, &start_todestination, curr_topickup->source.gridl);
			}





			if(curr_todestination){
				transferflag = aedv_ride_manager_2nd_step(curr_todestination, &start_todestination, &start_parked, curr_todestination->destination.gridl);
				if(transferflag == 1) {
					deliveryfile(*curr_todestination);
					transferflag = 0;
				}
			}




			print_current_destination(curr_parked, start_parked);

			if (curr_intersection_for_pickup) {
				curr_intersection_for_pickup = curr_intersection_for_pickup->next;
			}
			if (curr_topickup) {
				curr_topickup = curr_topickup->next;
			}
			if (curr_todestination) {
				curr_todestination = curr_todestination->next;
			}
			if (curr_parked) {
				curr_parked = curr_parked->next;
			}
		}
		Sleep(sleeptime);                                                                          // add delay to show the aedv moving

	}
}

int aedv_ride_manager_2nd_step(aedvs* tomove, aedvs ** tomovellhead, aedvs ** destinationll, COORD destination)
{
	int transferflag = 0;
	if (*tomovellhead) {
		if (tomove == NULL) {
			tomove = *tomovellhead;
		}

		/*MOVE AND TRANSFER LINKED LISTS IF SOURCE IS REACHED*/
		aedv_movement_manager_3rd_step(tomove, destination);
		if (tomove->current.gridl.X == destination.X) {
			if (tomove->current.gridl.Y == destination.Y) {
				CUP(tomove->current.gridl.X, tomove->current.gridl.Y)//+yoffset
					printf(" ");
				//move_cursor(tomove->current.gridl.Y + yoffset, tomove->current.gridl.X);
				//printf("  ");
				transferflag = 1;
				add_to_aedv_list(destinationll, *tomove);
				delete_from_aedv_list(tomovellhead, * tomove);
			}
		}
	}
}



void aedv_parking_manager (aedvs** tomovellhead, COORD destination, aedvs* tomove) {

	if (tomove->battery >= lowbatterylevel) {
		add_to_aedv_list(&start_parked, *tomove);
		delete_from_aedv_list(&start_todestination, *tomove);
	}
	else {
		add_to_aedv_list(&start_tocharge, *tomove);
		delete_from_aedv_list(&start_todestination, *tomove);
	}
}


void aedv_movement_manager_3rd_step(aedvs* aedv, COORD destination) {
	int distancey = destination.Y - aedv->current.gridl.Y;
	int distancex = destination.X - aedv->current.gridl.X;                                       // Find distance in x-axis
	unsigned char direction = word[aedv->current.gridl.Y][aedv->current.gridl.X];
	
	if (direction == We)
		if (distancey == 0 && distancex == 0)
			aedv->battery--;
		else
			move_aedv_once_in_x(aedv, -1);
	else if (direction == Ea)
		 if (distancey == 0 && distancex == 0)
			aedv->battery--;
		 else	
			move_aedv_once_in_x(aedv, 1);
	else if (direction == No)
		if (distancey == 0 && distancex == 0)
			aedv->battery--;
		else
			move_aedv_once_in_y(aedv, -1);
	else if (direction == So)
		if (distancey == 0 && distancex == 0)
			aedv->battery--; 
		else
			move_aedv_once_in_y(aedv, 1);
	else if (direction == EN)
	{
		if (distancex < 4 && distancey < 0) {
			move_aedv_once_in_y(aedv, -1);//changed this from y -1 to x 1
			aedv->battery--;
		}
		else if (distancey == 0 && distancex == 0)
			aedv->battery--;
		else {
			move_aedv_once_in_x(aedv, 1);
			aedv->battery--;
		}
	}
	else if (direction == WN)
	{
		if ((aedv->current.gridl.Y - 2) % 4 != 0)
		{
			if (distancey == 0 && distancex < 2 && distancex > -2)
				move_aedv_once_in_x(aedv, -1);
			else
				move_aedv_once_in_y(aedv, -1);
		}
		else if (distancex >= ZERO && distancey <= 0) { //-4
			move_aedv_once_in_y(aedv, -1);
			aedv->battery--;
		}
		else if (distancey == 0 && distancex == 0)
			aedv->battery--;
		else {
			move_aedv_once_in_x(aedv, -1);
			aedv->battery--;
		}
	}
	else if (direction == ES)
	{
		if ((aedv->current.gridl.Y - 2) % 4 != 0)
		{
			if (distancey == 0 && distancex <2 && distancex>-2)
				move_aedv_once_in_x(aedv, 1);
			else
				move_aedv_once_in_y(aedv, 1);
		}
		else if (distancex < 4 && distancey > 0) {
			move_aedv_once_in_y(aedv, 1);
			aedv->battery--;
		}
		else if (distancey == 0 && distancex == 0)
			aedv->battery--;
		else {
			move_aedv_once_in_x(aedv, 1);
			aedv->battery--;
		}
	}
	else if (direction == WS)
	{
		if (distancex >= ZERO && distancey >= 0) {
			move_aedv_once_in_y(aedv, 1);
			aedv->battery--;
		}
		else if (distancey == 0 && distancex == 0)
			aedv->battery--;
		else {
			move_aedv_once_in_x(aedv, -1);
			aedv->battery--;
		}
	}
}
