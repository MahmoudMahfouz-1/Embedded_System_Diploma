/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */


#include "stdio.h"
#include "string.h"

int main()
{
	int len =0;
	printf("Enter string length: ");
	scanf("%d",&len);
	char str[len];
	printf("Enter a string: ");
	scanf("%s",&str);
	char *ptr =str+len;
	int i;
	for(i =0;i<len+1;i++)
	{
		printf("%c",*ptr--);
	}


	return 0;
}




