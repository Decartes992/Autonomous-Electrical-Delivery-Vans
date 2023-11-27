#include "UI_Manager.h"


/*MODULE: UI_MANAGER
*
* WHAT IT DOES:THE UI MANAGER MODULE IS PURPOSED TO HANDLE IO TO THE CONSOLE
* AND FOR ASSIGNING ORDERS TO THE AEDVS
*
* DATE: 10-11-2022
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/


HANDLE Console; /* Identify action and I/O stream */


FILE* tfd;
FILE* activevehicle;
FILE* orders;
FILE* map;
FILE* chargingandparking;

int activeVIN[ACTIVEVEHICLECOUNT];

aedvs* start_topark;
aedvs* start_topark_intersection;

aedvs* start_parked;

aedvs* start_topickup_intersection;
aedvs* start_topickup;

aedvs* start_todestination_intersection;
aedvs* start_todestination;

aedvs* start_tocharge_intersection;
aedvs* start_tocharge;

aedvs* start_charging;
aedvs* start_charging;

void UI_Manager(int argc, char* argv[]) {
	int whichinput = ZERO, emulationorfilemanagement = ZERO;
	COORD scrsize;

	/* For console output via Windows */
	Console = GetStdHandle(STD_OUTPUT_HANDLE);

	/* Determine screen size */
	scrsize = GetLargestConsoleWindowSize(Console);
	printf("Size: r: %d c: %d\n", scrsize.Y, scrsize.X);

	printf("Press 0 to run emulation, Press 1 for file management: ");
	scanf_s("%d", &emulationorfilemanagement);
	getchar();


	if (emulationorfilemanagement == ZERO) {
		printf("Press 0 for user-input, 1 for file-input: ");

		scanf_s("%d", &whichinput);
		getchar();

		if (whichinput == ZERO) {
			take_user_input();
		}
		else if (whichinput == 1) {
			take_file_input(argc, argv);
		}
	}
	else if (emulationorfilemanagement == 1) {
		file_manager(argc, argv);
	}


}

void take_user_input() {
	/*VARIABLE DECLARATION*/
	int street = ZERO, avenue = ZERO, check_if_to_run_emulation_of_aedvs = ZERO;
	int i, Numberofbuildings, Text_Position_Y;

	check_if_to_run_emulation_of_aedvs = get_map_size(&street, &avenue);
	if (check_if_to_run_emulation_of_aedvs != ZERO) {
		return -1;
	}

	draw_map(street, avenue);

	Numberofbuildings = street * avenue;
	Text_Position_Y = buildingz[Numberofbuildings].B_address.Y + Voffsetfortext;

	ask_for_current_location(start_parked, buildingz, Numberofbuildings);

	while (check_if_to_run_emulation_of_aedvs == ZERO) {

		/*ASSIGN NEW RIDE ORDER TO PARKED AEDVS*/
		ask_for_source_and_destination_and_assign_parking_location(start_parked, buildingz, Numberofbuildings);

		/*MOVE ALL AEDVS AT ONCE*/
		aedv_movement_manager();

		check_if_to_run_emulation_of_aedvs_input(&check_if_to_run_emulation_of_aedvs, Text_Position_Y);
	}

}

/*FUNCTION TO GET NUMBER OF STREETS AND AVENUES*/
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


	return ZERO;
}

/*FUNCTION TO SEE WHETHER TO CONTINUE EMULATION*/
void check_if_to_run_emulation_of_aedvs_input(int* check_if_to_run_emulation_of_aedvs, int Text_Position_Y)
{
	// Ask user if they want to continue
	CUP(Indent_location, Text_Position_Y)
		printf("move aedvs? (0 for yes and 1 for no) ");
	scanf_s("%d", check_if_to_run_emulation_of_aedvs);
	getchar();
}

