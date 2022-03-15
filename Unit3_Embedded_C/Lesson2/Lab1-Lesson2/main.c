#include "uart.h"
#include "stdio.h"
unsigned char string_Buffer[100] = "learn-in-depth : Mahmoud";
unsigned char const string_Buffer2[100] = "learn-in-depth : Mahmoud";

void main(void)
{
	uart_Send_String(string_Buffer);
}