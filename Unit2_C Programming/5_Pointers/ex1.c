/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */


#include "stdio.h"

int main()
{
	int m = 29;
	printf("The address of m is:%x \n",(unsigned int)&m);
	printf("The value of m is:%d \n\n",m);
	int *ptr = &m;
	printf("Now ptr is assigned with the address of m\n");
	printf("Address of ptr is: %x\n",(unsigned int)ptr);
	printf("Content of ptr is: %d\n\n",*ptr);
	m = 34;
	printf("The value of m is assigned to 34\n\n");
	printf("Address of ptr is: %x\n",(unsigned int)ptr);
	printf("Content of ptr is: %d\n\n",*ptr);
	*ptr = 7;
	printf("The pointer variable ptr is assigned with the value 7\n");
	printf("The address of m is:%x \n",(unsigned int)&m);
	printf("The value of m is:%d \n",m);


	return 0;
}