/*FUNCTION TO ASK FOR USER INPUT FOR STARTING LOCATION OF AEDVS*/
void ask_for_current_location(aedvs* head, buildings* buildingz, int Numberofbuildings)
{
	int Text_Position_Y = buildingz[Numberofbuildings].B_address.Y + Voffsetfortext;
	int i;
	aedvs aedv_;
	int x_current_offset = ZERO, y_current_offset = ZERO;

	for (i = 1; i <= NumeroAEDV; i++) {

		CUP(Indent_location, Text_Position_Y + cursoroffset);
			printf("                                                                                                           \n");
			printf("                                                                                                           \n");
			printf("                                                                                                           \n");
			printf("                                                                                                           \n");


		aedv_.VIN = i + offsetid;

		CUP(Indent_location, Text_Position_Y + cursoroffset);

		printf("Enter the starting location for AEDV%d: \n", i);
		printf("Enter source building side of AEDV%d: \n", i);
		printf("For buildingside: Enter 1 for NW, 2 for N, 3 for NE, 4 for W, 5 for E, 6 for SE, 7 for S, 8 for SE \n");

		CUP(Indent_location, Text_Position_Y + cursoroffset);

		printf("Enter the starting location for AEDV%d: ", i);
		scanf_s("%d", &aedv_.current.buildingl);
		printf("Enter source building side of AEDV%d: ", i);
		scanf_s("%d", &aedv_.current.buildingside);


		if (aedv_.current.buildingl > Numberofbuildings) {
			i--;
			printf("The starting location does not exist on the Map");
		}

			
		else {
			get_offset(aedv_.current.buildingside, &x_current_offset, &y_current_offset);

			// set current for AEDV
			aedv_.current.gridl.X = buildingz[aedv_.current.buildingl].B_address.X + x_current_offset;
			aedv_.current.gridl.Y = buildingz[aedv_.current.buildingl].B_address.Y + y_current_offset;

			aedv_.battery = 100; //FULL BATTERY = 100%

			add_to_aedv_list(&start_parked, aedv_);
		}
	}
}

/*FUNCTION TO GET SOURCE AND DESTINATION LOCATION AND SET PARKING LOCATION*/
void ask_for_source_and_destination_and_assign_parking_location(aedvs* head, buildings* buildingz, int Numberofbuildings)
{

	aedvs* curr_parked = head;
	int Text_Position_Y = buildingz[Numberofbuildings].B_address.Y + Voffsetfortext;
	int ask_for_whether_to_start_aedv = 1;


	while (curr_parked) {
		CUP(Indent_location, Text_Position_Y + cursoroffset)
			printf("                                                                                                                   \n");
			printf("                                                                                                                   \n");
			printf("                                                                                                                   \n");
			printf("                                                                                                                   \n");
			printf("                                                                                                                   \n");
			printf("                                                                                                                   \n");
			printf("                                                                                                                   \n");

		CUP(Indent_location, Text_Position_Y + cursoroffset);
			printf("Move AEDV%d?(0 for yes): ", curr_parked->VIN);
		scanf_s("%d", &ask_for_whether_to_start_aedv);

		CUP(Indent_location, Text_Position_Y + cursoroffset);


		if (ask_for_whether_to_start_aedv == ZERO) {
			
			CUP(Indent_location, Text_Position_Y + cursoroffset);
				printf("Enter pickup location of AEDV%d:                   \n", curr_parked->VIN);
				printf("Enter source building side of AEDV%d:              \n", curr_parked->VIN);

				printf("Enter destination location of AEDV%d:              \n", curr_parked->VIN);
				printf("Enter destination building side of AEDV%d:         \n", curr_parked->VIN);
				printf("For buildingside: Enter 1 for NW, 2 for N, 3 for NE, 4 for W, 6 for E, 7 for SE, 8 for S, 9 for SE");

			CUP(Indent_location, Text_Position_Y + cursoroffset);
				printf("Enter pickup location of AEDV%d: ", curr_parked->VIN);
			scanf_s("%d", &curr_parked->source.buildingl);
				printf("Enter source building side of AEDV%d: ", curr_parked->VIN);
			scanf_s("%d", &curr_parked->source.buildingside);

			if (curr_parked->source.buildingl <= Numberofbuildings && curr_parked->source.buildingl > ZERO) {

				printf("Enter destination location of AEDV%d:", curr_parked->VIN);
				scanf_s("%d", &curr_parked->destination.buildingl);
				printf("Enter destination building side of AEDV%d: ", curr_parked->VIN);
				scanf_s("%d", &curr_parked->destination.buildingside);

				set_location(curr_parked);

				if (curr_parked->destination.buildingl <= Numberofbuildings && curr_parked->destination.buildingl >= ZERO) {

					add_to_aedv_list(&start_topickup_intersection, *curr_parked);
					delete_from_aedv_list(&start_parked, *curr_parked);

					curr_parked = curr_parked->next;                          //MOVE FIRST POINTER TO THE NEXT NODE

				}
				else {
					printf("The building does not exist.");
				}
			}
			else {
				printf("The building does not exist.");
			}
		}
		else {
			curr_parked = curr_parked->next;                          //MOVE FIRST POINTER TO THE NEXT NODE
		}
	}
}

