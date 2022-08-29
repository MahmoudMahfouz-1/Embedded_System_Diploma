/*
 * Sequentioal_Leds.c
 *
 * Created: 8/29/2022 10:13:17 PM
 * Author : Mahmoud Essam
 */ 

#include "Utils.h"
#include <util/delay.h>

#define PORTA (*(volatile unsigned char*)0x3B)
#define DDRA  (*(volatile unsigned char*)0x3A)
#define PINA  (*(volatile unsigned char*)0x39)
#define F_CPU 8000000UL

int main(void)
{
	DDRA = 0xFF ;
    while (1) 
    {
		int i;
		for(i = 0; i < 8;i++)
		{
			setBit(PORTA,i);
			_delay_ms(500);
		}
		for(i = 7; i >= 0;i--)
		{
			clearBit(PORTA,i);
			_delay_ms(500);
		}
		
    }
}

