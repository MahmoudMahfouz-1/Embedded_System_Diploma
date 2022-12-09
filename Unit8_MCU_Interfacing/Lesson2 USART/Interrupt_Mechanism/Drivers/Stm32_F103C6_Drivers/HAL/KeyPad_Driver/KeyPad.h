/*
 * KeyPad.h
 *
 *  Created on: Sep 27, 2022
 *      Author: Mahmoud Essam
 */

#ifndef HAL_KEYPAD_DRIVER_KEYPAD_H_
#define HAL_KEYPAD_DRIVER_KEYPAD_H_

#include "stm32f013x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"

#define KEYPAD_PORT GPIOB

#define R0 GPIO_PIN_0
#define R1 GPIO_PIN_1
#define R2 GPIO_PIN_3
#define R3 GPIO_PIN_4

#define C0 GPIO_PIN_5
#define C1 GPIO_PIN_6
#define C2 GPIO_PIN_7
#define C3 GPIO_PIN_8


// APIs
void HAL_KEYPAD_INIT(void);
char HAL_KEYPAD_GET_KEY(void);



#endif /* HAL_KEYPAD_DRIVER_KEYPAD_H_ */
