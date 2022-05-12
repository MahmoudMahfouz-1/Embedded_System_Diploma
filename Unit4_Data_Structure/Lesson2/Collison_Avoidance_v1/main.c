/*
 * main.c
 *
 *  Created on: May 11, 2022
 *      Author: Mahmoud Essam
 */

#include "Collision_Avoidance.h"

void setup()
{
	state = STATE(CA_waiting);
}
void main ()
{
	setup();
	while(1)
	{
		state();
	}
}






