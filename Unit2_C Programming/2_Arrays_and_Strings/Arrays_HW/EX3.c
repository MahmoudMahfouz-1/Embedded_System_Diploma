/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"

void main()
{
	int x , y;
	printf("Enter number of Rows and Coloms : ");
	fflush(stdout);  fflush(stdin);
	scanf("%d %d",&x ,&y);
	int a[x][y];
	int b[y][x];
	int i,j;
	// Scaning array A
	printf("Enter elements of Array a\n");
	for(i = 0; i<x;i++)
	{
		for(j = 0; j <y;j++)
		{
			printf("Enter element %d %d : ",i,j);
			fflush(stdout);  fflush(stdin);
			scanf("%d",&a[i][j]);
		}
	//transposing the matrix
	}
	for(i = 0; i<y;i++)
	{
		for(j = 0; j <x;j++)
		{
			b[i][j] = a[j][i];
		}
	}
	// Entered matrix
	printf("The entered matrix  \n");
	for(i = 0; i<x;i++)
	{
		for(j = 0; j <y;j++)
		{
			printf("%d	",a[i][j]);
		}
		printf("\n");
	}
	// Transposed matrix
	printf("The array after transpose is  \n");
	for(i = 0; i<y;i++)
	{
		for(j = 0; j <x;j++)
		{
			printf("%d	",b[i][j]);
		}
		printf("\n");
	}



}
