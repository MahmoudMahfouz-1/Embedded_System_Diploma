/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"
int factorial(int num);
int main()
{
	int y,x ;
	printf("Enter a number to calculate factorial : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d",&x);
	fflush(stdin);	fflush(stdout);
	printf("The factorial is: %d",factorial(x));
	return 0;
}
int factorial(int num)
{
	if(num != 1)
		return num * factorial(num-1);
}
