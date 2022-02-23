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
	int len;
	printf("Enter the number of elements (MAX 15): " );
	scanf("%d",&len);
	int arr[len];
	int i;
	printf("Enter array elements:\n");
	for(i=0; i<len; i++)
	{
		printf("Enter element %d :",i+1);
		scanf("%d",&arr[i]);
	}
	int *ptr = arr+len-1;
	for(i=5 ; i>0; i--)
	{
		printf("Element %d is:%d\n",i,*ptr--);
	}
	return 0;
}
