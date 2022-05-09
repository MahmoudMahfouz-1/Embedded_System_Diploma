/*
 * main.c
 *
 *  Created on: Apr 26, 2022
 *      Author: Mahmoud
 */

#include "queue.h"

element_type UART_Buff[Buffer_length];
int main()
{
	element_type i , temp;
	Queue UART_Queue;
	// Initialize Queue
	if(Queue_Init(&UART_Queue, &UART_Buff) == Queue_no_error)
		printf("\t\tQueue Initialization Done\n");
	// Enqueue items
	for(i = 0; i<Buffer_length; i++)
	{
		if(Queue_Enqueue(&UART_Queue,i) == Queue_no_error)
			printf("Item %d is Enqueued\n",i);
	}

	// print Queue
	//Queue_print(&UART_Queue);

	// Dequeue 2 items
	if(Queue_Dequeue(&UART_Queue,&temp) == Queue_no_error)
		printf("Item %d is Dequeued\n",temp);

	if(Queue_Dequeue(&UART_Queue,&temp) == Queue_no_error)
		printf("Item %d is Dequeued\n",temp);

	return 0;
}
