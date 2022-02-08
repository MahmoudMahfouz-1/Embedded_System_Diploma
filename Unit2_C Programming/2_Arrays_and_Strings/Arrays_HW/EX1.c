/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"

void main()
{
	float a[2][2];
	float b[2][2];
	float c[2][2];
	int i,j;
	// Scaning array A
	printf("Enter elements of Array a\n");
	for(i = 0; i<2;i++)
	{
		for(j = 0; j <2;j++)
		{
			printf("Enter element %d %d : ",i,j);
			fflush(stdout);  fflush(stdin);
			scanf("%f",&a[i][j]);
		}
	}

	// Scaning array B
	printf("Enter elements of Array b\n");
	for(i = 0; i<2;i++)
	{
		for(j = 0; j <2;j++)
		{
			printf("Enter element %d %d : ",i,j);
			fflush(stdout);  fflush(stdin);
			scanf("%f",&b[i][j]);
		}
	}

	// Calculating the sum
	for(i = 0; i<2;i++)
	{
		for(j = 0; j <2;j++)
		{
			c[i][j] = a[i][j] + b[i][j];
		}
	}
	// Printing the sum
	printf("The Sum is \n");
	for(i = 0; i<2;i++)
	{
		for(j = 0; j <2;j++)
		{
			printf("%f	",c[i][j]);
		}
		printf("\n");
	}

}
