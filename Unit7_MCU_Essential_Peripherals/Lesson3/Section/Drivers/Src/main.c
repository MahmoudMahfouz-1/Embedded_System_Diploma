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

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif
#include "stm32f013x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"
#include "LCD.h"
#include "KeyPad.h"
//#include "KeyPad.h"
void my_wait(int x)
{
	volatile unsigned int i , j;
	for(int i = 0; i < x ; i++)
	{
		for(int j = 0; j < 255 ; j++) ;
	}
}
void clock_init(void)
{
	// GPIOA clock enable
	RCC_GPIOA_CLK_EN();

	// GPIOB clock enable
	RCC_GPIOB_CLK_EN();
}

int main(void)
{
	clock_init();
	// GPIO Init();

	HAL_LCD_INIT();
	HAL_KEYPAD_INIT();
	/* Super Loop */
	HAL_LCD_WRITE_STRING("Hello There");
	my_wait(500);
	char pressed_key;
	HAL_LCD_CLEAR_SCREEN();
	while(1)
	{
		pressed_key = HAL_KEYPAD_GET_KEY();
		switch (pressed_key)
		{
		case '!':
			HAL_LCD_CLEAR_SCREEN();
			break;
		case 'A':
			break;
		default:
			HAL_LCD_WRITE_CHAR(pressed_key);
			break;
		}
	}

}

