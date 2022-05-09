/*
 * stack.h
 *
 *  Created on: Apr 25, 2022
 *      Author: Mahmoud
 */

#ifndef STACK_H_
#define STACK_H_

#include "stdint.h"
// user definitions
#define Buffer_legnth 5
#define element_type uint32_t
// type definitions
typedef struct
{
	unsigned int length ;
	unsigned int count ;
	element_type* base;
	element_type* head;

}Stack;

typedef enum
{
	stack_no_error,
	stack_full,
	stack_empty,
	stack_null
}Stack_Status;

Stack_Status stack_init(Stack* stack_ptr,element_type* buffer);
Stack_Status stack_push(Stack* stack_ptr, element_type item);
Stack_Status stack_pop(Stack* stack_ptr, element_type* item);



#endif /* STACK_H_ */
