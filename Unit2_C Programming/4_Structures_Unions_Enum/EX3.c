/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */


#include "stdio.h"
struct Scomplex
	{
		float real;
		float img;
	};
int main()
{

	struct Scomplex comp1;
	struct Scomplex comp2;
	printf("For the first complex number enter the Real and the img parts : ");
	fflush(stdin);	fflush(stdout);
	scanf("%f %f",&comp1.real, &comp1.img);
	printf("For the second complex number enter the Real and the img parts : ");
	fflush(stdin);	fflush(stdout);
	scanf("%f %f",&comp2.real, &comp2.img);
	addComplex(comp1,comp2);

	return 0;
}

void addComplex(struct Scomplex com1,struct Scomplex com2)
	{
		float res_real,res_img;
		res_real = com1.real + com2.real;
		res_img = com1.img + com2.img;

		printf("Sum is %f+%fi",res_real,res_img);

	}



