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
	struct employee
	{
		char* empname;
		int empid;
	};
	struct employee emp1 ={"Mahmoud",21},emp2={"Ahmed",22},emp3={"Essam",23};
	struct employee(*arr[])={&emp1,&emp2,&emp3};
	struct employee(*(*pt)[3]) = &arr;
	printf("employee1 name : %s\n",(**(*pt+1)).empname);
	printf("employee1 id is: %d",(*(*pt+1))->empid);
	return 0;
}
