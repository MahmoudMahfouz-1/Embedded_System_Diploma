/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */


#include "stdio.h"

int main()
{
	char alpha[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	char *ptr = alpha;
	int i;
	for(i =0;i<26;i++)
	{
		printf("%c\t",*ptr++);
	}


	return 0;
}




