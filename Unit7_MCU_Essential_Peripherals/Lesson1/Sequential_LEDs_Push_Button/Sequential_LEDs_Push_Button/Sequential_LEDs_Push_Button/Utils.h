/*
 * Utils.h
 *
 * Created: 8/29/2022 10:49:54 PM
 *  Author: Mahmoud Essam
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define setBit(address,bit) address |= (1<<bit)
#define clearBit(address,bit) address &= ~(1<<bit)
#define toggleBit(address,bit) address ^= (1<<bit)
#define readBit(address,bit) ((address & (1<<bit)) >> bit)



#endif /* UTILS_H_ */