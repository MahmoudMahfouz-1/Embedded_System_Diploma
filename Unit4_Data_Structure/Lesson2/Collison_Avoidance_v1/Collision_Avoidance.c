/*
 * Collision_Avoidance.c
 *
 *  Created on: May 11, 2022
 *      Author: Mahmoud Essam
 */
#include "Collision_Avoidance.h"
unsigned int distance, speed, threshold = 50;

int generate_Random(int l, int r , int count)
{
	int i;
	for(i = 0 ; i < count ; i++)
	{
		int rand_num = (rand() % (r-l+1))+43;
		return rand_num;
	}
}

extern void (*state)();
STATE_define(CA_waiting)
{
	//state action
	state_id = CA_Waiting;
	speed = 0;
	distance = generate_Random(44,55,1);

	//Check Event
	(distance<= threshold) ? (state = STATE(CA_waiting)) : (state = STATE(CA_driving));
	printf("Waiting state : distance %d speed %d\n",distance, speed);
}

STATE_define(CA_driving)
{
	//state action
	state_id = CA_Driving;
	speed = 30;
	distance = generate_Random(44,55,1);

	//Check Event
	(distance<= threshold) ? (state = STATE(CA_waiting)) : (state = STATE(CA_driving));
	printf("Driving state : distance %d speed %d\n",distance, speed);
}

