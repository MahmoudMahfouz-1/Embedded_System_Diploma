/*
 * Collision_Avoidance.h
 *
 *  Created on: May 11, 2022
 *      Author: Mahmoud Essam
 */

#ifndef COLLISION_AVOIDANCE_H_
#define COLLISION_AVOIDANCE_H_

#include "stdio.h"
#include "stdlib.h"

enum
{
	CA_Driving,
	CA_Waiting
}state_id;

#define STATE_define(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_) ST_##_stateFunc_

//prototypes
STATE_define(CA_driving);
STATE_define(CA_waiting);

//global pointer to function

void (*state)();


#endif /* COLLISION_AVOIDANCE_H_ */
