/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */




#include "stdio.h"
int main()
{
	struct student
	{
		char name[100];
		int roll;
		int marks;

	};
	struct student s;
	printf("Enter Student Name: ");
	fflush(stdin);	fflush(stdout);
	scanf("%s",&s.name);
	printf("Enter Student Roll Number: ");
	fflush(stdin);	fflush(stdout);
	scanf("%d",&s.roll);
	printf("Enter Student Marks: ");
	fflush(stdin);	fflush(stdout);
	scanf("%d",&s.marks);

	printf("Name: %s\n",s.name);
	fflush(stdin);	fflush(stdout);
	printf("Roll: %d\n",s.roll);
	fflush(stdin);	fflush(stdout);
	printf("Marks: %d",s.marks);


	return 0;
}
