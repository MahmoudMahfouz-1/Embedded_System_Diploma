/*
 * SDB_Queue.c
 *
 *  Created on: Jun 8, 2022
 *      Author: Mahmoud Essam
 */
#include "SDB_Queue.h"
DataBase_status DataBase_init(DataBase_t* Database,element_type* arr)
{
	DataBase_t *pDatabase = Database;
	pDatabase->base=arr;
	pDatabase->tail=arr;
	pDatabase->head=arr;
	pDatabase->count=0;
	pDatabase->length=50;
	DPRINTF("\tInitialization Done\n");
	return DataBase_no_error;
}
DataBase_status Add_Student_Manually(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->head;
	SData_t *id_check = pDatabase->base;
	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is full
	if(pDatabase->count == pDatabase->length)
	{
		DPRINTF("DataBase Full\n");
		return DataBase_full;
	}

	//Variables used
	int tmp_id,i;
	DPRINTF("Enter Student ID: ");
	scanf("%d",&tmp_id);
	// check if the id is in the database if yes --> return null
	for(i = 0; i<pDatabase->count; i++)
	{
		if(tmp_id == id_check->ID)
		{
			DPRINTF("The ID is already in the database choose another one\n");
			return DataBase_null;
		}
		else
			id_check++;

	}
	SData->ID = tmp_id;
	DPRINTF("Enter student GPA: ");
	scanf("%f",&SData->GPA);
	DPRINTF("Enter Student First Name: ");
	gets(SData->FName);
	DPRINTF("Enter Student Last Name: ");
	gets(SData->LName);
	for(i = 0 ; i< 5; i++)
	{
		DPRINTF("Enter course id %d : ",i+1);
		scanf("%d",&SData->course_id[i]);
	}

	pDatabase->count++;

	// Make the DataBase Circular
	if(pDatabase->head == (pDatabase->base + (pDatabase->length * sizeof(element_type))))
		pDatabase->head = pDatabase->base;
	else
		pDatabase->head++;

	DPRINTF("\n\tStudent Added Successfully\n");
	return DataBase_no_error;
}

DataBase_status Add_Students_From_File(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->head;
	SData_t *id_check = pDatabase->base;

	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is full
	if(pDatabase->count == pDatabase->length)
	{
		DPRINTF("DataBase Full\n");
		return DataBase_full;
	}

	//variables
	int i , tmp_id = 0, j;
	FILE* pInfo = fopen("info.txt", "r");
	if(pInfo == NULL)
	{
		DPRINTF("\n Failed To open the file\n");
		return DataBase_null;
	}
	rewind(pInfo);
	while(!feof(pInfo))
	{
		fscanf(pInfo, "%d" , &tmp_id);

		//check if the id in the database if yes --> return null
		for(i = 0; i<pDatabase->count; i++)
		{
			if(tmp_id == id_check->ID)
			{
				DPRINTF("The ID is already in the database choose another one\n");
				return DataBase_null;
			}
			else
				id_check++;
		}

		// add the id in the database
		SData->ID = tmp_id;

		// scan the remaining data
		fscanf(pInfo, "%f" ,&SData->GPA);
		fscanf(pInfo, "%s" ,SData->FName);
		fscanf(pInfo, "%s" ,SData->LName);
		for(j = 0 ; j < 5; j++)
		{
			fscanf(pInfo, "%d" ,&SData->course_id[j]);
		}

		// Increment the SData pointer to point to the next slot after scanning the data
		SData++;
		// Increment the count var by 1
		pDatabase->count++;

		// Make the DataBase Circular
		if(pDatabase->head == (pDatabase->base + (pDatabase->length * sizeof(element_type))))
			pDatabase->head = pDatabase->base;
		else
			pDatabase->head++;

		DPRINTF("\n\tStudent Added Successfully\n");


	}
	DPRINTF("-----------------File scanned Successfully-----------------\n");
	fclose(pInfo);
	return DataBase_no_error;
}


