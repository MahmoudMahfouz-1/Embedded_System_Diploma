/*
 * Stm32_F103C6_GPIO_Driver.c
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

//-----------------------------
//Includes
//-----------------------------

#include "Stm32_F103C6_EXTI_Driver.h"

//==================================
/*
 * ===================================================================
 *						Generic Variables
 * ===================================================================
 *
 */

void(* GP_IRQ_CallBack[15])(void);
/*
 * ===================================================================
 *						Generic Macros
 * ===================================================================
 *
 */

#define AFIO_GPIO_Mapping(x)		( (x==GPIOA)?0:\
		(x==GPIOB)?1:\
				(x==GPIOC)?2:\
						(x==GPIOD)?3:0  )
//==================================




/*
 * ===================================================================
 *						Generic Functions
 * ===================================================================
 *
 */

void Enable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0: NVIC_IRQ6_EXTI0_Enable;			break;
	case 1: NVIC_IRQ7_EXTI1_Enable;			break;
	case 2: NVIC_IRQ8_EXTI2_Enable;			break;
	case 3: NVIC_IRQ9_EXTI3_Enable;			break;
	case 4: NVIC_IRQ10_EXTI4_Enable;		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:	NVIC_IRQ6_EXTI5_9_Enable; 		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:NVIC_IRQ6_EXTI10_15_Enable; 	break;
	}
}
void Disable_NVIC(uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0: NVIC_IRQ6_EXTI0_Disable;		break;
	case 1: NVIC_IRQ7_EXTI1_Disable;		break;
	case 2: NVIC_IRQ8_EXTI2_Disable;		break;
	case 3: NVIC_IRQ9_EXTI3_Disable;		break;
	case 4: NVIC_IRQ10_EXTI4_Disable;		break;

	case 5:
	case 6:
	case 7:
	case 8:
	case 9:	NVIC_IRQ6_EXTI5_9_Disable; 		break;

	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:NVIC_IRQ6_EXTI10_15_Disable; 	break;
	}
}
void Update_EXTI(EXTI_Config_t *EXTI_Cfg)
{
	//1- Configure GPIO to be floating Input
	GPIO_PinConfig PinCfg;
	PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	PinCfg.GPIO_PinNumber = EXTI_Cfg->EXTI_PIN.GPIO_PIN;
	MCAL_GPIO_Init(EXTI_Cfg->EXTI_PIN.GPIO_Port, &PinCfg);
	//======================================================

	//2- Update AFIO to Route between EXTI line with PORT A,B,C,D

	uint8_t AFIO_EXTICR_Index = EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber / 4;

	uint8_t AFIO_EXTICR_Position = (EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber % 4) * 4;

	// Clear the 4 bits
	AFIO->EXTICR[AFIO_EXTICR_Index] &= ~(0xF << AFIO_EXTICR_Position);

	AFIO->EXTICR[AFIO_EXTICR_Index] |= ((AFIO_GPIO_Mapping(EXTI_Cfg->EXTI_PIN.GPIO_Port) & 0xF) << AFIO_EXTICR_Position);
	//======================================================

	//3- Update Rising or Falling Registers

	EXTI->RTSR &= ~(1 << EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
	EXTI->FTSR &= ~(1 << EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);

	if(EXTI_Cfg->Trigger_Case == Trigger_Case_Rising)
	{
		EXTI->RTSR |= (1 <<  EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Cfg->Trigger_Case == Trigger_Case_Falling)
	{
		EXTI->FTSR |= (1 <<  EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Cfg->Trigger_Case == Trigger_Case_RisingAndFalling)
	{
		EXTI->RTSR |= (1 <<  EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
		EXTI->FTSR |= (1 <<  EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
	}
	//======================================================

	//4- Update IRQ Handling CallBack

	GP_IRQ_CallBack[EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber] = EXTI_Cfg->P_IRQ_CallBack ;
	//======================================================

	//5- Enable/ Disable IRQ & NVIC
	if (EXTI_Cfg->IRQ_EN == IRQ_ENABLE)
	{
		EXTI->IMR |= (1 << EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
		Enable_NVIC(EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
	}
	else if(EXTI_Cfg->IRQ_EN == IRQ_DISABLE)
	{
		EXTI->IMR &= ~(1 << EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
		Disable_NVIC(EXTI_Cfg->EXTI_PIN.EXTI_InputLineNumber);
	}
}
//==================================


/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_DeInit
 * @brief 		-Resets EXTI Registers and NVIC corresponding Mask Registers
 * @param [in] 	-None
 * @retval		-None
 * Note			-None
 */
void MCAL_EXTI_GPIO_DeInit()
{
	EXTI->IMR =   0x00000000 ;
	EXTI->EMR =   0x00000000 ;
	EXTI->RTSR =  0x00000000 ;
	EXTI->FTSR =  0x00000000 ;
	EXTI->SWIER = 0x00000000 ;
	//	This bit is cleared by writing a ‘1’ into the bit.
	EXTI->PR =    0xFFFFFFFF;

	// Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_Disable 		;
	NVIC_IRQ8_EXTI2_Disable 		;
	NVIC_IRQ9_EXTI3_Disable 		;
	NVIC_IRQ10_EXTI4_Disable 		;
	NVIC_IRQ6_EXTI5_9_Disable 		;
	NVIC_IRQ6_EXTI10_15_Disable		;
}


/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Init
 * @brief 		-This is used to initialize EXTI from specific GPIO PIN and specify Mask/Trigger and IRQ callback
 * @param [in] 	-EXTI_Cfg set by @ref EXTI_define, @ref Trigger_Case_define and @ref IRQ_EN_define
 * @retval		-None
 * Note			-Mandatory to enable RCC clock and AFIO clock for the corresponding GPIO Port
 */
void MCAL_EXTI_GPIO_Init(EXTI_Config_t *EXTI_Cfg)
{
	Update_EXTI(EXTI_Cfg);
}


/**================================================================
 * @Fn			-MCAL_EXTI_GPIO_Update
 * @brief 		-This is used to Update EXTI from specific GPIO PIN and specify Mask/Trigger and IRQ callback
 * @param [in] 	-EXTI_Cfg set by @ref EXTI_define, @ref Trigger_Case_define and @ref IRQ_EN_define
 * @retval		-None
 * Note			-Mandatory to enable RCC clock and AFIO clock for the corresponding GPIO Port
 */
void MCAL_EXTI_GPIO_Update(EXTI_Config_t *EXTI_Cfg)
{
	Update_EXTI(EXTI_Cfg);
}



////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////					ISR FUNCTIONS							////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

void EXTI0_IRQHandler(void)
{
	//	cleared by writing a ‘1’ into the bit
	EXTI->PR |= (1<< 0);
	// Call the CallBack Function
	GP_IRQ_CallBack[0]();
}
void EXTI1_IRQHandler(void)
{
	//	cleared by writing a ‘1’ into the bit
	EXTI->PR |= (1<< 1);
	// Call the CallBack Function
	GP_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void)
{
	//	cleared by writing a ‘1’ into the bit
	EXTI->PR |= (1<< 2);
	// Call the CallBack Function
	GP_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void)
{
	//	cleared by writing a ‘1’ into the bit
	EXTI->PR |= (1<< 3);
	// Call the CallBack Function
	GP_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void)
{
	//	cleared by writing a ‘1’ into the bit
	EXTI->PR |= (1<< 4);
	// Call the CallBack Function
	GP_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<< 5) { EXTI->PR |= (1<< 5)	;  GP_IRQ_CallBack[5]();}
	if(EXTI->PR & 1<< 6) { EXTI->PR |= (1<< 6)	;  GP_IRQ_CallBack[6]();}
	if(EXTI->PR & 1<< 7) { EXTI->PR |= (1<< 7)	;  GP_IRQ_CallBack[7]();}
	if(EXTI->PR & 1<< 8) { EXTI->PR |= (1<< 8)	;  GP_IRQ_CallBack[8]();}
	if(EXTI->PR & 1<< 9) { EXTI->PR |= (1<< 9)	;  GP_IRQ_CallBack[9]();}

}
void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<< 10) { EXTI->PR |= (1<< 10)	;  GP_IRQ_CallBack[10]();}
	if(EXTI->PR & 1<< 11) { EXTI->PR |= (1<< 11)	;  GP_IRQ_CallBack[11]();}
	if(EXTI->PR & 1<< 12) { EXTI->PR |= (1<< 12)	;  GP_IRQ_CallBack[12]();}
	if(EXTI->PR & 1<< 13) { EXTI->PR |= (1<< 13)	;  GP_IRQ_CallBack[13]();}
	if(EXTI->PR & 1<< 14) { EXTI->PR |= (1<< 14)	;  GP_IRQ_CallBack[14]();}
	if(EXTI->PR & 1<< 15) { EXTI->PR |= (1<< 15)	;  GP_IRQ_CallBack[15]();}
}







