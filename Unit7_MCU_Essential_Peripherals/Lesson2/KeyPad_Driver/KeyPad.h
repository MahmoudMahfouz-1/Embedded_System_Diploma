/*
 * KeyPad.h
 *
 * Created: 9/25/2022 8:18:31 PM
 *  Author: Mahmoud Essam
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

//Includes
#include "avr/io.h"
#include "util/delay.h"
#define F_CPU 1000000UL

#define KEYPAD_PORT PORTD
#define DataDir_KEYPAD_CTRL DDRD
#define KEYPAD_PIN	PIND

#define R0 0
#define R1 1
#define R2 2
#define R3 3
#define C0 4
#define C1 5
#define C2 6
#define C3 7


// APIs
void KEYPAD_Init(void);
char KEYPAD_Get_Char(void);


#endif /* KEYPAD_H_ */