DataBase_status Find_Student_By_ID(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->base;
	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is empty
	if(pDatabase->count == 0)
	{
		DPRINTF("DataBase Empty\n");
		return DataBase_empty;
	}
	//Variables used
	int tmp_id,i,j;
	DPRINTF("Enter Student ID: ");
	scanf("%d",&tmp_id);
	for(i=0 ;i < pDatabase->count; i++)
	{
		//check if the id in the database if yes --> print the student data
		if(tmp_id == SData->ID)
		{
			DPRINTF("Student Data are below\n");
			DPRINTF("Student GPA : %.2f\n",SData->GPA);
			DPRINTF("Student First Name is %s\n",SData->FName);
			DPRINTF("Student Last Name is %s\n",SData->LName);
			for(j = 0; j < 5; j++)
			{
				DPRINTF("Course id %d is %d\n",j+1,SData->course_id[j]);
			}
			return DataBase_no_error;
		}
		// if no --> make the pointer points to the next slot in the array
		else
			SData++;
	}
	DPRINTF("The id isn't in the DataBase\n");
	return DataBase_null;
}


DataBase_status Find_Student_By_FName(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->base;
	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is empty
	if(pDatabase->count == 0)
	{
		DPRINTF("DataBase Empty\n");
		return DataBase_empty;
	}
	// Variables
	int i, j;
	char fname[40];

	DPRINTF("Enter the Student's First name: ");
	gets(fname);

	for(i = 0 ; i< pDatabase->count; i++)
	{
		// check if the scanned name is in the database if yes --> print student data
		if(strcmp(fname,SData->FName) == 0)
		{
			DPRINTF("Student Data are below\n");
			DPRINTF("Student ID : %d\n",SData->ID);
			DPRINTF("Student GPA : %.2f\n",SData->GPA);
			DPRINTF("Student First Name is %s\n",SData->FName);
			DPRINTF("Student Last Name is %s\n",SData->LName);
			for(j = 0; j < 5; j++)
			{
				DPRINTF("Course id %d is %d\n",j+1,SData->course_id[j]);
			}
			return DataBase_no_error;
		}
		// if no --> make the pointer points to the next slot in the array
		else
			SData++;
	}
	DPRINTF("There is no such first name in the database\n");
	return DataBase_null;

}

DataBase_status Find_Students_in_Course(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->base;
	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is empty
	if(pDatabase->count == 0)
	{
		DPRINTF("DataBase Empty\n");
		return DataBase_empty;
	}

	// Variables
	int i,j , c_id, counter = 0;
	DPRINTF("Enter course id: ");
	scanf("%d",&c_id);

	for(i = 0; i < pDatabase->count; i++)
	{
		for(j = 0; j < 5; j++)
		{
			//check if the course id is in the database if yes --> print all the students data enrolled in it
			if(c_id == SData->course_id[j])
			{
				DPRINTF("Students enrolled in this course are\n");
				DPRINTF("Student ID : %d\n",SData->ID);
				DPRINTF("Student GPA : %.2f\n",SData->GPA);
				DPRINTF("Student First Name is %s\n",SData->FName);
				DPRINTF("Student Last Name is %s\n",SData->LName);
				DPRINTF("------------------------------------------\n");
				counter++;
			}

		}
		// if no --> increment the pointer to point to the next slot in the array
		SData++;
	}
	// if the counter > 0 means that there is at least one student enrolled
	if(counter > 0)
		return DataBase_no_error;
	// else there is no student enrolled
	else
	{
		DPRINTF("No student is enrolled in this course\n");
		return DataBase_null;
	}
}

DataBase_status view_All(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->base;

	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is empty
	if(pDatabase->count == 0)
	{
		DPRINTF("DataBase Empty\n");
		return DataBase_empty;
	}

	// Variables

	int i, j;
	for(i = 0 ; i < pDatabase->count; i++)
	{
		DPRINTF("Student number %d data are\n",i+1);
		DPRINTF("Student ID : %d\n",SData->ID);
		DPRINTF("Student GPA : %.2f\n",SData->GPA);
		DPRINTF("Student First Name is %s\n",SData->FName);
		DPRINTF("Student Last Name is %s\n",SData->LName);
		for(j = 0 ; j < 5; j++)
		{
			DPRINTF("course %d id is %d\n",j+1,SData->course_id[j])
		}
		DPRINTF("------------------------------------------\n");
		SData++;
	}
	return DataBase_no_error;
}


