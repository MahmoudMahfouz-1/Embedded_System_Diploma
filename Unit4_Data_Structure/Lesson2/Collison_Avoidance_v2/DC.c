/*
 * US.c
 *
 *  Created on: May 12, 2022
 *      Author: Mahmoud Essam
 */

#include "DC.h"

unsigned int speed;
 void (*DC_state)();

void DC_init()
{
	printf("DC_init\n");

}
DC_motor(int s)
{
	speed = s;
	DC_state = STATE(DC_idle);
	printf("CA -> -> -> -> DC DC_motor()\n");
}
STATE_define(DC_idle)
{
	DC_state_id = DC_idle;
	DC_state = STATE(DC_idle);
	printf("DC_idle state : speed = %d \n\n\n",speed);
}
STATE_define(DC_busy)
{
	DC_state_id =DC_busy;
	DC_state = STATE(DC_busy);
	printf("DC_busy state : speed = %d \n\n\n",speed);

}
