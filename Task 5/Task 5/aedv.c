/*
 - Linked list code
 - Code to sort list and print list
 - Two print routines are shown:
	- Print in sorted order
	- Print in reverse order using recursion.
 - ECED 3401
 - 29 Oct 2023
*/
#include "Structure_definition.h"

int x_offset = -8;
int y_offset = 4;


/*FUNCTION TO PRINT AEDVS IN LINKED LIST MAINLY USED TO TEST CODE*/
void print_aedv_list(aedv* start)
{
	/* Print from start to end of list */
	aedv* curr;

	curr = start;

	while (curr)
	{
		printf("%d\n", curr->VIN);
		printf("(%d,%d)\n", curr->current.gridl.X, curr->current.gridl.Y);
		printf("(%d,%d)\n", curr->source.gridl.X, curr->source.gridl.Y);	
		printf("(%d,%d)\n", curr->destination.gridl.X, curr->destination.gridl.Y);
		curr = curr->next;
	}
}

/*FUNCTION TO COPY AEDVS TYPE*/
void copy_aedv(aedv* old, aedv* new)
{
	new->VIN = old->VIN;

	new->current.buildingl = old->current.buildingl;
	new->current.gridl.X = old->current.gridl.X;
	new->current.gridl.Y = old->current.gridl.Y;

	new->current.buildingl = old->source.buildingl;
	new->source.gridl.X = old->source.gridl.X;
	new->source.gridl.Y = old->source.gridl.Y; 

	new->current.buildingl = old->destination.buildingl;
	new->destination.gridl.X = old->destination.gridl.X;
	new->destination.gridl.Y = old->destination.gridl.Y;
}


int add_to_aedv_list(aedv** start, aedv data)
{
	/*
	 - Create a node
	 - Address, not the contents, of the start of list is passed, allowing
		its contents to be modified if a new first entry is added to the list.
	 - Data[] is the address of the first byte of the word read.
	 - Return -1 if can't be created
	 - Return 0 if can be created
	*/


	aedv* new;                                     //POINTER TO NEW NODE CREATED
	aedv* curr;                                    //FIRST POINTER THAT POINTS TO CURRENT SELECTION IN THE LIST
	aedv* prev;                                    //SECOND POINTER THAT POINTS TO PREVIOUS SELECTION IN THE LIST


	new = malloc(sizeof(aedv));                    //ALLOCATE SPACE TO THE NEW NODE

	copy_aedv(&data, new);                          //COPY CONTENTS INTO THE NEW NODE
	new->next = NULL;;                              //SET POINTER TO NEXT NODE TO NULL


	curr = *start;                                  //SET CURRENT SELECTION TO START FROM THE POINTER TO THE FIRST NODE OR HEAD NODE
	prev = NULL;                                    //SET PREVIOUS SELECTION TO START FROM NULL AS THERE IS NO NODE BEFORE THE FIRST ONE


	/* Find position in list */
	while (curr != NULL && (curr->VIN != data.VIN)) //WHILE CURRENT SELECTION IS NOT NULL OR EMPTY
                                                    //AND
                                                    //WHILE THE VEHICLE IDENTIFICATION NUMBER OF THE CURRENT SELECTION IS NOT EQUAL TO
                                                    //THE VEHICALE IDENTIFICATION NUMBER OF THE AEDV DATA GIVEN
	{
		prev = curr;                                //MOVE SECOND POINTER TO CURRENT NODE
		curr = curr->next;                          //MOVE FIRST POINTER TO THE NEXT NODE
	}

	new->next = curr;                               //AFTER EITHER POSITION IS FOUND OR THE END OF LIST IS REACHED SET

	/* Insert new into list */
	if (prev == NULL)                             //IF THE NEW NODE IS THE FIRST NODE TO BE ENTERED
		*start = new;
	else
		prev->next = new;

	return 0;
}

void delete_from_aedv_list(aedv** head, aedv data)
{
	/*
	 - Remove word from list if it exists
	 - list points to start of list
	 - list is call-by-reference, so it can be changed
	 - word is the word to be removed from list (in an ENTRY)
	 - Steps if found:
		- curr is entry to be removed
		- prev is the entry before curr
		- unlink curr from list by prev->next = curr->next
		- return curr;
	 - If not in list, return NULL
	*/

	aedv* curr; // FIRST POINTER TO THE CURRENT NODE
	aedv* prev; // SECOND POINTER TO THE PREVIOUS NODE

	curr = *head;
	prev = NULL;

	/* Do while curr is not NULL */
	while (curr)
	{
		if (curr->VIN == data.VIN)
		{
			/* aedv found - break links */
			if (prev != NULL)
				/* Update prev's next */
				prev->next = curr->next;
			else
				/* Already first node */
				*head = curr->next;
		}
		/* Not in list, check next node */
		prev = curr;
		curr = curr->next;
	}
}


