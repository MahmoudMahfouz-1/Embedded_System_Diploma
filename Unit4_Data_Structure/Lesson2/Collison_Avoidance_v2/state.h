/*
 * state.h
 *
 *  Created on: May 12, 2022
 *      Author: Mahmoud Essam
 */

#ifndef STATE_H_
#define STATE_H_

#include "stdio.h"
#include "stdlib.h"
#define STATE_define(_stateFunc_) void ST_##_stateFunc_()
#define STATE(_stateFunc_) ST_##_stateFunc_
 US_distance_set(int d);
 DC_motor(int s);
#endif /* STATE_H_ */
