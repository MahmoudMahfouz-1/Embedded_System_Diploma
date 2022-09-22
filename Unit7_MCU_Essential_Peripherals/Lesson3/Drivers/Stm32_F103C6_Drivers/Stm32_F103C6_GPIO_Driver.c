/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

//-----------------------------
//Includes
//-----------------------------

#include "Stm32_F103C6_GPIO_Driver.h"

//==================================

uint8_t Get_CRLH_Position(uint32_t PinNumber)
{
	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;
	case GPIO_PIN_1:
		return 4;
		break;
	case GPIO_PIN_2:
		return 8;
		break;
	case GPIO_PIN_3:
		return 12;
		break;
	case GPIO_PIN_4:
		return 16;
		break;
	case GPIO_PIN_5:
		return 20;
		break;
	case GPIO_PIN_6:
		return 24;
		break;
	case GPIO_PIN_7:
		return 28;
		break;
	case GPIO_PIN_8:
		return 0;
		break;
	case GPIO_PIN_9:
		return 4;
		break;
	case GPIO_PIN_10:
		return 8;
		break;
	case GPIO_PIN_11:
		return 12;
		break;
	case GPIO_PIN_12:
		return 16;
		break;
	case GPIO_PIN_13:
		return 20;
		break;
	case GPIO_PIN_14:
		return 24;
		break;
	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}
/**================================================================
 * @Fn			-MCAL_GPIO_Init
 * @brief 		-Initializes GPIOx PINy according to the specified parameters in PinConfig
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @param [in] 	-PinConfig pointer to GPIO_PinConfig structure that contains the configuration information
 * 				 for the specified GPIO PIN
 * @retval		-None
 * Note			-Stm32f103c6 MCU has GPIO A,B,C,D,E Modules
 * 				 but LQFP48 has only GPIO A,B and Part of C,D Exported as external pins from the MCU
 */

void MCAL_GPIO_Init(GPIO_Typedef *GPIOx, GPIO_PinConfig* PinConfig)
{
	volatile uint32_t* ConfigRegister = NULL;
	uint8_t PIN_Config = 0;
	ConfigRegister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH ;

	// Clear CNF1[1:0] MODE1[1:0]
	(*ConfigRegister) &= ~(0xF << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	// If Pin is Output
	if(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_ALT_OD || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_ALT_PP || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP  )
	{
		PIN_Config = ((((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_Output_Speed)) &0x0F) ;

	}
	// If Pin is Input
	else //MODE = 00: Input mode (reset state)
	{
		if(PinConfig->GPIO_MODE == GPIO_MODE_ANALOG || PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO )
		{
			PIN_Config = ((((PinConfig->GPIO_MODE) << 2) | 0x0) &0x0F) ;
		}
		else if(PinConfig->GPIO_MODE == GPIO_MODE_ALT_INPUT)  // Consider it as input floating
		{
			PIN_Config = ((((GPIO_MODE_INPUT_FLO) << 2) | 0x0) &0x0F) ;

		}
		else // PU PD
		{
			//			Table 20. Port bit configuration table

			PIN_Config = ((((GPIO_MODE_INPUT_PU) << 2) | 0x0) &0x0F) ;
			if(PinConfig ->GPIO_MODE == GPIO_MODE_INPUT_PU) // Write 1 on the PxODR register
			{
				GPIOx->ODR |= PinConfig->GPIO_PinNumber ;
			}
			else // Write 0 on the PxODR register
			{
				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber) ;
			}
		}
	}
	// Write on CRL Or CRH
	(*ConfigRegister) |= ( (PIN_Config) << Get_CRLH_Position(PinConfig->GPIO_PinNumber)  );


}
//void MCAL_GPIO_Init (GPIO_Typedef *GPIOx, GPIO_PinConfig *PinConfig)
//{
//	//Port configuration register low (GPIOx_CRL)  0 >>> 7
//	//Port configuration register high (GPIOx_CRH) 8 >>> 15
//	uint32_t *config_reg = NULL; // To store which register for the input pin number
//
//	uint8_t PIN_CONFIG = 0 ; // To store the pin configuration
//
//	// Check if the input GPIO is bigger than bit number 8 to return the correct register for it
//	config_reg = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->CRL : &GPIOx->CRH; // Return the register (Low or High)
//
//	// Clear CNF8[1:0] MODE8[1:0]
//	(*config_reg) &= ~(0xF << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
//
//	// If pin is output
//	if(PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_ALT_OD || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_ALT_PP || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD || PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP  )
//	{
//		// Set CNF8[1:0] MODE8[1:0]
//		PIN_CONFIG = ((((PinConfig->GPIO_MODE - 4) << 2)|(PinConfig->GPIO_Output_Speed)) & 0x0F); // "-4" > for definition on .h file  and "& 0x0F" > for neglect all remaining bits
//
//	}
//	// If pin is input
//	else //00: Input mode (reset state)
//	{
//		if((PinConfig->GPIO_MODE == GPIO_MODE_ANALOG)||(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO))
//		{
//			// Set CNF8[1:0] MODE8[1:0] 00
//			PIN_CONFIG = ((((PinConfig->GPIO_MODE) << 2)|(0x0)) & 0x0F); // "-4" > for definition on .h file  and "& 0x0F" > for neglect all remaining bits
//		}
//		else if (PinConfig->GPIO_MODE == GPIO_MODE_ALT_INPUT) // Considered that GPIO_MODE_AF_INPUT = GPIO_MODE_INPUT_FLO in data sheet
//		{
//			PIN_CONFIG = ((((GPIO_MODE_INPUT_FLO) << 2)|(0x0)) & 0x0F); // "-4" > for definition on .h file  and "& 0x0F" > for neglect all remaining bits
//		}
//		else // Pull-up / Pull-Down Input
//		{
//			// GPIO_MODE_INPUT_PU == 0b10 as Table 20. Port bit configuration table
//			PIN_CONFIG = ((((GPIO_MODE_INPUT_PU) << 2)|(0x0)) & 0x0F); // "-4" > for definition on .h file  and "& 0x0F" > for neglect all remaining bits
//
//			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
//			{
//				// PxODR = 1 Input pull-up: Table 20. Port bit configuration table
//				GPIOx->ODR |= PinConfig->GPIO_PinNumber;
//			}
//			else
//			{
//				// PxODR = 0 Input pull-down: Table 20. Port bit configuration table
//				GPIOx->ODR &= ~(PinConfig->GPIO_PinNumber);
//			}
//		}
//	}
//	// Write on CRL or CRH
//	(*config_reg) |= (PIN_CONFIG << Get_CRLH_Position(PinConfig->GPIO_PinNumber));
//}
//


/**================================================================
 * @Fn			-MCAL_GPIO_DeInit
 * @brief 		-Resets All the GPIO Registers
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_DeInit(GPIO_Typedef *GPIOx)
{
	// Using The Reset Controller
	// APB2 peripheral reset register (RCC_APB2RSTR)
	// Set and cleared by software.
	if(GPIOx == GPIOA)
	{
		RCC->APB1RSTR |= (1<<2) ;
		RCC->APB2RSTR &= ~(1<<2);
	}
	else if(GPIOx == GPIOB)
	{
		RCC->APB1RSTR |= (1<<3) ;
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
	{
		RCC->APB1RSTR |= (1<<4) ;
		RCC->APB2RSTR &= ~(1<<4);
	}
	else if(GPIOx == GPIOD)
	{
		RCC->APB1RSTR |= (1<<5) ;
		RCC->APB2RSTR &= ~(1<<5);
	}
	else if(GPIOx == GPIOE)
	{
		RCC->APB1RSTR |= (1<<6) ;
		RCC->APB2RSTR &= ~(1<<6);
	}
}
/* READ APIs */
/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Reads The data from a specific Pin
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @param [in]  -PinNumber to read the data from
 * @retval		-The input pin Value
 * Note			-None
 */
uint16_t MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOx, uint16_t PinNumber)
{
	uint8_t bitStatus = 0;

	if(((GPIOx->IDR) & PinNumber) != GPIO_STATUS_RESET )
	{
		bitStatus = (uint8_t)GPIO_STATUS_SET;
	}
	else
	{
		bitStatus = (uint8_t)GPIO_STATUS_RESET;
	}
	return bitStatus;
}




