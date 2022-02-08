/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"

void main()
{
	// scanning the size of the array
	int x,num;
	printf("Enter number of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);

	int arr[x];
	int i;
	// Scanning the array
	for(i = 0 ; i<x;i++)
	{
		printf("Enter element %d : ",i);
		fflush(stdout);  fflush(stdin);
		scanf("%d",&arr[i]);
	}
	// scanning the number to search for in the array
	printf("Enter number to search for : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&num);
	// Searching for the element
	for(i = 0 ;i<x;i++)
	{
		if(arr[i] == num)
		{
			printf("Found it and the location is : %d \n",i);
			break;
		}


	}
	if (i == x)
		printf("DIDN'T FIND IT\n");

}

