#include "uart.h"
#define UART0DR *((volatile unsigned  int*)((unsigned int)0x101f1000))

void uart_Send_String(unsigned char *p_string)
{
	while(*p_string != '\0')
	{
		UART0DR = (unsigned int) *p_string;
		p_string++;
	}
}