/*FUNCTION TO SET THE SOURCE AND DESTINATION LOCATION OF AEDV*/
void set_location(aedvs* curr_parked) {
	int x_source_offset = ZERO, y_source_offset = ZERO, x_destination_offset = ZERO, y_destination_offset = ZERO;
	int dist_topickup_x = ZERO, dist_topickup_y = ZERO, dist_todestination_x = ZERO, dist_todestination_y = ZERO;

	get_offset(curr_parked->source.buildingside, &x_source_offset, &y_source_offset);

	get_offset(curr_parked->destination.buildingside, &x_destination_offset, &y_destination_offset);


	/*Set source for AEDV from building location*/
	curr_parked->source.gridl.X = buildingz[curr_parked->source.buildingl].B_address.X + x_source_offset;
	curr_parked->source.gridl.Y = buildingz[curr_parked->source.buildingl].B_address.Y + y_source_offset;

	/*Set destination for AEDV from building location*/
	curr_parked->destination.gridl.X = buildingz[curr_parked->destination.buildingl].B_address.X + x_destination_offset;
	curr_parked->destination.gridl.Y = buildingz[curr_parked->destination.buildingl].B_address.Y + y_destination_offset;

	/*Set intersection location for pickup location*/
	curr_parked->source.intersection_location.X = curr_parked->source.gridl.X;
	curr_parked->source.intersection_location.Y = curr_parked->source.gridl.Y;
	
	/*Calculate distance*/
	dist_topickup_x = curr_parked->source.gridl.X - curr_parked->current.gridl.X;
	dist_topickup_y = curr_parked->source.gridl.Y - curr_parked->current.gridl.Y;

	/*SETTING STARTING LOCATION*/
	/*North-East*/
	if (curr_parked->source.buildingside == NE) {

		/*MOVING LEFT*/
		if (dist_topickup_x < ZERO) {
			curr_parked->current.gridl.Y++; //--
		}
	}
	/*North-West*/
	else if (curr_parked->source.buildingside == NW) {
		/*MOVING LEFT*/
		if (dist_topickup_x < ZERO) {
			curr_parked->current.gridl.Y++;//--
		}
		if (dist_topickup_x > ZERO) {
			if (dist_topickup_y != ZERO) {
				curr_parked->source.intersection_location.X = curr_parked->source.gridl.X - intersection_increment_x;
				curr_parked->source.intersection_location.Y = curr_parked->source.gridl.Y;
			}
		}
	}
	/*South-East*/
	else if (curr_parked->source.buildingside == SE) {
		/*MOVING RIGHT*/
		if (dist_topickup_x > ZERO) {
			curr_parked->current.gridl.Y--;//++
		}
	}
	/*South-West*/
	else if (curr_parked->source.buildingside == SW) {
		/*MOVING RIGHT*/
		if (dist_topickup_x > ZERO) {
			curr_parked->current.gridl.X--; //++
		}
	}





	/*SETTING PICKUP LOCATION*/
	/*MOVING RIGHT*/
	if (dist_topickup_x > ZERO) {
		/*MOVING UP*/
		if (dist_topickup_y < ZERO) {
			curr_parked->source.gridl.X ++;
		}
	}
	else if (dist_topickup_x < ZERO) {
		/*MOVING DOWN*/
		if (dist_topickup_y > ZERO) {
			curr_parked->source.gridl.X -= 2; //DECREMENT BY 2 TO OFFSET IN MAP
		}
	}
#ifdef DEBUG

	dist_todestination_x = curr_parked->source.gridl.X;
	dist_todestination_y = curr_parked->source.gridl.Y;

	/*SETTING DESTINATION LOCATION*/
	/*MOVING RIGHT*/
	if (dist_topickup_x > ZERO) {
		/*MOVING UP*/
		if (dist_topickup_y < ZERO) {
			curr_parked->source.gridl.X++;
		}
	}
	else if (dist_topickup_x < ZERO) {
		/*MOVING DOWN*/
		if (dist_topickup_y > ZERO) {
			curr_parked->source.gridl.X--;
		}
	}

#endif // DEBUG

}

