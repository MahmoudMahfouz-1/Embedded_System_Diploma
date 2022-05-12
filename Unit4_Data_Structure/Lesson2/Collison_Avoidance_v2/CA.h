/*
 * US.h
 *
 *  Created on: May 12, 2022
 *      Author: Mahmoud Essam
 */

#ifndef US_H_
#define US_H_
#include "state.h"

enum
{
	CA_waiting,
	CA_driving
}CA_state_id;

STATE_define(CA_driving);
STATE_define(CA_waiting);
extern void (*CA_state)();
#endif /* US_H_ */
