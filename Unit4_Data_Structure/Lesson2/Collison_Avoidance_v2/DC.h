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
	DC_idle,
	DC_busy
}DC_state_id;

STATE_define(DC_idle);
STATE_define(DC_busy);
extern void (*DC_state)();
#endif /* US_H_ */
