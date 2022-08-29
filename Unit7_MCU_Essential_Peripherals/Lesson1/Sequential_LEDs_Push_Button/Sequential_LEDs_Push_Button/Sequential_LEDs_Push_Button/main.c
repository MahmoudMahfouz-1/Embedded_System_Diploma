/*
 * Sequential_LEDs_Push_Button.c
 *
 * Created: 8/29/2022 10:48:11 PM
 * Author : Mahmoud Essam
 */ 




#include "Utils.h"
#include <util/delay.h>
// IOA
#define PORTA (*(volatile unsigned char*)0x3B)
#define DDRA  (*(volatile unsigned char*)0x3A)
#define PINA  (*(volatile unsigned char*)0x39)

// IOB
#define PORTC (*(volatile unsigned char*)0x35)
#define DDRC  (*(volatile unsigned char*)0x34)
#define PINC  (*(volatile unsigned char*)0x33)

#define F_CPU 8000000UL
int i = 0;


int main(void)
{
	// Make PC.pin0 INPUT
	clearBit(DDRC,0);
	DDRA = 0xFF ;
	
	while (1)
	{
		
		if(readBit(PINC,0) == 1)
		{
			setBit(PORTA,i);
			i++;
			_delay_ms(1000);
		}
		
		
	}
}