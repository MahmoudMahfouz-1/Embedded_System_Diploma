/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
// register address
#define GPIOA_BASE 0x40010800
#define GPIOA_CRH *(volatile uint32_t *)(GPIOA_BASE + 0x04)
#define GPIOA_ODR *(volatile uint32_t *)(GPIOA_BASE + 0x0C)
#define GPIOA_CRL *(volatile uint32_t *)(GPIOA_BASE + 0x00)

#define AFIO_BASE 0x40010000
#define AFIO_EXTICR1  *(volatile uint32_t *)(AFIO_BASE + 0x8)


#define EXTI_BASE 0x40010400
#define EXTI_IMR *(volatile uint32_t *)(EXTI_BASE + 0x0)
#define EXTI_RTSR *(volatile uint32_t *)(EXTI_BASE + 0x8)
#define EXTI_PR *(volatile uint32_t *)(EXTI_BASE + 0x14)


#define RCC_BASE 0x40021000
#define RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_CFGR *(volatile uint32_t *)(RCC_BASE + 0x04)


#define NVIC_EXTIE0 *(volatile uint32_t *)(0xE000E100)

void clock_init(void)
{
	//	Bit 2 IOPAEN: IO port A clock enable
	//	Set and cleared by software.
	//	0: IO port A clock disabled
	//	1: IO port A clock enabled
	RCC_APB2ENR |= (1<<2) ;
	RCC_APB2ENR |= (1<<0) ;
}

void GPIOA_init(void)
{
	//Init GPIOA
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x00200000;
	// pin A0 floating input
	GPIOA_CRL |= (1<<2);

}
int main(void)
{
	clock_init();
	GPIOA_init();
	// EXTI0 configuration to port A0
	AFIO_EXTICR1 = 0;

	// Enable Rising trigger
	EXTI_RTSR |= (1 << 0) ;

	// Enable EXTI Line0 Mask1
	EXTI_IMR |= (1<<0);

	// enable NVIC Irq6 <<>> EXTI0
	NVIC_EXTIE0 |= (1<<6);


	while(1) ;

}
void EXTI0_IRQHandler(void)
{
	GPIOA_ODR ^= (1<<13) ;

	// Clear Pending Request for Line 0
	EXTI_PR |= (1<<0);
}
