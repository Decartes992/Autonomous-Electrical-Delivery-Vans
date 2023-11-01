/*The file manager file contains all functions related to accessing, reading, writing,
* initializing and updating files.  
* 
* 
* 
*/

/*MODULE: FILE_MANAGER
*
* WHAT IT DOES:THE FILE MANAGER MODULE IS PURPOSED TO HANDLE IO RELATED TO FILES
* AND FOR ASSIGNING ORDERS TO THE TAXIS
*
* DATE: 10-11-2022
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM
*
*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>     /* for _O_TEXT and _O_BINARY */
#include "File_Manager.h"

FILE* tfd;  /* Taxi file file-descriptor */
FILE* activevehicle; /*Active taxi file*/
taxis* start_orders;
taxis* start_active;
FILE* orders;
FILE* map;
FILE* chargingandparking;
clock_t start, currenttime, end;
int activeVIN[ACTIVEVEHICLECOUNT];

void file_manager(int argc, char* argv[])
{
	int street, avenue, go_back_to_menu;
	int CONTINUE = 1, rwu = 0, ans, check_if_to_run_emulation_of_taxis = 0;
	getmapsize(&street, &avenue);
	dud_map(street, avenue);

	/* Open a file for initialization */

	do {
		printf("Press 0 to Read, 1 to Write, 2 to Update, 3 to Delete, or 4 to Initiatlize a new file: ");
		scanf_s("%d", &rwu);
		getchar();
		if (rwu == 4 || open_file(argc, argv, TRUE) )
		{

			/*Read*/
			if (rwu == 0) {
				/* File exists -- process records */
				sequential_access();
				/* Access any record */
				rel_read();

				/* Close opened file -- will occur by default when file closes */
				fclose(tfd);

				getchar();
			}
			/*Write*/
			else if (rwu == 1) {

				/* Add at least one taxi */
				do
				{
					add_taxi(tfd);
					printf("Add another (1 - yes 0 - no)\n");
					scanf_s("%d", &ans);
					getchar();
				} while (ans == 1);

				/* Now print contents */
				sequential_access();

				fclose(tfd);
				getchar();

			}
			/*Update*/
			else if (rwu == 2) {

				/* File exists -- process records */
				printf("Original contents\n");
				sequential_access();

				rel_update();

				printf("Updated contents\n");
				sequential_access();

				/* Close opened file -- will occur by default when file closes */
				fclose(tfd);

				getchar();
			}
			else if (rwu == 3) {

				/* File exists -- process records */
				printf("Original contents\n");
				sequential_access();

				rel_delete();

				printf("Updated contents\n");
				sequential_access();

				/* Close opened file -- will occur by default when file closes */
				fclose(tfd);
			}

			else if (rwu == 4)
			{
				printf("Initialize File? Enter 0 for yes: ");
				scanf_s("%d", &CONTINUE);
				getchar();

				if (CONTINUE == 0) {
					if (open_file(argc, argv, FALSE))
					{
						init_file();

						sequential_access();

						fclose(tfd);
					}
				}

			}
		}
		printf("Open Another File?Enter 0 for yes: ");
		scanf_s("%d", &CONTINUE);
		getchar();
		system("cls");
	} while (CONTINUE == 0);

	printf("Enter 0 to go back to menu, 1 to restart file manager: ");
	scanf_s("%d", &go_back_to_menu);

	system("cls");
	if (go_back_to_menu == 0) {
		UI_Manager(argc,argv);
	}
	else if (go_back_to_menu == 1) {
		file_manager(argc, argv);
	}


	getchar();
}
void init_file()
{

	/*
	 - Initialize header:
	   - No deleted records
	   - First available record is 1
	*/
	SFREC header;

	printf("Start of initialization\n");

	header.hrec.del_rec_list = DEL_END;	/* Deleted list is empty */
	header.hrec.first_VIN = 1;	    	/* First record is 1000*/

	/* Default opening record is 0 (Header) */
	fseek(tfd, 0, SEEK_SET);

	fwrite(&header, sizeof(SFREC), 1, tfd);

	printf("End of intialization\n");
}
int open_file(int argc, char* argv[], int must_exist)
{
	/*
	 - opens or creates a file for reading and writing
	 - if must_exist is TRUE, the file must exist in order to proceed
	 - if must_exist is FALSE, the file must not exist in order to proceed
	 - returns TRUE if successful, FALSE otherwise
	*/
	char fname[NAMELEN];

	/* Set file access mode */
	_set_fmode(_O_BINARY);

	if (must_exist)
	{
		/* File must exist - does it? */
		if (argc == 1)
		{
			/*
			 - File must exist but wasn't supplied
			 - Ask for name
			*/
			printf("Name required - Enter name of taxi file\n");
			fgets(fname, NAMELEN, stdin);
			TRUNCATE(fname);
			/*
			 - Try to open for reading and writing
			 - = 0: open; !=0: can't open
			*/
			return (tfd = fopen(fname, "r+")) != NULL;
		}
		/*
		 - Presumably exists - check argv[1]
		 - If can open file for reading and writing ("r+"), return TRUE
		   otherwise FALSE
		*/
		return (tfd = fopen(argv[1], "r+")) != NULL;
	}

	/* File must not exist */
	if (argc > 1){		
		/* File supplied */
		return FALSE;
	}


	/*
	 - argc = 1
	 - ask for new file
	*/
	printf("Enter name of taxi file\n\n");
	fgets(fname, NAMELEN, stdin);
	TRUNCATE(fname);
	/* Try to open for reading and writing */
	return (tfd = fopen(fname, "w+")) != NULL;
}
void sequential_access()
{
	/* Read the fixed-length taxi file sequentially */
	SFREC taxi_rec;
	HEADER header_rec;
	long taxirec_no, adjustedcount;

	/* Position file pointer to start-of-file (header) */
	fseek(tfd, 0, SEEK_SET);

	/*
	 - Read header record - in zeroth record
	 - Indicates first available taxi id
	*/
	fread(&header_rec, sizeof(HEADER), 1, tfd);

	printf("Header:\nFirst available VIN: %u\n\n", header_rec.first_VIN + VINADJUST);

	if (header_rec.first_VIN == 1)
	{
		printf("File is empty, nothing to display\n");
		return;
	}

	/* Position file pointer to first possible taxi record */
	fseek(tfd, sizeof(SFREC), SEEK_SET);

	/*
	 * Read taxis records:
	 * Limit is first available taxi id (from header)
	 * Read will be successful (non-zero return value) until end-of-file,
	   when a zero value is returned, causing the while to terminate
	*/

	taxirec_no = 1; /* Default first record */
	adjustedcount = header_rec.first_VIN + VINADJUST;
	while (taxirec_no < adjustedcount &&	fread(&taxi_rec, sizeof(SFREC), 1, tfd))
	{
		switch (taxi_rec.taxirec.status)
		{
		case ACTIVE:
			/* Active record */
			printf("%3d Active ID: %4d, Battery: %d%%, Current location: Building Number: %d , Building side: %d Location: (%d,%d)\n", taxirec_no, taxi_rec.taxirec.VIN, taxi_rec.taxirec.battery, taxi_rec.taxirec.current.buildingl, taxi_rec.taxirec.current.buildingside, taxi_rec.taxirec.current.gridl.X, taxi_rec.taxirec.current.gridl.Y);
			break;
		case DELETED:
			/* Deleted record */
			break;
		default:
			printf("%3d Invalid record: Status: %d\n", taxirec_no, taxi_rec.taxirec.status);
		}
		taxirec_no++; /* Walk through sequentially */
	}

	/* Print list of deleted record */
	if (header_rec.del_rec_list == DEL_END)
		printf("No deleted records in file\n");
	else
	{
		/* At least one deleted record */
		taxirec_no = header_rec.del_rec_list; /* First in list */
		do
		{
			printf("Record: %d deleted\n", taxirec_no);
			/* Get next deleted record from current deleted record */
			fseek(tfd, taxirec_no * sizeof(SFREC), SEEK_SET);
			fread(&taxi_rec, sizeof(SFREC), 1, tfd);
			taxirec_no = taxi_rec.drec.next_deleted;
		} while (taxirec_no != DEL_END);
	}
}
void rel_read()
{
	/* Access any taxi record regardless of its location in the
	   file (direct/relative access).
	 * Limited by number of possible taxis (from header record)
	 * This is *not* accessing records using the taxi number, instead
	   it is using the record number.  How to access using a key other than
	   the record number will be discussed in class.
	*/
	SFREC taxi_rec;
	HEADER hrec;
	long rec_no, adjustedcount;

	/* Read header, indicates last allowable record */
	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);
	adjustedcount = hrec.first_VIN + VINADJUST;
	do
	{
		printf("Enter taxi record number (0 to end)\n");
		scanf_s("%d", &rec_no);
		getchar();
		/* Valid record? */
		if (rec_no >= hrec.first_VIN)
			printf("Invalid record: %u\n", rec_no);
		else
			if (rec_no > 0)
			{
				/* Position file to record */
				fseek(tfd, rec_no * sizeof(SFREC), SEEK_SET);
				/*
				 - Once the file pointer is moved, the record, if it exists,
				   is read.
				*/
				fread(&taxi_rec, sizeof(taxis), 1, tfd);
				/* Record exists - is it active? */
				if (taxi_rec.taxirec.status == ACTIVE)
				{
					/* Active record */
					printf("%3d Active ID: %4d, Battery: %3d%%, Current location: Building Number: %d , Building side: %d Location: (%d,%d)\n", rec_no, taxi_rec.taxirec.VIN, taxi_rec.taxirec.battery, taxi_rec.taxirec.current.buildingl, taxi_rec.taxirec.current.buildingside, taxi_rec.taxirec.current.gridl.X, taxi_rec.taxirec.current.gridl.Y);

				}
				else
					printf("Not active record %3d\n", rec_no);
			}
	} while (rec_no > 0);

	printf("Reading finished\n");

}
void add_taxi(FILE* tfd)
{
	/* Add a taxi to the taxi file */
	DEL_TAXI deltaxi;
	SFREC newtaxi;
	HEADER hrec;
	long del_rec_no;
	long VIN;
	int x_current_offset = 0, y_current_offset = 0;
	/* Access header record to get first available taxi id */
	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);

	/*
	 - Check if a deleted record is available
	 - If so, this will become the new VIN to use
	*/
	if ((del_rec_no = hrec.del_rec_list) != DEL_END)
	{
		/* At least one deleted record exists */
		if (fseek(tfd, del_rec_no * sizeof(SFREC), SEEK_SET) < 0)
		{
			printf("Invalid deleted record number\n");
			getchar();
			return;
		}
		/* Read deleted taxi record to get next deleted */
		fread(&deltaxi, sizeof(DEL_TAXI), 1, tfd);
		/* Update del_rec_list in header */
		hrec.del_rec_list = deltaxi.next_deleted;
		/*
		 - del_rec_no is the number of the to-be-reused record
		 - VIN is now del_rec_no
		 - Header (hrec) is updated with next del_rec_list (below)
		*/
		printf("Reusing deleted taxi id: %u\n", del_rec_no);
		VIN = del_rec_no;
	}
	else
	{
		/*
		 - No deleted records - get new VIN
		 - Get taxi information
		 - VIN is used as offset - keep in range
		*/
		printf("New taxi id is: %u\n", hrec.first_VIN);
		VIN = hrec.first_VIN + VINADJUST;
	}

	/* Move to taxi record (new or formerly deleted) */
	if (fseek(tfd, (VIN - VINADJUST) * sizeof(SFREC), SEEK_SET) < 0)
	{
		printf("Invalid VIN\n");
		getchar();
		return;
	}
	/*
	 * Record positioned to new record
	 * Read data and write to file
	*/
	/* Get record */
	printf("Enter starting building number\n");
	scanf_s("%d", &newtaxi.taxirec.current.buildingl);
	printf("Enter starting building side\n");
	scanf_s("%d", &newtaxi.taxirec.current.buildingside);
	printf("Enter Battery Percentage (Number Only): \n");
	scanf_s("%d", &newtaxi.taxirec.battery);



	/* Complete remaining fields */
	newtaxi.taxirec.VIN = VIN;
	newtaxi.taxirec.status = ACTIVE;

	get_offset(newtaxi.taxirec.current.buildingside, &x_current_offset, &y_current_offset);
	newtaxi.taxirec.current.gridl.X = buildingz[newtaxi.taxirec.current.buildingl].B_address.X + x_current_offset;
	newtaxi.taxirec.current.gridl.Y = buildingz[newtaxi.taxirec.current.buildingl].B_address.Y + y_current_offset;

	/* Display complete record */
	printf("ID: >%d< BN: >%d< BS: >%d<\n", newtaxi.taxirec.VIN, newtaxi.taxirec.current.buildingl, newtaxi.taxirec.current.buildingside);
	/*
	 - Write taxi data to taxi file
	 - File pointer was positioned to taxi record
	   with fseek() above
	*/
	fwrite(&newtaxi, sizeof(SFREC), 1, tfd);
	/*
	 - first_VIN is either:
		- Updated with new first available (first_VIN + 1)
		- Unchanged (if deleted record used)
	 - Header is always written in case del_rec_list updated
	 - Position to zeroth record using fseek()
	 - Update first_VIN with fwrite()
	*/
	fseek(tfd, 0, SEEK_SET);
	if (del_rec_no == DEL_END)
		hrec.first_VIN = hrec.first_VIN + 1;
	fwrite(&hrec, sizeof(HEADER), 1, tfd);

}
void rel_delete()
{
	/* Access any taxi record regardless of its location in the
	   file (direct/relative access).
	 * Limited by number of possible taxis (from header record)
	 * This is *not* accessing records using the taxi number, instead
	   it is using the record number.  How to access using a key other than
	   the record number will be discussed in class.
	*/
	DEL_TAXI taxi_rec;
	HEADER hrec;
	long rec_no;

	/* Read header, indicates last allowable record */
	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);

	do
	{
		printf("Enter taxi record number to delete (0 to end)\n");
		scanf_s("%d", &rec_no);
		getchar();
		/* Valid record? */
		if (rec_no >= hrec.first_VIN)
			printf("Invalid record: %u\n", rec_no);
		else
			if (rec_no > 0)
			{
				/* Record to be delete - position record */
				fseek(tfd, rec_no * sizeof(SFREC), SEEK_SET);
				/* Read record */
				fread(&taxi_rec, sizeof(DEL_TAXI), 1, tfd);
				/* Is record active? */
				switch (taxi_rec.status)
				{
				case ACTIVE:
					taxi_rec.status = DELETED;
					/* Update deleted link */
					taxi_rec.next_deleted = hrec.del_rec_list;
					hrec.del_rec_list = rec_no;
					/* Reposition file position back to rec_no */
					fseek(tfd, rec_no * sizeof(SFREC), SEEK_SET);
					/* Now write */
					fwrite(&taxi_rec, sizeof(DEL_TAXI), 1, tfd);
					printf("Record %u deleted\n", rec_no);
					break;
				case DELETED:
					printf("Record %u already deleted\n", rec_no);
					break;
				default:
					printf("Record %u - Invalid status %d\n", rec_no, taxi_rec.status);
				}
			}
	} while (rec_no > 0);

	/* Update header with new del_rec_list */
	fseek(tfd, 0, SEEK_SET);
	fwrite(&hrec, sizeof(HEADER), 1, tfd);
}
void rel_update()
{
	/* Update any taxi record regardless of its location in the
	   file (direct access).
	 * This is *not* accessing records using the taxi number, instead
	   it is using the record number.  How to access using a key other
	   than the record number will be discussed in class.
	 */
	SFREC taxi_rec;
	HEADER hrec;
	int choice;
	long rec_no;

	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);

	do
	{
		printf("Enter taxi record number (0 to end)\n");
		scanf_s("%d", &rec_no);

		if (rec_no >= hrec.first_VIN)
			printf("Invalid record %u\n", rec_no);
		else
			if (rec_no > 0)
			{
				/* Position to specified record number */
				fseek(tfd, rec_no * sizeof(SFREC), SEEK_SET);
				/*
				 * Once the file position is moved, the record, if it
				   exists, is read.  The user can then change the contents
				   of the record.  Once changed, the record is written
				   back to the file.
				 */
				fread(&taxi_rec, sizeof(SFREC), 1, tfd);
				if (taxi_rec.taxirec.status == ACTIVE)
				{
					printf("Record %4d found\n", rec_no);
					printf("%d %d %d %d\n",taxi_rec.taxirec.VIN,taxi_rec.taxirec.current.buildingl, taxi_rec.taxirec.current.buildingside, taxi_rec.taxirec.battery);
					/* Ask user for choice - repeat until zero */
					printf("Which field is to be changed? (0: Stop, 1: Current Building, 2: Building Side and 3: Battery Status)\n");
					scanf_s("%d", &choice);
					while (choice != 0)
					{
						getc(stdin); /* Clear NL from input buffer */
						switch (choice)
						{
						case 1: /* Current Building */
							printf("Enter new Current Building\n");
							scanf_s("%d", &taxi_rec.taxirec.current.buildingl);
							printf("New LN: >>%d<<\n", taxi_rec.taxirec.current.buildingl);
							break;
						case 2: /* Building Side */
							printf("Enter new Building Side\n");
							scanf_s("%d", &taxi_rec.taxirec.current.buildingside);
							printf("New LN: >>%d<<\n", taxi_rec.taxirec.current.buildingside);
							break;
						case 3: /* Battery Percentage */
							printf("Enter new Battery Percentage\n");
							scanf_s("%d", &taxi_rec.taxirec.battery);
							printf("New LN: >>%d<<\n", taxi_rec.taxirec.battery);
							break;
						default:
							printf("Unknown field: %d\n", choice);
						}
						/* Ask user for choice - repeat until zero */
						printf("Which field is to be changed? (0: Stop, 1: Current Building, 2: Building Side and 3: Battery Status)\n");
						scanf_s("%d", &choice);
					}
					/*
					 * Modified record must be written back to the file;
					   however, the last read moved the file pointer to
					   the start of the next record, therefore, it is
					   necessary to lseek() "back" to the record
					 */
					fseek(tfd, rec_no * sizeof(SFREC), SEEK_SET);
					/* Now the record can be written to the file */
					fwrite(&taxi_rec, sizeof(SFREC), 1, tfd);
				}
				else
					printf("Record %d is not active\n", rec_no);
			}
	} while (rec_no > 0);

}
void read_activevehicle(taxis ** taxi_) {

	taxis curr;

	_set_fmode(_O_TEXT);

	char fname[NAMELEN];

	printf("Name required - Enter name of active taxi file\n");
	fgets(fname, NAMELEN, stdin);
	TRUNCATE(fname);


	activevehicle = fopen(fname, "r+");



	while (fscanf_s(activevehicle, "%d", &curr.VIN) != EOF)
	{
		add_to_taxi_list(taxi_, curr);
	}

	fclose(activevehicle);
	getchar();

}
void read_ordersfile(taxis ** taxi_) {
	taxis curr;

	_set_fmode(_O_TEXT);

	char fname[NAMELEN];

	printf("Name required - Enter name of Orders file\n");
	fgets(fname, NAMELEN, stdin);
	TRUNCATE(fname);

	orders = fopen(fname, "r+");

	int time;

	while (fscanf_s(orders, "%d	%d	%d	%d	%d", &curr.ordertime, &curr.source.buildingl, &curr.source.buildingside, &curr.destination.buildingl, &curr.destination.buildingside) != EOF)
	{
		//printf("%d	%d	%d	%d	%d\n", curr.ordertime, curr.source.buildingl, curr.source.buildingside, curr.destination.buildingl, curr.destination.buildingside);
		set_location(&curr);
		add_to_taxi_list(taxi_, curr);
	}
	fclose(orders);
	getchar();
}
void taxi_initiator() {
	SFREC taxi_rec;
	HEADER hrec;
	long rec_no, adjustedcount;
	int i = 0;
	taxis* curr;
	int x_current_offset, y_current_offset;

	/* Read header, indicates last allowable record */
	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);
	adjustedcount = hrec.first_VIN + VINADJUST;

	curr = start_active;

	_set_fmode(_O_BINARY);

	do
	{

		rec_no = curr->VIN - VINADJUST;


		/* Valid record? */
		if (rec_no >= hrec.first_VIN)
			printf("Invalid record: %u\n", curr->VIN);
		else
			if (rec_no > 0)
			{
				/* Position file to record */
				fseek(tfd, rec_no * sizeof(SFREC), SEEK_SET);
				/*
				 - Once the file pointer is moved, the record, if it exists,
				   is read.
				*/
				fread(&taxi_rec, sizeof(taxis), 1, tfd);
				/* Record exists - is it active? */
				if (taxi_rec.taxirec.status == ACTIVE)
				{

					/* Active record */
					taxi_rec.taxirec.VIN = curr->VIN;

					get_offset(taxi_rec.taxirec.current.buildingside, &x_current_offset, &y_current_offset);

					// set current for taxi
					taxi_rec.taxirec.current.gridl.X = buildingz[taxi_rec.taxirec.current.buildingl].B_address.X + x_current_offset;
					taxi_rec.taxirec.current.gridl.Y = buildingz[taxi_rec.taxirec.current.buildingl].B_address.Y + y_current_offset;

					taxi_rec.taxirec.source.gridl.X = taxi_rec.taxirec.current.gridl.X;
					taxi_rec.taxirec.source.gridl.Y = taxi_rec.taxirec.current.gridl.Y;
					taxi_rec.taxirec.destination.gridl.X = taxi_rec.taxirec.current.gridl.X;
					taxi_rec.taxirec.destination.gridl.Y = taxi_rec.taxirec.current.gridl.Y;


					taxi_rec.taxirec.source.intersection_location.X = taxi_rec.taxirec.current.gridl.X;
					taxi_rec.taxirec.source.intersection_location.Y = taxi_rec.taxirec.current.gridl.Y;
					taxi_rec.taxirec.destination.intersection_location.X = taxi_rec.taxirec.current.gridl.X;
					taxi_rec.taxirec.destination.intersection_location.Y = taxi_rec.taxirec.current.gridl.Y;


					printf("%3d Active ID: %4d, Battery: %d%%, Current location: Building Number: %d , Building side: %d Location: (%d,%d)\n", rec_no, taxi_rec.taxirec.VIN, taxi_rec.taxirec.battery, taxi_rec.taxirec.current.buildingl, taxi_rec.taxirec.current.buildingside, taxi_rec.taxirec.current.gridl.X, taxi_rec.taxirec.current.gridl.Y);


					add_to_taxi_list(&start_parked, taxi_rec.taxirec);

				}
			}
		curr = curr->next;
	} while (curr);
}
void getmapsize(int* street, int* avenue) {

	_set_fmode(_O_TEXT);

	map = fopen("Map.txt", "r+");

	fscanf_s(map, "%d	%d", street, avenue);
	fclose(map);
}