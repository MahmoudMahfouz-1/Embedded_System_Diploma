/*
 * US.c
 *
 *  Created on: May 12, 2022
 *      Author: Mahmoud Essam
 */

#include "US.h"
unsigned int distance;
 void (*US_state)();
US_distance_set(int d)
{
	distance = d;
	US_state = STATE(US_busy);
	printf("US -> -> -> -> CA US_distance_set()\n");
}

int generate_Random(int l, int r , int count)
{
	int i;
	for(i = 0 ; i < count ; i++)
	{
		int rand_num = (rand() % (r-l+1))+43;
		return rand_num;
	}
}

void US_init()
{
	printf("US_init\n");

}

STATE_define(US_busy)
{
	US_state_id = US_busy;
	distance = generate_Random(45 , 55 , 1);
	printf("US_busy state : distance = %d\n",distance);
	US_distance_set(distance);
	US_state = STATE(US_busy);
}