/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Reads The data from a specific PORT
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @retval		-The input Port Value
 * Note			-None
 */
uint16_t MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOx)
{
	uint16_t portValue = 0;
	portValue = (uint16_t)GPIOx->IDR;
	return portValue;
}



/* WRITE APIs */

/**================================================================
 * @Fn			-MCAL_GPIO_WrirePin
 * @brief 		-Writes data on a specific Pin
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @param [in] 	-PinNumber to write the data on
 * @param [in] 	-value the value that will be written
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_WrirePin(GPIO_Typedef *GPIOx, uint8_t PinNumber, uint16_t value)
{
	if(value != GPIO_STATUS_RESET)
	{
		GPIOx->BSRR = (uint32_t)PinNumber;
	}
	else
	{
		GPIOx->BRR =  (uint32_t)PinNumber;
	}
}


/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-Writes data on a specific PORT
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @param [in] 	-value the value that will be written
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOx, uint16_t value)
{
	GPIOx->ODR = (uint32_t)value;
}


/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-toggles the data on a specific PORT
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @param [in] 	-PinNumber to toggle the data on
 * @retval		-None
 * Note			-None
 */
void MCAL_GPIO_TogglePin(GPIO_Typedef *GPIOx, uint16_t PinNumber)
{
	GPIOx->ODR ^= (PinNumber);
}



/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-toggles the data on a specific PORT
 * @param [in] 	-*GPIOx where x can be (A .. E)
 * @param [in] 	-PinNumber to toggle the data on
 * @retval		-None
 * Note			-None
 */
uint8_t MCAL_GPIO_LockPin(GPIO_Typedef *GPIOx, uint16_t PinNumber)
{
	//Set LCKK[16]
		volatile uint32_t temp = 1<<16;

		//Set the LCKy
		temp |= PinNumber;

		//Write 1
		GPIOx->LCKR = temp;

		//Write 0
		GPIOx->LCKR = PinNumber;

		//Write 1
		GPIOx->LCKR = temp;

		//Read 0
		temp = GPIOx->LCKR;

		//Read 1 (this read is optional but confirms that the lock is active)
		if((uint32_t)GPIOx->LCKR & 1<<16)
		{
			return GPIO_RETURN_LOCK_Enabled;
		}
		else
		{
			return GPIO_RETURN_LOCK_ERROR;
		}
}













