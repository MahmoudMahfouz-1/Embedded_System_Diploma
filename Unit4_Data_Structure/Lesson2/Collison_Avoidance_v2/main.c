/*
 * main.c
 *
 *  Created on: May 12, 2022
 *      Author: Mahmoud Essam
 */
#include "CA.h"
#include "DC.h"
#include "US.h"
extern void (*US_state)();
extern void (*DC_state)();
STATE_define(US_busy);
STATE_define(DC_idle);
STATE_define(DC_busy);
void setup()
{
	US_init();
	DC_init();
	CA_state = STATE(CA_waiting);
	US_state = STATE(US_busy);
	DC_state = STATE(DC_idle);
}

void main()
{
	 volatile int d ;
	 setup();
	 while (1)
	 {
		 US_state();
		 CA_state();
		 DC_state();
	 }
}

