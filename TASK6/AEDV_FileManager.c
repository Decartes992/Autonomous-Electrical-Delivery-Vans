/*The file manager file contains all functions related to accessing, reading, writing,
* initializing and updating files.  
* 
* 
* 
*/

/*MODULE: manageAedvFiles
*
* WHAT IT DOES:THE FILE MANAGER MODULE IS PURPOSED TO HANDLE IO RELATED TO FILES
* AND FOR ASSIGNING ORDERS TO THE AEDVS
*
* DATE: 10-29-2023
*
* NAME:
* IFTEKHAR RAFI
* WILLIAM THORNTON
*
*/



#include "AEDV_FileManager.h"

FILE* tfd;  /* AEDV file file-descriptor */
FILE* activevehicle; /*Active AEDV file*/
aedvs* start_orders;
aedvs* start_active;
FILE* orders;
FILE* map;
FILE* chargingandparking;
clock_t start, currenttime, end;
int activeVIN[ACTIVEVEHICLECOUNT];


void manageAedvFiles(int argc, char* argv[])
{
	int street, avenue, go_back_to_menu;
	int CONTINUE = 1, rwu = 0, ans, check_if_to_run_emulation_of_aedvs = 0;
	getmapsize(&street, &avenue);
	//dud_map(street, avenue);

	/* Open a file for initialization */

	do {
		printf("Press 0 to Read, 1 to Write, 2 to Update, 3 to Delete, or 4 to Initiatlize a new file: ");
		scanf_s("%d", &rwu);
		getchar();
		if (rwu == 4 || openAedvFile(argc, argv, TRUE) )
		{

			/*Read*/
			if (rwu == 0) {
				/* File exists -- process records */
				sequentialAccessAedv();
				/* Access any record */
				readAedv();

				/* Close opened file -- will occur by default when file closes */
				fclose(tfd);

				getchar();
			}
			/*Write*/
			else if (rwu == 1) {

				/* Add at least one aedv */
				do
				{
					addAedv(tfd);
					printf("Add another (1 - yes 0 - no)\n");
					scanf_s("%d", &ans);
					getchar();
				} while (ans == 1);

				/* Now print contents */
				sequentialAccessAedv();

				fclose(tfd);
				getchar();

			}
			/*Update*/
			else if (rwu == 2) {

				/* File exists -- process records */
				printf("Original contents\n");
				sequentialAccessAedv();

				updateAedv();

				printf("Updated contents\n");
				sequentialAccessAedv();

				/* Close opened file -- will occur by default when file closes */
				fclose(tfd);

				getchar();
			}
			else if (rwu == 3) {

				/* File exists -- process records */
				printf("Original contents\n");
				sequentialAccessAedv();

				deleteAedv();

				printf("Updated contents\n");
				sequentialAccessAedv();

				/* Close opened file -- will occur by default when file closes */
				fclose(tfd);
			}

			else if (rwu == 4)
			{
				printf("Initialize File? Enter 0 for yes: ");
				scanf_s("%d", &CONTINUE);
				getchar();

				if (CONTINUE == 0) {
					if (openAedvFile(argc, argv, FALSE))
					{
						initializeAedvFile();

						sequentialAccessAedv();

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
		manageAedvFiles(argc, argv);
	}


	getchar();
}
void initializeAedvFile()
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
int openAedvFile(int argc, char* argv[], int must_exist)
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
			printf("Name required - Enter name of aedv file\n");
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
	printf("Enter name of aedv file\n\n");
	fgets(fname, NAMELEN, stdin);
	TRUNCATE(fname);
	/* Try to open for reading and writing */
	return (tfd = fopen(fname, "w+")) != NULL;
}
void sequentialAccessAedv()
{
	/* Read the fixed-length aedv file sequentially */
	SFREC aedv_rec;
	HEADER header_rec;
	long aedvrec_no, adjustedcount;

	/* Position file pointer to start-of-file (header) */
	fseek(tfd, 0, SEEK_SET);

	/*
	 - Read header record - in zeroth record
	 - Indicates first available aedv id
	*/
	fread(&header_rec, sizeof(HEADER), 1, tfd);

	printf("Header:\nFirst available VIN: %u\n\n", header_rec.first_VIN + VINADJUST);

	if (header_rec.first_VIN == 1)
	{
		printf("File is empty, nothing to display\n");
		return;
	}

	/* Position file pointer to first possible aedv record */
	fseek(tfd, sizeof(SFREC), SEEK_SET);

	/*
	 * Read aedvs records:
	 * Limit is first available aedv id (from header)
	 * Read will be successful (non-zero return value) until end-of-file,
	   when a zero value is returned, causing the while to terminate
	*/

	aedvrec_no = 1; /* Default first record */
	adjustedcount = header_rec.first_VIN + VINADJUST;
	while (aedvrec_no < adjustedcount &&	fread(&aedv_rec, sizeof(SFREC), 1, tfd))
	{
		switch (aedv_rec.aedvrec.status)
		{
		case ACTIVE:
			/* Active record */
			printf("%3d Active ID: %4d, Battery: %d%%, Current location: Building Number: %d , Building side: %d Location: (%d,%d)\n", aedvrec_no, aedv_rec.aedvrec.VIN, aedv_rec.aedvrec.battery, aedv_rec.aedvrec.current.buildingl, aedv_rec.aedvrec.current.buildingside, aedv_rec.aedvrec.current.gridl.X, aedv_rec.aedvrec.current.gridl.Y);
			break;
		case DELETED:
			/* Deleted record */
			break;
		default:
			printf("%3d Invalid record: Status: %d\n", aedvrec_no, aedv_rec.aedvrec.status);
		}
		aedvrec_no++; /* Walk through sequentially */
	}

	/* Print list of deleted record */
	if (header_rec.del_rec_list == DEL_END)
		printf("No deleted records in file\n");
	else
	{
		/* At least one deleted record */
		aedvrec_no = header_rec.del_rec_list; /* First in list */
		do
		{
			printf("Record: %d deleted\n", aedvrec_no);
			/* Get next deleted record from current deleted record */
			fseek(tfd, aedvrec_no * sizeof(SFREC), SEEK_SET);
			fread(&aedv_rec, sizeof(SFREC), 1, tfd);
			aedvrec_no = aedv_rec.drec.next_deleted;
		} while (aedvrec_no != DEL_END);
	}
}
void readAedv()
{
	/* Access any aedv record regardless of its location in the
	   file (direct/relative access).
	 * Limited by number of possible AEDVs (from header record)
	 * This is *not* accessing records using the AEDV number, instead
	   it is using the record number.  How to access using a key other than
	   the record number will be discussed in class.
	*/
	SFREC aedv_rec;
	HEADER hrec;
	long rec_no, adjustedcount;

	/* Read header, indicates last allowable record */
	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);
	adjustedcount = hrec.first_VIN + VINADJUST;
	do
	{
		printf("Enter AEDV record number (0 to end)\n");
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
				fread(&aedv_rec, sizeof(aedvs), 1, tfd);
				/* Record exists - is it active? */
				if (aedv_rec.aedvrec.status == ACTIVE)
				{
					/* Active record */
					printf("%3d Active ID: %4d, Battery: %3d%%, Current location: Building Number: %d , Building side: %d Location: (%d,%d)\n", rec_no, aedv_rec.aedvrec.VIN, aedv_rec.aedvrec.battery, aedv_rec.aedvrec.current.buildingl, aedv_rec.aedvrec.current.buildingside, aedv_rec.aedvrec.current.gridl.X, aedv_rec.aedvrec.current.gridl.Y);

				}
				else
					printf("Not active record %3d\n", rec_no);
			}
	} while (rec_no > 0);

	printf("Reading finished\n");

}
void addAedv(FILE* tfd)
{
	/* Add a aedv to the aedv file */
	DEL_AEDV delaedv;
	SFREC newaedv;
	HEADER hrec;
	long del_rec_no;
	long VIN;
	int x_current_offset = 0, y_current_offset = 0;
	/* Access header record to get first available aedv id */
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
		/* Read deleted aedv record to get next deleted */
		fread(&delaedv, sizeof(DEL_AEDV), 1, tfd);
		/* Update del_rec_list in header */
		hrec.del_rec_list = delaedv.next_deleted;
		/*
		 - del_rec_no is the number of the to-be-reused record
		 - VIN is now del_rec_no
		 - Header (hrec) is updated with next del_rec_list (below)
		*/
		printf("Reusing deleted AEDV id: %u\n", del_rec_no);
		VIN = del_rec_no;
	}
	else
	{
		/*
		 - No deleted records - get new VIN
		 - Get AEDV information
		 - VIN is used as offset - keep in range
		*/
		printf("New AEDV id is: %u\n", hrec.first_VIN);
		VIN = hrec.first_VIN + VINADJUST;
	}

	/* Move to AEDV record (new or formerly deleted) */
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
	scanf_s("%d", &newaedv.aedvrec.current.buildingl);
	printf("Enter starting building side\n");
	scanf_s("%d", &newaedv.aedvrec.current.buildingside);
	printf("Enter Battery Percentage (Number Only): \n");
	scanf_s("%d", &newaedv.aedvrec.battery);



	/* Complete remaining fields */
	newaedv.aedvrec.VIN = VIN;
	newaedv.aedvrec.status = ACTIVE;

	GetOffset(newaedv.aedvrec.current.buildingside, &x_current_offset, &y_current_offset);
	newaedv.aedvrec.current.gridl.X = buildingz[newaedv.aedvrec.current.buildingl].B_address.X + x_current_offset;
	newaedv.aedvrec.current.gridl.Y = buildingz[newaedv.aedvrec.current.buildingl].B_address.Y + y_current_offset;

	/* Display complete record */
	printf("ID: >%d< BN: >%d< BS: >%d<\n", newaedv.aedvrec.VIN, newaedv.aedvrec.current.buildingl, newaedv.aedvrec.current.buildingside);
	/*
	 - Write aedv data to aedv file
	 - File pointer was positioned to aedv record
	   with fseek() above
	*/
	fwrite(&newaedv, sizeof(SFREC), 1, tfd);
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
void deleteAedv()
{
	/* Access any AEDV record regardless of its location in the
	   file (direct/relative access).
	 * Limited by number of possible AEDVs (from header record)
	 * This is *not* accessing records using the AEDV number, instead
	   it is using the record number.  How to access using a key other than
	   the record number will be discussed in class.
	*/
	DEL_AEDV aedv_rec;
	HEADER hrec;
	long rec_no;

	/* Read header, indicates last allowable record */
	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);

	do
	{
		printf("Enter AEDV record number to delete (0 to end)\n");
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
				fread(&aedv_rec, sizeof(DEL_AEDV), 1, tfd);
				/* Is record active? */
				switch (aedv_rec.status)
				{
				case ACTIVE:
					aedv_rec.status = DELETED;
					/* Update deleted link */
					aedv_rec.next_deleted = hrec.del_rec_list;
					hrec.del_rec_list = rec_no;
					/* Reposition file position back to rec_no */
					fseek(tfd, rec_no * sizeof(SFREC), SEEK_SET);
					/* Now write */
					fwrite(&aedv_rec, sizeof(DEL_AEDV), 1, tfd);
					printf("Record %u deleted\n", rec_no);
					break;
				case DELETED:
					printf("Record %u already deleted\n", rec_no);
					break;
				default:
					printf("Record %u - Invalid status %d\n", rec_no, aedv_rec.status);
				}
			}
	} while (rec_no > 0);

	/* Update header with new del_rec_list */
	fseek(tfd, 0, SEEK_SET);
	fwrite(&hrec, sizeof(HEADER), 1, tfd);
}
void updateAedv()
{
	/* Update any AEDV record regardless of its location in the
	   file (direct access).
	 * This is *not* accessing records using the AEDV number, instead
	   it is using the record number.  How to access using a key other
	   than the record number will be discussed in class.
	 */
	SFREC aedv_rec;
	HEADER hrec;
	int choice;
	long rec_no;

	fseek(tfd, 0, SEEK_SET);
	fread(&hrec, sizeof(HEADER), 1, tfd);

	do
	{
		printf("Enter AEDV record number (0 to end)\n");
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
				fread(&aedv_rec, sizeof(SFREC), 1, tfd);
				if (aedv_rec.aedvrec.status == ACTIVE)
				{
					printf("Record %4d found\n", rec_no);
					printf("%d %d %d %d\n", aedv_rec.aedvrec.VIN, aedv_rec.aedvrec.current.buildingl, aedv_rec.aedvrec.current.buildingside, aedv_rec.aedvrec.battery);
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
							scanf_s("%d", &aedv_rec.aedvrec.current.buildingl);
							printf("New LN: >>%d<<\n", aedv_rec.aedvrec.current.buildingl);
							break;
						case 2: /* Building Side */
							printf("Enter new Building Side\n");
							scanf_s("%d", &aedv_rec.aedvrec.current.buildingside);
							printf("New LN: >>%d<<\n", aedv_rec.aedvrec.current.buildingside);
							break;
						case 3: /* Battery Percentage */
							printf("Enter new Battery Percentage\n");
							scanf_s("%d", &aedv_rec.aedvrec.battery);
							printf("New LN: >>%d<<\n", aedv_rec.aedvrec.battery);
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
					fwrite(&aedv_rec, sizeof(SFREC), 1, tfd);
				}
				else
					printf("Record %d is not active\n", rec_no);
			}
	} while (rec_no > 0);

}
void initiateAedv() {
	SFREC aedv_rec;
	HEADER hrec;
	long rec_no, adjustedcount;
	int i = 0;
	aedvs* curr;
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
				fread(&aedv_rec, sizeof(aedvs), 1, tfd);
				/* Record exists - is it active? */
				if (aedv_rec.aedvrec.status == ACTIVE)
				{

					/* Active record */
					aedv_rec.aedvrec.VIN = curr->VIN;

					GetOffset(aedv_rec.aedvrec.current.buildingside, &x_current_offset, &y_current_offset);

					// set current for AEDV
					aedv_rec.aedvrec.current.gridl.X = buildingz[aedv_rec.aedvrec.current.buildingl].B_address.X + x_current_offset;
					aedv_rec.aedvrec.current.gridl.Y = buildingz[aedv_rec.aedvrec.current.buildingl].B_address.Y + y_current_offset;

					aedv_rec.aedvrec.source.gridl.X = aedv_rec.aedvrec.current.gridl.X;
					aedv_rec.aedvrec.source.gridl.Y = aedv_rec.aedvrec.current.gridl.Y;
					aedv_rec.aedvrec.destination.gridl.X = aedv_rec.aedvrec.current.gridl.X;
					aedv_rec.aedvrec.destination.gridl.Y = aedv_rec.aedvrec.current.gridl.Y;


					aedv_rec.aedvrec.source.intersection_location.X = aedv_rec.aedvrec.current.gridl.X;
					aedv_rec.aedvrec.source.intersection_location.Y = aedv_rec.aedvrec.current.gridl.Y;
					aedv_rec.aedvrec.destination.intersection_location.X = aedv_rec.aedvrec.current.gridl.X;
					aedv_rec.aedvrec.destination.intersection_location.Y = aedv_rec.aedvrec.current.gridl.Y;


					printf("%3d Active ID: %4d, Battery: %d%%, Current location: Building Number: %d , Building side: %d Location: (%d,%d)\n", rec_no, aedv_rec.aedvrec.VIN, aedv_rec.aedvrec.battery, aedv_rec.aedvrec.current.buildingl, aedv_rec.aedvrec.current.buildingside, aedv_rec.aedvrec.current.gridl.X, aedv_rec.aedvrec.current.gridl.Y);


					add_to_aedv_list(&start_parked, aedv_rec.aedvrec);

				}
			}
		curr = curr->next;
	} while (curr);
}