/*FUNCTION TO COUNT NUMBER OF AEDV IN A LINKED LIST. THIS IS USED MAINLY FOR CODE TESTING*/
int count_aedv(aedv* head) {

	int count = 0;                                  
	/*if (head == NULL)
		printf("Linked list is empty");*/
	aedv* ptr;
	ptr = head;

	while (ptr) {
		count++;
		ptr = ptr->next;
	}
	return count;
}

/*FUNCTION TO MOVE AEDVS ONCE, FIRST IN X DIRECTION AND THEN IN Y DIRECTION*/
void move_aedv_once(aedv* aedv, COORD destination) {

	int i, distancex, distancey;


                                                                                             // Move aedv along x axis
	distancex = destination.X - aedv->current.gridl.X;                                       // Find distance in x-axis



	if (distancex > 0) {                                                                     // MOVE RIGHT
		move_cursor(aedv->current.gridl.Y + yoffset, aedv->current.gridl.X);                 // postition cursor
		printf(" A%d ", (aedv->VIN - offsetid));                                             // print the aedv onto screen
		aedv->current.gridl.X++;
	}


	else if (distancex == 0) {                                                               // MOVE Y AXIS
		distancey = destination.Y - aedv->current.gridl.Y;

                                                                                             // MOVE DOWN
		if (distancey > 0) {
			move_cursor(aedv->current.gridl.Y + yoffset, aedv->current.gridl.X);             // increment cursor up every loop before printing
			printf("   ");
			move_cursor(aedv->current.gridl.Y + cursoroffset, aedv->current.gridl.X);        // increment cursor up every loop before printing
			printf("A%d", (aedv->VIN - offsetid));                                           // print the aedv onto screen
			aedv->current.gridl.Y++;
		}

		else if(distancey < 0) {                                                                               // MOVE UP

			move_cursor(aedv->current.gridl.Y, aedv->current.gridl.X);                       // postition cursor
			printf("A%d", (aedv->VIN - offsetid));                                           // print the aedv onto screen
			move_cursor(aedv->current.gridl.Y + yoffset, aedv->current.gridl.X);             // increment cursor down every loop before printing
			printf("   ");
			aedv->current.gridl.Y--;
		}
	}

	else {                                                                                   // MOVE LEFT
		move_cursor(aedv->current.gridl.Y + yoffset, aedv->current.gridl.X);                 // postition cursor
		printf("A%d ", (aedv->VIN - offsetid));                                              // print the aedv onto screen
		aedv->current.gridl.X--;
	}


}

void ask_for_source_and_destination(aedv* head, buildings* buildingz, int Numberofbuildings)
{

	aedv* curr_parked = head;
	int Text_Position_Y = buildingz[Numberofbuildings].B_address.Y + Voffset;
	int ask_for_whether_to_start_aedv = 1;

	while (curr_parked) {

		move_cursor(Text_Position_Y + cursoroffset, 0);
		printf("                                                  \n");
		printf("                                                  \n");
		printf("                                                  \n");
		printf("                                                  \n");
		printf("                                                  \n");
		printf("                                                  \n");

		move_cursor(Text_Position_Y + cursoroffset, 0);
		printf("Move AEDV%d?(0 for yes): ", curr_parked->VIN);
		scanf_s("%d", &ask_for_whether_to_start_aedv);

		move_cursor(Text_Position_Y + cursoroffset, 0);


		if (ask_for_whether_to_start_aedv == 0) {
			move_cursor(Text_Position_Y + cursoroffset, 0);

			printf("Enter pickup location of AEDV%d:            \n", curr_parked->VIN);
			printf("Enter destination location of AEDV%d:          ", curr_parked->VIN);

			move_cursor(Text_Position_Y + cursoroffset, 0);
			printf("Enter pickup location of AEDV%d: ", curr_parked->VIN);
			scanf_s("%d", &curr_parked->source.buildingl);


			if (curr_parked->source.buildingl <= Numberofbuildings && curr_parked->source.buildingl > 0) {

				printf("Enter destination location of AEDV%d:", curr_parked->VIN);
				scanf_s("%d", &curr_parked->destination.buildingl);


				if (curr_parked->destination.buildingl <= Numberofbuildings && curr_parked->destination.buildingl >= 0) {


					/*Set source for aedv from building location*/
					curr_parked->source.gridl.X = buildingz[curr_parked->source.buildingl].B_address.X + x_offset;
					curr_parked->source.gridl.Y = buildingz[curr_parked->source.buildingl].B_address.Y + y_offset;

					/*Set destination for aedv from building location*/
					curr_parked->destination.gridl.X = buildingz[curr_parked->destination.buildingl].B_address.X + x_offset;
					curr_parked->destination.gridl.Y = buildingz[curr_parked->destination.buildingl].B_address.Y + y_offset;


					add_to_aedv_list(&start_topickup, *curr_parked);
					delete_from_aedv_list(&start_parked, *curr_parked);

					curr_parked = curr_parked->next;                          //MOVE FIRST POINTER TO THE NEXT NODE

				}
				else {
					move_cursor(Text_Position_Y + y_offset, 0);

					printf("The building does not exist.");
				}
			}
			else {
				move_cursor(Text_Position_Y + y_offset, 0);

				printf("The building does not exist.");
			}
		}
		else {
			curr_parked = curr_parked->next;                          //MOVE FIRST POINTER TO THE NEXT NODE
		}

		
	}

}

