/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"
void reverse();
int main()
{
	printf("Enter a sentence : ");
	fflush(stdin); fflush(stdout);
	reverse();
	return 0;
}
void reverse()
{
	char c;
	scanf("%c",&c);
	if(c != '\n')
	{
		reverse();
		printf("%c",c);
	}
}
