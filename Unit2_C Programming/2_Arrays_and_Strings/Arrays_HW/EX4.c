/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"

void main()
{
	int x,e,location;
	printf("Enter number of elements : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&x);
	++x;
	int arr[x];
	int i;
	// Scanning the array
	for(i = 0 ; i<x-1;i++)
	{
		printf("Enter element %d : ",i);
		fflush(stdout);  fflush(stdin);
		scanf("%d",&arr[i]);
	}
	printf("Enter the element to be inserted : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&e);
	printf("Enter the location : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&location);
	// Shifting the elements
	for(i = x ; i>=location;i--)
	{
		arr[i] = arr[i-1] ;
	}
	arr[location] = e;
	// Printing the array after insertion
	for(i = 0 ; i<x;i++)
	{
		printf(" element %d :%d \n",i,arr[i]);

	}

}
