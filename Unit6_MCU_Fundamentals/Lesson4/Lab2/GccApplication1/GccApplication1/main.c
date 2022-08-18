/*
 * GccApplication1.c
 *
 * Created: 8/18/2022 3:54:44 PM
 * Author : Mahmoud Essam
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// #define SREG *(volatile unsigned int *)(0x20+0x3F)


int main(void)
{
	// Enable Global Interrupts
	sei();
	// INT0 At any logical Change
	MCUCR |= (1<<0);
	MCUCR &= ~(1<<1);
	// INT1 At Rising Edge
	MCUCR |= (1<<4);
	MCUCR |= (1<<3);
	// INT2 Ar Falling Edge
	MCUCR &= ~(1<<6);
	
	// Enable 3 Interrupts to work
	GICR |= (1<<5);
	GICR |= (1<<6);
	GICR |= (1<<7);

	DDRD |= (1<<5);
	DDRD |= (1<<6);
	DDRD |= (1<<7);
    while (1) 
    {
		PORTD &= ~ (1<<5);
		PORTD &= ~ (1<<6);
		PORTD &= ~ (1<<7);
    }
}

ISR(INT0_vect)
{
	PORTD |= (1<<5);
	_delay_ms(1000);
}

ISR(INT1_vect)
{
	PORTD |= (1<<6);
	_delay_ms(1000);
}

ISR(INT2_vect)
{
	PORTD |= (1<<7);
	_delay_ms(1000);
}


