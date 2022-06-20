/*
 * main.c
 *
 *	Student DataBase Project using Queue Data Structure
 *
 *  Created on: June 8, 2022
 *      Author: Mahmoud Essam
 */
#include "SDB_Queue.h"
DataBase_t base;
element_type arr[50];
int main()
{
	DataBase_init(&base, arr);
	while(1)
	{
		char temp_text[40];
		DPRINTF("\n=====================================");
		DPRINTF("\n\tChoose one of the following options");
		DPRINTF("\n1: Add student manually");
		DPRINTF("\n2: Add students from file");
		DPRINTF("\n3: Find student by ID");
		DPRINTF("\n4: Find student by the first name");
		DPRINTF("\n5: Find Students enrolled in one course");
		DPRINTF("\n6: Update Student");
		DPRINTF("\n7: Delete Student");
		DPRINTF("\n8: View All Students");
		DPRINTF("\n9: Print Students Count");
		DPRINTF("\n10: Exit");
		DPRINTF("\nEnter Your option: ");
		gets(temp_text);
		switch(atoi(temp_text))
		{
		case 1: Add_Student_Manually(&base);
		break;
		case 2: Add_Students_From_File(&base);
		break;
		case 3: Find_Student_By_ID(&base);
		break;
		case 4: Find_Student_By_FName(&base);
		break;
		case 5: Find_Students_in_Course(&base);
		break;
		case 6: Update_Student(&base);
		break;
		case 7: Delete_Student(&base, arr);
		break;
		case 8: view_All(&base);
		break;
		case 9: print_student_count(&base);
		break;
		case 10: exit(0);
		break;
		default:
			DPRINTF("\nWrong Option");
			break;
		}

	}
	return 1;
}
