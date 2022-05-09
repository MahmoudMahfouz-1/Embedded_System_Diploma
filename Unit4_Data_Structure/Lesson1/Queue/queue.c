/*
 * queue.c
 *
 *  Created on: Apr 26, 2022
 *      Author: Mahmoud
 */
#include "queue.h"
Queue_Status Queue_Init(Queue* queue_ptr,element_type* Buffer)
{

	queue_ptr->count=0;
	queue_ptr->length=Buffer_length;
	queue_ptr->head=Buffer;
	queue_ptr->tail=Buffer;
	queue_ptr->base=Buffer;

	return Queue_no_error;
}
Queue_Status Queue_Enqueue(Queue* queue_ptr,element_type item)
{
	if(!queue_ptr->head || !queue_ptr->base || !queue_ptr || !queue_ptr->tail)
	{
		printf("Queue_Enqueue Failed\n");
		return Queue_null;
	}
	if(queue_ptr->count == Buffer_length)
	{
		printf("Queue_Enqueue Failed\n");
		return Queue_full;
	}
	*(queue_ptr->head) = item;
	queue_ptr->count++;
	if(queue_ptr->head == (queue_ptr->base + (queue_ptr->length * sizeof(element_type))))
		queue_ptr->head = queue_ptr->base;
	else
		queue_ptr->head++;

	return Queue_no_error;

}
Queue_Status Queue_Dequeue(Queue* queue_ptr,element_type* item)
{
	if(!queue_ptr->head || !queue_ptr->base || !queue_ptr || !queue_ptr->tail)
	{
		printf("Queue_Dequeue Failed\n");
		return Queue_null;
	}
	if(queue_ptr->count == 0)
	{
		printf("Queue_Dequeue Failed\n");
		return Queue_empty;
	}
	*item = *queue_ptr->tail;
	queue_ptr->count--;
	if(queue_ptr->tail == (queue_ptr->base + (queue_ptr->length * sizeof(element_type))))
		queue_ptr->tail = queue_ptr->base;
	else
		queue_ptr->tail++;

	return Queue_no_error;
}
//Queue_Status Queue_print(Queue* queue_ptr)
//{
//	//check if FIFO buffer is exist
//	if(!queue_ptr->head || !queue_ptr->base || !queue_ptr || !queue_ptr->tail)
//		{
//			printf("Queue_Print Failed\n");
//			return Queue_null;
//		}
//
//	//check if FIFO buffer is empty
//	if ( queue_ptr->count == 0 )
//		return Queue_empty ;
//
//	return Queue_no_error ;
//
//}

