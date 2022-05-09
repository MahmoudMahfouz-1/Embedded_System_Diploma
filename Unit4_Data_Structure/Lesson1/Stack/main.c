/*
 * main.c
 *
 *  Created on: Apr 25, 2022
 *      Author: Mahmoud
 */
#include "stdio.h"
#include "stack.h"

element_type static_buffer[Buffer_legnth];

int main()
{
	// create stack
	Stack UART_stack;

	// initialize stack
	stack_init(&UART_stack, static_buffer);
	// Push items in the Stack
	uint32_t i ,temp;
	for(i = 0 ; i < Buffer_legnth; i++)
	{
		if(stack_push(&UART_stack,i) == stack_full)
			break;
		printf("item %x is Pushed \n",i);
	}
	// Pop items from the Stack
	for(i = 0 ; i < Buffer_legnth; i++)
	{
		if(stack_pop(&UART_stack,&temp) == stack_empty)
			break;
		printf("item %x is Popped \n",temp);
	}

	return 0;
}
