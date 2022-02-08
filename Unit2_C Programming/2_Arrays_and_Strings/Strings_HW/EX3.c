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
	// scanning the string
	printf("Enter a string : ");
	fflush(stdin);   fflush(stdout);
	gets(str);
	int i,temp;
	int len = strlen(str);
	 for (i = 0; i < len/2; i++)
	    {
	        temp = str[i];
	        str[i] = str[len - i - 1];
	        str[len - i - 1] = temp;
	    }
		printf("%s",str);

}
