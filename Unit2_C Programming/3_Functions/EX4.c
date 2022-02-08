/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"
int powerFunc(int base, int power);
int main()
{
	int base , power;
	printf("Enter a Base number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&base);
	printf("Enter a Power number : ");
	fflush(stdin); fflush(stdout);
	scanf("%d",&power);
	printf("%d",powerFunc(base,power));
	return 0;
}

int powerFunc(int base, int power)
{
	if(power !=1)
	{
		return base * powerFunc(base,power-1);
	}
}
