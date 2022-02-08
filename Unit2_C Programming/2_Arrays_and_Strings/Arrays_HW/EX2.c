/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"

void main()
{
	int x;
	printf("Enter the number of elements : ");
	fflush(stdout);  fflush(stdin);
	scanf("%d",&x);
	int arr[x];
	int i;
	printf("Enter The array Elements.\n ");
	for(i = 0 ; i<x;i++)
	{
		printf("Enter element %d : ",i);
		fflush(stdout);  fflush(stdin);
		scanf("%d",&arr[i]);
	}
	float average;
	float sum = 0;
	for(i = 0 ; i<x;i++)
		{
			sum += arr[i];
		}
	average = sum/x;
	printf("Average is : %.2f",average);

}
