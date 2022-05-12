/*
 * US.c
 *
 *  Created on: May 12, 2022
 *      Author: Mahmoud Essam
 */
#include "CA.h"
 int CA_speed = 0;
 int CA_distance = 0;
 int CA_threshold = 50;
 void (*CA_state)();
 void US_Set_distance(int d)
 {
	 CA_distance = d;
	 (CA_distance <= CA_threshold ? (CA_state = STATE(CA_waiting)) : (CA_state = STATE(CA_driving)) );
	 printf("US ---------distance = %d --------------> CA \n",CA_distance);
 }
 STATE_define(CA_waiting)
 {

 	CA_state_id = CA_waiting;
 	printf("Waiting state : distance %d speed %d\n",CA_distance, CA_speed);
 	CA_speed = 0;
 	DC_motor(CA_speed);



 }

 STATE_define(CA_driving)
 {
 	//state action
 	CA_state_id = CA_driving;
 	printf("Driving state : distance %d speed %d\n",CA_distance, CA_speed);
 	CA_speed = 30;
 	DC_motor(CA_speed); 	//Check Event

 }


