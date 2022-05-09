/*
 * queue.h
 *
 *  Created on: Apr 26, 2022
 *      Author: Mahmoud
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include "stdio.h"
#include "stdint.h"
// User definitions

#define element_type uint32_t
#define Buffer_length 5

// data types definitions

typedef struct
{
	unsigned int length ;
	unsigned int count ;
	element_type* base ;
	element_type* head ;
	element_type* tail ;

}Queue;

typedef enum
{
	Queue_no_error,
	Queue_full,
	Queue_empty,
	Queue_null
}Queue_Status;

// APIs

Queue_Status Queue_Init(Queue* queue_ptr,element_type* Buffer);
Queue_Status Queue_Enqueue(Queue* queue_ptr,element_type item);
Queue_Status Queue_Dequeue(Queue* queue_ptr,element_type* item);
Queue_Status Queue_print(Queue* queue_ptr);

#endif /* QUEUE_H_ */
