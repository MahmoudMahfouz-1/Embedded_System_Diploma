/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */


#include "stdio.h"

int main()
{
	struct data
	{
		float inch;
		float feet;
	};
	struct data d1;
	struct data d2;
	struct data sum;
	printf("Enter data for the first distance \n\n");
	printf("Enter inch and feet: ");
	fflush(stdin);	fflush(stdout);
	scanf("%f %f",&d1.inch,&d1.feet);
	printf("Enter data for the second distance \n\n");
	printf("Enter inch and feet: ");
	fflush(stdin);	fflush(stdout);
	scanf("%f %f",&d2.inch,&d2.feet);
	sum.feet = d1.feet +d2.feet;
	sum.inch = d1.inch +d2.inch;
	if(sum.inch >12)
	{
		sum.inch=sum.inch-12;
		++sum.feet;
	}
	printf("Sum of distance is: %f feet & %f inches",sum.feet,sum.inch);
	return 0;
}




