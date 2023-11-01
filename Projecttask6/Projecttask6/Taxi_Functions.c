#include "Taxi_Functions.h"
/*MODULE: TAXI_FUNCTIONS
*
* WHAT IT DOES: THIS TAXI_FUNCTIONS.H AND TAXI_FUNCTIONS.C FILES ACHEIVE THE PURPOSE OF HANDLING
* THE REQUIRED FUNCTIONS FOR MOVING THE TAXI ACROSS THE SCREEN.
* -CODE TO MOVE TAXI ONCE IN X DIRECTION
* -CODE TO MOVE TAXI ONCE IN Y DIRECTION
* -ALGORITHM FOR TAXI MANAGER
* - 2ND STEP FOR TAXI MANAGER
* - 3RD STEP FOR TAXI MANAGER
* 
* DATE: 10-11-2022
*
* NAME:
* IFTEKHAR RAFI
* 
*
*/





/*FUNCTION TO MOVE TAXI ONCE IN X DIRECTION*/
void move_taxi_once_in_x(taxis* taxi, int distancex) {




	if (distancex > ZERO) {                                                                     // MOVE RIGHT
		move_cursor(taxi->current.gridl.Y + yoffset, taxi->current.gridl.X);                 // postition cursor
		printf(" T%d ", (taxi->VIN - offsetid));                                             // print the taxi onto screen
		taxi->current.gridl.X++;
	}

	else if (distancex < ZERO) {                                                                                   // MOVE LEFT
		move_cursor(taxi->current.gridl.Y + yoffset, taxi->current.gridl.X);                 // postition cursor
		printf("T%d  ", (taxi->VIN - offsetid));                                              // print the taxi onto screen
		taxi->current.gridl.X--;
	}


}

/*FUNCTION TO MOVE TAXI ONCE IN Y DIRECTION*/
void move_taxi_once_in_y(taxis* taxi, int distancey) {

	// MOVE DOWN
	if (distancey > ZERO) {
		move_cursor(taxi->current.gridl.Y + yoffset, taxi->current.gridl.X);             // increment cursor up every loop before printing
		printf("  ");
		move_cursor(taxi->current.gridl.Y + cursoroffset, taxi->current.gridl.X);        // increment cursor up every loop before printing
		printf("T%d", (taxi->VIN - offsetid));                                           // print the taxi onto screen
		taxi->current.gridl.Y++;
	}

	else if (distancey < ZERO) {                                                                               // MOVE UP

		move_cursor(taxi->current.gridl.Y, taxi->current.gridl.X);                       // postition cursor
		printf("T%d", (taxi->VIN - offsetid));                                           // print the taxi onto screen
		move_cursor(taxi->current.gridl.Y + yoffset, taxi->current.gridl.X);             // increment cursor down every loop before printing
		printf("  ");
		taxi->current.gridl.Y--;
	}

}


void taxi_movement_manager()
{
	taxis* curr_parked, * prev, * curr_topickup, * curr_todestination, * curr_intersection_for_pickup, * curr_intersection_for_destination;

	while (start_topickup || start_todestination || start_topickup_intersection || start_todestination_intersection) {

		curr_topickup = start_topickup;
		curr_todestination = start_todestination;
		curr_parked = start_parked;
		curr_intersection_for_pickup = start_topickup_intersection;
		curr_intersection_for_destination = start_todestination_intersection;

		while (curr_topickup || curr_todestination || curr_intersection_for_pickup || curr_intersection_for_destination || curr_parked) {




			if (curr_intersection_for_pickup) {
				taxi_ride_manager_2nd_step(curr_intersection_for_pickup, &start_topickup_intersection, &start_topickup, curr_intersection_for_pickup->source.intersection_location);
			}


			if(curr_topickup){
				taxi_ride_manager_2nd_step(curr_topickup, &start_topickup, &start_todestination, curr_topickup->source.gridl);
			}





			if(curr_todestination){
				taxi_ride_manager_2nd_step(curr_todestination, &start_todestination, &start_parked, curr_todestination->destination.gridl);
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
		Sleep(sleeptime);                                                                          // add delay to show the taxi moving

	}
}

void taxi_ride_manager_2nd_step(taxis* tomove, taxis ** tomovellhead, taxis ** destinationll, COORD destination)
{

	if (*tomovellhead) {
		if (tomove == NULL) {
			tomove = *tomovellhead;
		}

		/*MOVE AND TRANSFER LINKED LISTS IF SOURCE IS REACHED*/
		taxi_movement_manager_3rd_step(tomove, destination);
		if (tomove->current.gridl.X == destination.X) {
			if (tomove->current.gridl.Y == destination.Y) {
				move_cursor(tomove->current.gridl.Y + yoffset, tomove->current.gridl.X);
				printf("  ");
				add_to_taxi_list(destinationll, *tomove);
				delete_from_taxi_list(tomovellhead, * tomove);
			}
		}
	}
}



void taxi_parking_manager (taxis** tomovellhead, COORD destination, taxis* tomove) {

	if (tomove->battery >= lowbatterylevel) {
		add_to_taxi_list(&start_parked, *tomove);
		delete_from_taxi_list(&start_todestination, *tomove);
	}
	else {
		add_to_taxi_list(&start_tocharge, *tomove);
		delete_from_taxi_list(&start_todestination, *tomove);
	}
}


void taxi_movement_manager_3rd_step(taxis* taxi, COORD destination) {
	int distancey = destination.Y - taxi->current.gridl.Y;
	int distancex = destination.X - taxi->current.gridl.X;                                       // Find distance in x-axis


	if (distancex != ZERO) {
		move_taxi_once_in_x(taxi, distancex);
		taxi->battery--;
	}
	else {
		move_taxi_once_in_y(taxi, distancey);
		taxi->battery--;
	}
	if (distancex == -1) {		//IF TAXI IS MOVING LEFT, MOVE LEFT ONCE MORE AT INTERSECTION
		distancex--;
		move_taxi_once_in_x(taxi, distancex);
	}

}
