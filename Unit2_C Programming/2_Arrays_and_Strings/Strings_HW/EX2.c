/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"
#include "string.h"

void main()
{
	char str[100];
	int i;
	int length = 0;
	// scanning the string
	printf("Enter a string : ");
	fflush(stdin);   fflush(stdout);
	gets(str);
	for(i = 0;i<100 && str[i] != '\0';i++)
	{
		length++;
	}
	printf("%d",length);


}
