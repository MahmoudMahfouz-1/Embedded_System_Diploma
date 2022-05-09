/*
 * main.c
 *
 *  Created on: May 8, 2022
 *      Author: Mahmoud Essam
 *      Project: Student_Data_Base using linked-list
 */
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#define DPRINTF(...)	{fflush(stdout);\
		fflush(stdin);\
		printf(__VA_ARGS__);\
		fflush(stdout);\
		fflush(stdin);}



struct Sdata
{
	int ID;
	float height;
	char name[40];
};

struct SStudent
{
	struct Sdata Student;
	struct SStudent* pNextStudent;
};
struct SStudent* gpNewStudent =NULL ;

void Add_Student()
{
	struct SStudent* pNewStudent =NULL ;
	struct SStudent* pLastStudent =NULL ;
	char temp_text[40];
	if(gpNewStudent) //a record exists
	{
		pLastStudent = gpNewStudent;
		while(pLastStudent->pNextStudent)
		{
			pLastStudent = pLastStudent->pNextStudent;
		}
		//create new record
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		pLastStudent->pNextStudent = pNewStudent;

	}
	else // No record exists
	{

		//create new record
		pNewStudent = (struct SStudent*)malloc(sizeof(struct SStudent));
		//Assign gpNew to it
		gpNewStudent = pNewStudent;
	}


	//fill the new record
	DPRINTF("\nEnter Student ID: ");
	gets(temp_text);
	pNewStudent->Student.ID = atoi(temp_text);

	DPRINTF("\nEnter Student name: ");
	gets(pNewStudent->Student.name);


	DPRINTF("\nEnter Student height: ");
	gets(temp_text);
	pNewStudent->Student.height = atof(temp_text);


	//Set the new record's nextptr to null
	pNewStudent->pNextStudent = NULL;

}


int Delete_Student()
{
	char selected_id[40];
	DPRINTF("\nEnter the id to delete: ");
	gets(selected_id);

	struct SStudent* pPreviousStudent =NULL ;
	struct SStudent* pSelectedStudent =gpNewStudent ;
	while(pSelectedStudent)
	{
		if(atoi(selected_id) == pSelectedStudent->Student.ID)
		{
			if(pPreviousStudent)
			{
				pPreviousStudent->pNextStudent= pSelectedStudent->pNextStudent;
			}
			else
			{
				gpNewStudent=pSelectedStudent->pNextStudent;
			}
			free(pSelectedStudent);
			DPRINTF("\nStudent Deleted");
			return 1;

		}
		pPreviousStudent=pSelectedStudent;
		pSelectedStudent = pSelectedStudent->pNextStudent;
	}
	DPRINTF("\nCan't Find student ID");
	return 0;
}

int view_Students()
{
	struct SStudent* pStudent =gpNewStudent ;
	int count= 0;
	if(gpNewStudent == NULL)
	{
		DPRINTF("\nList is Empty");
		return 0;
	}
	while(pStudent)
	{
		DPRINTF("\nRecord Number %d ",count+1);
		DPRINTF("\n\tStudent ID: %d ",pStudent->Student.ID);
		DPRINTF("\n\tStudent Name: %s ",pStudent->Student.name);
		DPRINTF("\n\tStudent height: %f ",pStudent->Student.height);

		pStudent = pStudent->pNextStudent;
		count++;

	}

}


void Delete_All()
{
	if(gpNewStudent == NULL)
		DPRINTF("\nList is Empty");

	struct SStudent* pStudent =gpNewStudent ;
	struct SStudent* pTempStudent =NULL ;
	while(pStudent)
	{
		pTempStudent = pStudent;
		pStudent = pStudent->pNextStudent;
		free(pTempStudent);
	}
	gpNewStudent= NULL;
}

int GetNth()
{
	if(gpNewStudent == NULL)
	{
		DPRINTF("\nList is Empty");
		return 0;
	}
	int count = 1;
	struct SStudent* pCurrentStudent =gpNewStudent ;
	int index;
	DPRINTF("\nEnter the index: ");
	scanf("%d",&index);

	while(pCurrentStudent)
	{
		if(count == index)
		{
			DPRINTF("\nIndex Number %d ",index);
			DPRINTF("\n\tStudent ID: %d ",pCurrentStudent->Student.ID);
			DPRINTF("\n\tStudent Name: %s ",pCurrentStudent->Student.name);
			DPRINTF("\n\tStudent height: %f ",pCurrentStudent->Student.height);
			return 1;
		}
		else
		{
			pCurrentStudent = pCurrentStudent->pNextStudent;
			count++;
		}
	}
	return 0;
}

int Length_Iterative()
{
	if(gpNewStudent == NULL)
	{
		DPRINTF("\nList is Empty");
		return 0;
	}
	int count = 0;
	struct SStudent* pCurrentStudent = gpNewStudent;
	while(pCurrentStudent)
	{
		pCurrentStudent = pCurrentStudent->pNextStudent;
		count++;
	}
	DPRINTF("\nLength is %d",count);
	return 1;
}

int Get_Nth_From_The_Last()
{
	if(gpNewStudent == NULL)
	{
		DPRINTF("\nList is Empty");
		return 0;
	}
	int index_needed = 0;
	DPRINTF("\nEnter the index from the last: ");
	scanf("%d",&index_needed);
	struct SStudent* pReferenceStudent = gpNewStudent;
	struct SStudent* pMainStudent = gpNewStudent;
	int i ;
	for(i= 0;i<index_needed;i++)
		pReferenceStudent = pReferenceStudent->pNextStudent;
	while(pReferenceStudent)
	{
		pReferenceStudent = pReferenceStudent->pNextStudent;
		pMainStudent = pMainStudent->pNextStudent;
	}
	DPRINTF("\nIndex Number %d from the last ",index_needed);
	DPRINTF("\n\tStudent ID: %d ",pMainStudent->Student.ID);
	DPRINTF("\n\tStudent Name: %s ",pMainStudent->Student.name);
	DPRINTF("\n\tStudent height: %f ",pMainStudent->Student.height);
	return 1;
}

void main()
{
	while(1)
	{
		char temp_text[40];
		DPRINTF("\n=====================================");
		DPRINTF("\n\tChoose one of the following options");
		DPRINTF("\n1: Add Student");
		DPRINTF("\n2: Delete Student");
		DPRINTF("\n3: View Student");
		DPRINTF("\n4: Delete All");
		DPRINTF("\n5: Get Specific index");
		DPRINTF("\n6: Find the length of the list");
		DPRINTF("\n7: Find Specific index from the last");
		DPRINTF("\nEnter Your option: ");
		gets(temp_text);
		switch(atoi(temp_text))
		{
		case 1: Add_Student();
		break;
		case 2: Delete_Student();
		break;
		case 3: view_Students();
		break;
		case 4: Delete_All();
		break;
		case 5: GetNth();
		break;
		case 6: Length_Iterative();
		break;
		case 7: Get_Nth_From_The_Last();
		break;
		defualt:
		DPRINTF("\nWrong Option");
		break;
		}

	}

}




