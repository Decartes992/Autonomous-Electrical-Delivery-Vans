/*MODULE: TAXI
*
* WHAT IT DOES: THIS TAXI.H AND TAXI.C FILES ACHEIVE THE PURPOSE OF HANDLING
* THE REQUIRED FUNCTIONS FOR USING LINKED LISTS OF TYPE TAXI.
* LINKED LIST HEADERS ARE ALSO DEFINED HERE.
* 
*  - Linked list code
   - Code to sort list and print list
   - Two print routines are shown:
   - Print in sorted order
*
* DATE: 10-10-2022
*
* NAME:
* IFTEKHAR RAFI
* MAZEN
*
*/

#include "Taxi.h"


/*FUNCTION TO COPY TAXIS TYPE*/
void copy_taxi(taxis* old, taxis* new)
{
	new->VIN = old->VIN;
	new->battery = old->battery;
	new->status = old->status;
	new->ordertime = old->ordertime;


	new->current.buildingside = old->current.buildingside;
	new->current.buildingl = old->current.buildingl;
	new->current.gridl.X = old->current.gridl.X;
	new->current.gridl.Y = old->current.gridl.Y;

	new->source.buildingside = old->source.buildingside;
	new->source.buildingl = old->source.buildingl;
	new->source.gridl.X = old->source.gridl.X;
	new->source.gridl.Y = old->source.gridl.Y; 
	new->source.intersection_location.X = old->source.intersection_location.X;
	new->source.intersection_location.Y = old->source.intersection_location.Y;

	new->destination.buildingside = old->destination.buildingside;
	new->destination.buildingl = old->destination.buildingl;
	new->destination.gridl.X = old->destination.gridl.X;
	new->destination.gridl.Y = old->destination.gridl.Y;
	new->destination.intersection_location.X = old->destination.intersection_location.X;
	new->destination.intersection_location.Y = old->destination.intersection_location.Y;
}


/* COPY DATA OF DATA TYPE taxis OF ONLY ORDERTIME PICKUP AND DESTINATION FOR READING ORDERS FILE*/
void copy_taxi_source_destination(taxis* old, taxis* new)
{
	new->ordertime = old->ordertime;


	new->source.buildingside = old->source.buildingside;
	new->source.buildingl = old->source.buildingl;
	new->source.gridl.X = old->source.gridl.X;
	new->source.gridl.Y = old->source.gridl.Y;
	new->source.intersection_location.X = old->source.intersection_location.X;
	new->source.intersection_location.Y = old->source.intersection_location.Y;

	new->destination.buildingside = old->destination.buildingside;
	new->destination.buildingl = old->destination.buildingl;
	new->destination.gridl.X = old->destination.gridl.X;
	new->destination.gridl.Y = old->destination.gridl.Y;
	new->destination.intersection_location.X = old->destination.intersection_location.X;
	new->destination.intersection_location.Y = old->destination.intersection_location.Y;
}

int add_to_taxi_list(taxis** start, taxis data)
{
	/*
	 - Create a node
	 - Address, not the contents, of the start of list is passed, allowing
		its contents to be modified if a new first entry is added to the list.
	 - Data[] is the address of the first byte of the word read.
	 - Return -1 if can't be created
	 - Return 0 if can be created
	*/


	taxis* new;                                     //POINTER TO NEW NODE CREATED
	taxis* curr;                                    //FIRST POINTER THAT POINTS TO CURRENT SELECTION IN THE LIST
	taxis* prev;                                    //SECOND POINTER THAT POINTS TO PREVIOUS SELECTION IN THE LIST


	new = malloc(sizeof(taxis));                    //ALLOCATE SPACE TO THE NEW NODE

	copy_taxi(&data, new);                          //COPY CONTENTS INTO THE NEW NODE
	new->next = NULL;;                              //SET POINTER TO NEXT NODE TO NULL


	curr = *start;                                  //SET CURRENT SELECTION TO START FROM THE POINTER TO THE FIRST NODE OR HEAD NODE
	prev = NULL;                                    //SET PREVIOUS SELECTION TO START FROM NULL AS THERE IS NO NODE BEFORE THE FIRST ONE


	/* Find position in list */
	while (curr != NULL && (curr->VIN != data.VIN)) //WHILE CURRENT SELECTION IS NOT NULL OR EMPTY
                                                    //AND
                                                    //WHILE THE VEHICLE IDENTIFICATION NUMBER OF THE CURRENT SELECTION IS NOT EQUAL TO
                                                    //THE VEHICALE IDENTIFICATION NUMBER OF THE TAXI DATA GIVEN
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

void delete_from_taxi_list(taxis** head, taxis data)
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

	taxis* curr; // FIRST POINTER TO THE CURRENT NODE
	taxis* prev; // SECOND POINTER TO THE PREVIOUS NODE

	curr = *head;
	prev = NULL;

	/* Do while curr is not NULL */
	while (curr)
	{
		if (curr->VIN == data.VIN)
		{
			/* taxi found - break links */
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