void get_offset(int comparator, int* x_offset, int* y_offset)
{

	/*North*/
	if (comparator == NE) {
		*x_offset = x_NE;
		*y_offset = y_NE;
	}
	/*South*/
	else if (comparator == NW) {
		*x_offset = x_NW;
		*y_offset = y_NW;
	}
	/*West*/
	else if (comparator == SE) {
		*x_offset = x_SE;
		*y_offset = y_SE;
	}
	else if (comparator == SW) {
		*x_offset = x_SW;
		*y_offset = y_SW;
	}
	else if (comparator == N)
	{
		*x_offset = x_N;
		*y_offset = y_N;
	}
	else if (comparator == E)
	{
		*x_offset = x_E;
		*y_offset = y_E;
	}
	else if (comparator == W)
	{
		*x_offset = x_W;
		*y_offset = y_W;
	}
	else if (comparator == S)
	{
		*x_offset = x_S;
		*y_offset = y_S;
	}
}


void print_current_destination(aedvs* tomove, aedvs* tomovellhead) {
	if (tomovellhead) {
		if (tomove == NULL) {
			tomove = tomovellhead;
		}
		CUP(tomove->current.gridl.X, tomove->current.gridl.Y + 1);                       // postition cursor
			printf("%d", (tomove->VIN - offsetid));                                           // print the AEDV onto screen
			printf(CSI "?25l");	/* Hide cursor */
	}
}



void take_file_input(int argc, char* argv[]) {
	int street, avenue, Numberofbuildings;

	getmapsize(&street, &avenue);
	draw_map(street, avenue);
	Numberofbuildings = street * avenue;


	printf("\n");

	read_ordersfile(&start_orders);

	read_activevehicle(&start_active);
	if (open_file(argc, argv, TRUE))
	{

			/*Read*/
			/* File exists -- process records */
			//sequential_access();
			/* Access any record */
			aedv_initiator();

			/* Close opened file -- will occur by default when file closes */
			fclose(tfd);

			getchar();
		}

	while (start_orders) {

		/*ASSIGN NEW RIDE ORDER TO PARKED AEDVS*/
		set_source_and_destination_and_assign_parking_location(start_parked, buildingz, Numberofbuildings);

		/*MOVE ALL AEDVS AT ONCE*/
		aedv_movement_manager();

	}
	getchar();
}

void set_source_and_destination_and_assign_parking_location(aedvs* head, buildings* buildingz, int Numberofbuildings)
{
	int mindist, dist;
	aedvs* curr_parked = start_parked;
	aedvs* cur_order = start_orders;

	mindist = sqrt(squareOfNumber(cur_order->source.gridl.Y - curr_parked->current.gridl.Y) + squareOfNumber(cur_order->source.gridl.X - curr_parked->current.gridl.X));
	while (cur_order && head) {
		curr_parked = start_parked;
		while (curr_parked) {
			dist = sqrt(squareOfNumber(cur_order->source.gridl.Y - curr_parked->current.gridl.Y) + squareOfNumber(cur_order->source.gridl.X - curr_parked->current.gridl.X));
			if (mindist > dist) {
				cur_order->VIN = curr_parked->VIN;
			}
			curr_parked = curr_parked->next;
		}
		curr_parked = head;
		while (curr_parked) {
			if (curr_parked->VIN == cur_order->VIN) {
				cur_order->VIN = ZERO;
				
				copy_aedv_source_destination(cur_order, curr_parked);
				set_location(curr_parked);

				add_to_aedv_list(&start_topickup_intersection, *curr_parked);
				delete_from_aedv_list(&start_parked, *curr_parked);
				delete_from_aedv_list(&start_orders, *cur_order);

			}
			curr_parked = curr_parked->next;
		}
		cur_order = cur_order->next;
	}
}

int squareOfNumber(int num){
	return (num * num);
}