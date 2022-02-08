/*
 * main.c
 *
 *  Created on: Dec 6, 2021
 *      Author: Mahmoud
 */

#include "stdio.h"
int isPrime(int num);
int main()
{
	int i,n1,n2,flag;
	printf("Enter two intervals seperated by space : ");
	fflush(stdin);	fflush(stdout);
	scanf("%d %d",&n1,&n2);
	printf("The prime numbers between %d and %d are : \n",n1,n2);
	fflush(stdin);	fflush(stdout);
	for(i=n1+1;i<n2;++i)
	{
		flag = isPrime(i);
		if(flag == 0)
			printf("%d\n",i);
	}
	return 0;
}
int isPrime(int num)
{
	int j ,flag;
	flag=0;
	for(j = 2;j<num/2;++j)
	{
		if(num%j ==0)
		{
			flag=1;
			break;
		}
	}
	return flag;
}