void read_activevehicle(aedvs ** aedv_) {

	aedvs curr;

	_set_fmode(_O_TEXT);

	char fname[NAMELEN];

	printf("Name required - Enter name of active AEDV file\n");
	fgets(fname, NAMELEN, stdin);
	TRUNCATE(fname);


	activevehicle = fopen(fname, "r+");



	while (fscanf_s(activevehicle, "%d", &curr.VIN) != EOF)
	{
		add_to_aedv_list(aedv_, curr);
	}

	fclose(activevehicle);
	getchar();

}
void read_ordersfile(aedvs ** aedv_) {
	aedvs curr;

	_set_fmode(_O_TEXT);

	char fname[NAMELEN];

	printf("Name required - Enter name of Orders file\n");
	fgets(fname, NAMELEN, stdin);
	TRUNCATE(fname);

	orders = fopen(fname, "r+");

	//int time;

	while (fscanf_s(orders, "%d	%d	%d	%d	%d", &curr.ordertime, &curr.source.buildingl, &curr.source.buildingside, &curr.destination.buildingl, &curr.destination.buildingside) != EOF)
	{
		//printf("%d	%d	%d	%d	%d\n", curr.ordertime, curr.source.buildingl, curr.source.buildingside, curr.destination.buildingl, curr.destination.buildingside);
		SetLocation(&curr);
		add_to_aedv_list(aedv_, curr);
	}
	fclose(orders);
	getchar();
}
void getmapsize(int* street, int* avenue) {

	_set_fmode(_O_TEXT);

	map = fopen("Map.txt", "r+");

	fscanf_s(map, "%d	%d", street, avenue);
	fclose(map);
}