/*FUNCTION TO ASK FOR USER INPUT FOR STARTING LOCATION OF AEDV*/
void ask_for_current_location(aedv* head, buildings* buildingz, int Numberofbuildings)
{
	int Text_Position_Y = buildingz[Numberofbuildings].B_address.Y + Voffset;
	int i;
	aedv aedv_;

	for (i = 1; i <= NumeroAEDV; i++) {

		move_cursor(Text_Position_Y + cursoroffset, 0);
		printf("                                        ");

		aedv_.VIN = i + offsetid;

		move_cursor(Text_Position_Y + cursoroffset, 0);

		printf("Enter the starting location for AEDV%d: ", i);
		scanf_s("%d", &aedv_.current.buildingl);

		if (aedv_.current.buildingl > Numberofbuildings) {
			i--;
			printf("The starting location does not exist on the Map");
		}

		else {

			// set current for aedv
			aedv_.current.gridl.X = buildingz[aedv_.current.buildingl].B_address.X+ x_offset;
			aedv_.current.gridl.Y = buildingz[aedv_.current.buildingl].B_address.Y+ y_offset;

			add_to_aedv_list(&start_parked, aedv_);
		}
	}
}

void aedv_movement_manager()
{
	aedv* curr_parked, * prev, * curr_topickup, * curr_todestination;


	while (start_topickup || start_todestination) {

		curr_topickup = start_topickup;
		curr_todestination = start_todestination;
		curr_parked = start_parked;

		while (curr_topickup || curr_todestination) {
			aedv_movement_manager_2nd_step(curr_topickup, start_topickup, start_todestination);
			aedv_movement_manager_2nd_step(curr_todestination, start_todestination, start_parked);
			print_current_destination(curr_parked, start_parked);
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
		Sleep(100);                                                                          // add delay to show the aedv moving

	}
}

void print_current_destination(aedv* tomove, aedv* tomovellhead) {
	if (tomovellhead) {
		if (tomove == NULL) {
			tomove = tomovellhead;
		}
		move_cursor(tomove->current.gridl.Y+1, tomove->current.gridl.X);                       // postition cursor
		printf("A%d", (tomove->VIN - offsetid));                                           // print the aedv onto screen
	}
}


int get_map_size(int* street, int* avenue)
{
	printf("Enter Number of streets [Maximum 5]: ");
	scanf_s("%d", street);

	printf("Enter Number of avenues [Maximum 5]: ");
	scanf_s("%d", avenue);

    if (*street > MAXMAP || *avenue > MAXMAP)
	{
	printf("Error: Number of streets or avenues were more than %d\n", MAXMAP);
	return -1;
	}


	return 0;
}

void check_if_to_run_emulation_of_aedv_input(int* check_if_to_run_emulation_of_aedv, int Text_Position_Y)
{
	// Ask user if they want to continue
	move_cursor(Text_Position_Y, 0);
	printf_s("move AEDV? (0 for yes and 1 for no) ");
	scanf_s("%d", check_if_to_run_emulation_of_aedv);
	move_cursor(Text_Position_Y + 10, 0);
}

void aedv_movement_manager_2nd_step(aedv* tomove, aedv* tomovellhead, aedv* destinationll)
{

	if (tomovellhead) {
		if (tomove == NULL) {
			tomove = tomovellhead;
		}

		/*MOVE AND TRANSFER LINKED LISTS IF SOURCE IS REACHED*/
		if (tomovellhead == start_topickup) {
			move_aedv_once(tomove, tomove->source.gridl);
			if (tomove->current.gridl.X == tomove->source.gridl.X) {
				if (tomove->current.gridl.Y == tomove->source.gridl.Y) {
					add_to_aedv_list(&start_todestination, *tomove);
					delete_from_aedv_list(&start_topickup, *tomove);
				}
			}

		}
		/*MOVE AND TRANSFER LINKED LISTS IF DESTINATION IS REACHED*/
		else if (tomovellhead == start_todestination) {
			move_aedv_once(tomove, tomove->destination.gridl);
			if (tomove->current.gridl.X == tomove->destination.gridl.X) {
				if (tomove->current.gridl.Y == tomove->destination.gridl.Y) {
					add_to_aedv_list(&start_parked, *tomove);
					delete_from_aedv_list(&start_todestination, *tomove);
				}
			}
		}
	}
}

