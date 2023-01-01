/*
 * Stm32_F103C6_RCC_Driver.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

#ifndef INC_STM32_F103C6_RCC_DRIVER_H_
#define INC_STM32_F103C6_RCC_DRIVER_H_


//-----------------------------
//--------- Includes ----------
//-----------------------------

#include "stm32f013x6.h"

#define HSE_Clock  (uint32_t)16000000
#define HSI_RC_Clk (uint32_t)8000000


/*
 * =============================================================================================
 * 								APIs Supported by "MCAL RCC DRIVER"
 * =============================================================================================
 */

uint32_t MCAL_RCC_GetSYS_CLKFreq(void) ;
uint32_t MCAL_RCC_GetHCLKFreq(void) ;
uint32_t MCAL_RCC_GetPCLK1Freq(void) ;
uint32_t MCAL_RCC_GetPCLK2Freq(void) ;



#endif /* INC_STM32_F103C6_RCC_DRIVER_H_ */
