/*
 * Stm32_F103C6_GPIO_Driver.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVER_H_
#define INC_STM32_F103C6_GPIO_DRIVER_H_


//-----------------------------
//Includes
//-----------------------------

#include "stm32f013x6.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint16_t GPIO_PinNumber    ;  // Specifies the GPIO pin to be configured
								 // The parameter can be a value of @ref GPIO_PINS_define

	uint8_t GPIO_MODE         ;	 // Specifies the GPIO pin Mode to be configured
								 // The parameter can be a value of @ref GPIO_MODE_define

	uint8_t GPIO_Output_Speed ; // Specifies the GPIO Speed In case of OUTPUT Mode
								// The parameter can be a value of  @ref GPIO_SPEED_define
}GPIO_PinConfig;

//-----------------------------
//Macros Configuration References
//-----------------------------


//@ref GPIO_PINS_define
#define GPIO_PIN_0			((uint16_t)0x0001)  /* Pin 0 selected  	 */
#define GPIO_PIN_1			((uint16_t)0x0002)  /* Pin 1 selected 	 */
#define GPIO_PIN_2			((uint16_t)0x0004)  /* Pin 2 selected 	 */
#define GPIO_PIN_3			((uint16_t)0x0008)  /* Pin 3 selected  	 */
#define GPIO_PIN_4			((uint16_t)0x0010)  /* Pin 4 selected  	 */
#define GPIO_PIN_5			((uint16_t)0x0020)  /* Pin 5 selected 	 */
#define GPIO_PIN_6			((uint16_t)0x0040)  /* Pin 6 selected 	 */
#define GPIO_PIN_7			((uint16_t)0x0080)  /* Pin 7 selected 	 */
#define GPIO_PIN_8			((uint16_t)0x0100)  /* Pin 8 selected 	 */
#define GPIO_PIN_9			((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10			((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11			((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12			((uint16_t)0x1000)  /* Pin 12 selected 	 */
#define GPIO_PIN_13			((uint16_t)0x2000)  /* Pin 13 selected 	 */
#define GPIO_PIN_14			((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15			((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_ALL		((uint16_t)0xFFFF)  /* All Pins selected */


//@ref GPIO_MODE_define
#define GPIO_MODE_ANALOG				0x00000000u		//Analog Mode
#define GPIO_MODE_INPUT_FLO				0x00000001u		//Floating Input
#define GPIO_MODE_INPUT_PU				0x00000002u		//Input With Pull Up
#define GPIO_MODE_INPUT_PD				0x00000003u		//Input With Pull Down
#define GPIO_MODE_OUTPUT_PP				0x00000004u		//General purpose output push-pull
#define GPIO_MODE_OUTPUT_OD				0x00000005u		//General purpose output Open-drain
#define GPIO_MODE_OUTPUT_ALT_PP			0x00000006u		//Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_ALT_OD			0x00000007u		//Alternate function output Open-drain
#define GPIO_MODE_ALT_INPUT				0x00000008u		//Alternate function INPUT


//@ref GPIO_SPEED_define
//01: Output mode, max speed 10 MHz.
//10: Output mode, max speed 2 MHz.
//11: Output mode, max speed 50 MHz.
#define GPIO_OUTPUT_SPEED_10_MHz 		0x00000001u		//Output mode, max speed 10 MHz.
#define GPIO_OUTPUT_SPEED_2_MHz 		0x00000002u		//Output mode, max speed 2 MHz.
#define GPIO_OUTPUT_SPEED_50_MHz 		0x00000003u		//Output mode, max speed 50 MHz.


//@ref GPIO_Status_define
#define GPIO_STATUS_SET     1
#define GPIO_STATUS_RESET   0

//@ref GPIO_LOCK_define
#define GPIO_RETURN_LOCK_Enabled     1
#define GPIO_RETURN_LOCK_ERROR       0




/*
 * =============================================================================================
 * 								APIs Supported by "MCAL GPIO DRIVER"
 * =============================================================================================
 */

void MCAL_GPIO_Init(GPIO_Typedef *GPIOx, GPIO_PinConfig* PinConfig);
void MCAL_GPIO_DeInit(GPIO_Typedef *GPIOx);

/* READ APIs */
uint16_t MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOx, uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOx);

/* WRITE APIs */
void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOx, uint16_t PinNumber, uint16_t value);
void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOx, uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_Typedef *GPIOx, uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_Typedef *GPIOx, uint16_t PinNumber);








#endif /* INC_STM32_F103C6_GPIO_DRIVER_H_ */