DataBase_status print_student_count(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	DPRINTF("The Student Count is %d\n",pDatabase->count);
	return DataBase_no_error;
}

DataBase_status Update_Student(DataBase_t* Database)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->base;

	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is empty
	if(pDatabase->count == 0)
	{
		DPRINTF("DataBase Empty\n");
		return DataBase_empty;
	}

	// Variables
	int choice, i, j, tmp_id;
	DPRINTF("Enter ID: ");
	scanf("%d",&tmp_id);


	for(i=0 ; i <pDatabase->count;i++)
	{
		if(tmp_id == SData->ID)
		{
			DPRINTF("\n\tChoose one of the following options");
			DPRINTF("\n1: Update Student's ID");
			DPRINTF("\n2: Update Student's GPA");
			DPRINTF("\n3: Update Student's First Name");
			DPRINTF("\n4: Update Student's Last Name");
			DPRINTF("\n5: Update Student's Course ID");
			DPRINTF("\nEnter your Choice: ");
			scanf("%d",&choice);

			switch(choice)
			{
			case 1:
				DPRINTF("Enter New ID: ");
				scanf("%d",&SData->ID);
				DPRINTF("\tStudent Data Update Successfully\n");
				return DataBase_no_error;
				break;
			case 2:
				DPRINTF("Enter New GPA: ");
				scanf("%f",&SData->GPA);
				DPRINTF("\tStudent Data Update Successfully\n");
				return DataBase_no_error;
				break;
			case 3:
				DPRINTF("Enter New First Name: ");
				gets(SData->FName);
				DPRINTF("\tStudent Data Update Successfully\n");
				return DataBase_no_error;
				break;
			case 4:
				DPRINTF("Enter New Last Name: ");
				gets(SData->LName);
				DPRINTF("\tStudent Data Update Successfully\n");
				return DataBase_no_error;
				break;
			case 5:
				for(j = 0; j < 5; j++)
				{
					DPRINTF("Enter course %d id: ",j+1);
					scanf("%d",&SData->course_id[j]);
				}
				DPRINTF("\tStudent Data Update Successfully\n");
				return DataBase_no_error;
				break;
			default:
				DPRINTF("\nWrong Option");
				return DataBase_null;
				break;
			}
		}
		else
			SData++;
	}
	DPRINTF("This ID isn't in the database\n");
	return DataBase_null;
}

DataBase_status Delete_Student(DataBase_t* Database,element_type* arr)
{
	DataBase_t *pDatabase = Database;
	SData_t *SData = pDatabase->base;

	//check if there is anything wrong with the database
	if(!pDatabase->head || !pDatabase->base || !pDatabase || !pDatabase->tail)
	{
		DPRINTF("DataBase Failed\n");
		return DataBase_null;
	}

	// check if the database is empty
	if(pDatabase->count == 0)
	{
		DPRINTF("DataBase Empty\n");
		return DataBase_empty;
	}

	// variables
	int i, tmp_id, j;

	DPRINTF("Enter Student ID to delete: ");
	scanf("%d",&tmp_id);

	for(i = 0; i < pDatabase->count;i++)
	{
		// check if the scanned id is in the database if yes --> delete the student
		if(tmp_id == SData->ID)
		{
			//code to delete the student data
			for(j = i ;j < pDatabase->count; j++)
			{
				arr[j] = arr[j+1];
			}
			pDatabase->count--;
			pDatabase->head--;
			DPRINTF("Student Data Deleted Successfully\n");
			return DataBase_no_error;
		}
		// if no --> increment the pointer to point to the next slot in the array
		else
			SData++;
	}
	DPRINTF("This id isn't in the database\n");
	return DataBase_null;
}
