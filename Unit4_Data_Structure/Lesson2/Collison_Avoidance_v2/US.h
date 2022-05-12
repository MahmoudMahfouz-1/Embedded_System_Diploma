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
	US_busy
}US_state_id;

void US_init();
STATE_define(US_busy);

extern void (*US_state)();


#endif /* US_H_ */
