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
		int marks;
		int roll;
	};
	struct student s[10];
	printf("Enter information of Students\n");
	int i;
	for( i =0;i<2;i++)
	{
		s[i].roll=i+1;
		printf("For roll number %d\n",s[i].roll);
		printf("Enter name: ");
		fflush(stdin);	fflush(stdout);
		scanf("%s",&s[i].name);
		printf("Enter marks: ");
		fflush(stdin);	fflush(stdout);
		scanf("%d",&s[i].marks);
	}
	printf("Displaying Students Information\n");
	for(i = 0;i<2;i++)
	{
		printf("\nInformation for roll %d\n",i+1);
		printf("Name :%s \n",s[i].name);
		printf("Marks :%d ",s[i].marks);
	}


	return 0;
}




