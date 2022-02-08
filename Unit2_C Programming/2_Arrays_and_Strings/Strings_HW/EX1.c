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
	char ch;
	int i, counter;
	counter = 0;
	// scanning the string
	printf("Enter a string : ");
	fflush(stdin);   fflush(stdout);
	gets(str);
	//scanning the char
	printf("Enter a char : ");
	fflush(stdin);   fflush(stdout);
	scanf("%c",&ch);
	// Searching...
	for(i = 0;i<strlen(str);i++)
	{
		if(ch== str[i])
			counter++;
	}
	//printing the number
	printf("the number is : %d",counter);

}
