/*
 * Stm32_F103C6_UART_Driver.c
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

//-----------------------------
//--------- Includes ----------
//-----------------------------
#include "Stm32_F103C6_UART_Driver.h"

//==================================
/*
 * =============================================================================================
 * 								Generic Variables
 * =============================================================================================
 */
USART_Config* Global_UART_Config = NULL;



/*
 * =============================================================================================
 * 								Generic Functions
 * =============================================================================================
 */

/**================================================================
 * @Fn			-MCAL_UART_Init
 * @brief 		-Initializes USART (OnLY UART Supported)
 * @param [in] 	-*USARTx where x can be (1 .. 3)
 * @param [in] 	-USART_Config all UART configuration
 * @retval		-None
 * Note			-Support for now Async. and 8Mhz clock
 */
void MCAL_UART_Init(USART_Typedef* USARTx, USART_Config* UART_Config )
{
	uint32_t pclk, BRR;


	Global_UART_Config = UART_Config;

	//Enable clock for the USART
	if(USARTx == USART1)
		RCC_USART1_CLK_EN();
	else if(USARTx == USART2)
		RCC_USART2_CLK_EN();
	else if(USARTx == USART3)
		RCC_USART3_CLK_EN();

	// Enable USART Module
	//	Bit 13 UE: USART enable
	USARTx->CR1 |= (1 << 13);

	// UART Mode
	USARTx->CR1 |= UART_Config->USART_Mode;

	// Payload Length
	//	Bit 12 M: Word length
	USARTx->CR1 |= UART_Config->Payload_Length;

	//Configuration of Parity Mode
	USARTx->CR1 |= UART_Config->Parity;

	//Configuration of Number of stop Bits
	USARTx->CR2 |= UART_Config->StopBits;

	//Configuration of Hardware Flow Control
	USARTx->CR3 |= UART_Config->HwFlowCtl;

	//Configuration of Baud Rate
	if(USARTx == USART1)
		pclk = MCAL_RCC_GetPCLK2Freq();
	else
		pclk = MCAL_RCC_GetPCLK1Freq();
	BRR = UART_BRR_Register(pclk, UART_Config->BaudRate);
	USARTx->BRR = BRR;

	// Enable/Disable Interrupt
	if(UART_Config->IRQ_Enable != IRQ_Enable_None)
	{
		USARTx->CR1 |= (UART_Config->IRQ_Enable);

		//		Enable NVIC for UARTx
		if(USARTx == USART1)
			NVIC_IRQ37_USART1_Enable;

		else if(USARTx == USART2)
			NVIC_IRQ38_USART2_Enable;

		else if(USARTx == USART3)
			NVIC_IRQ39_USART3_Enable;
	}

}

/**================================================================
 * @Fn			-MCAL_UART_DeInit
 * @brief 		-Resets USARTx (OnLY UART Supported)
 * @param [in] 	-*USARTx where x can be (1 .. 3)
 * @retval		-None
 * Note			-Support for now Async. and 8Mhz clock
 */
void MCAL_UART_DeInit(USART_Typedef* USARTx)
{
	if(USARTx == USART1)
	{
		RCC_USART1_CLK_Reset();
		NVIC_IRQ37_USART1_Disable;
	}
	else if(USARTx == USART2)
	{
		RCC_USART2_CLK_Reset();
		NVIC_IRQ38_USART2_Disable;
	}
	else if(USARTx == USART3)
	{
		RCC_USART3_CLK_Reset();
		NVIC_IRQ39_USART3_Disable;
	}
}


/* ================================================================
 * @Fn				- MCAL_UART_ReceiveData
 * @brief			- Recives Data From UART
 * @param [in] 		- USARTx where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer buffer
 * @param [in] 		- Polling Enable or disable
 * @retval 			- none
 * Note				- Initialize UART first
 * 					- when transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register)
 * 					- the value written in the MSB ( bit 7 or bit 8 depending on the data length ) has no effect
 * 					- because it is replaced by the parity
 * 					- when receiving with the parity enabled the value read in the MSB bit is the received parity bit
 */
void MCAL_UART_ReceiveData(USART_Typedef* USARTx, uint16_t* pTxBuffer, enum polling_mechanism PollingEn)
{
	if (PollingEn == enable)
	{
		while (!(USARTx->SR & 1<<5));
	}
	if(Global_UART_Config->Payload_Length == Payload_Length_9B)
	{
		/* 9 Bit Mode */
		if(Global_UART_Config->Parity == Parity_None)
		{
			/* No Parity so all Bits are considered Data */
			*((uint16_t*)pTxBuffer) = USARTx->DR ;
		}
		else
		{
			/* Parity is used so 8 Bits are data and one Bit for parity */
			*((uint16_t*)pTxBuffer) = ( USARTx->DR & (uint8_t)0xFF ) ;
		}
	}
	else
	{
		/* 8 Bit Mode */
		if(Global_UART_Config->Parity == Parity_None)
		{
			/* No Parity so all Bits are considered Data */
			*((uint16_t*)pTxBuffer) = (USARTx->DR & (uint8_t)0xFF) ;
		}
		else
		{
			/* Parity is used so 8 Bits are data and one Bit for parity */
			*((uint16_t*)pTxBuffer) = (USARTx->DR & (uint8_t)0x7F) ;
		}
	}
}

/* ================================================================
 * @Fn				- MCAL_UART_SendData
 * @brief			- Send buffer on UART
 * @param [in] 		- USARTx where x can be (1..3 depending on device used)
 * @param [in] 		- pTxBuffer buffer
 * @param [in] 		- Polling Enable or disable
 * @retval 			- none
 * Note				- Initialize UART first
 * 					- when transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register)
 * 					- the value written in the MSB ( bit 7 or bit 8 depending on the data length ) has no effect
 * 					- because it is replaced by the parity
 * 					- when receiving with the parity enabled the value read in the MSB bit is the received parity bit
 */
void MCAL_UART_SendData(USART_Typedef* USARTx, uint16_t* pTxBuffer, enum polling_mechanism PollingEn)
{

	if (PollingEn == enable)
	{
		while (!(USARTx->SR & 1<<7) );
	}
	if(Global_UART_Config->Payload_Length == Payload_Length_9B)
	{
		USARTx->DR = (*pTxBuffer & (uint16_t) 0x01FF);
	}
	else
	{
		USARTx->DR = (*pTxBuffer & (uint8_t) 0xFF);

	}
}
/* ================================================================
 * @Fn				- MCAL_UART_GPIO_Set_Pins
 * @brief			- Initializes GPIO Pins
 * @param[in]		- USARTx: where x can be (1..3 depending on device used)
 * @retval 			- None
 * @Notes			- Should enable the corresponding ALT & GPIO in RCC clock . Also called after MCAL_UART_Init()
 */
void MCAL_UART_GPIO_SetPins(USART_Typedef* USARTx)
{

	GPIO_PinConfig PinCfg;
	if(USARTx == USART1)
	{
		//PA09 --> TX
		//PA10 --> RX
		//PA11 --> CTS
		//PA12 --> RTS

		/* PA09 --> TX */
		PinCfg.GPIO_PinNumber = GPIO_PIN_9;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		/* PA10 --> RX */
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_ALT_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);



		if(Global_UART_Config->HwFlowCtl == HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS_CTS)
		{
			/* PA11 --> CTS */
			PinCfg.GPIO_PinNumber = GPIO_PIN_11;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
		if(Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS_CTS)
		{
			/* PA12 --> RTS */
			PinCfg.GPIO_PinNumber = GPIO_PIN_12;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_PP;
			PinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if(USARTx == USART2)
	{
		//PA02 --> TX
		//PA03 --> RX
		//PA00 --> CTS
		//PA01 --> RTS

		/* PA02 --> TX */
		PinCfg.GPIO_PinNumber = GPIO_PIN_2;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
		MCAL_GPIO_Init(GPIOA, &PinCfg);

		/* PA03 --> RX */
		PinCfg.GPIO_PinNumber = GPIO_PIN_3;
		PinCfg.GPIO_MODE = GPIO_MODE_ALT_INPUT;
		MCAL_GPIO_Init(GPIOA, &PinCfg);



		if(Global_UART_Config->HwFlowCtl == HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS_CTS)
		{
			/* PA00 --> CTS */
			PinCfg.GPIO_PinNumber = GPIO_PIN_0;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
		if(Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS_CTS)
		{
			/* PA01 --> RTS */
			PinCfg.GPIO_PinNumber = GPIO_PIN_1;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_PP;
			PinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}
	else if(USARTx == USART3)
	{
		//PB10 --> TX
		//PB11 --> RX
		//PB13 --> CTS
		//PB14 --> RTS

		/* PB10 -->TX */
		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_PP;
		PinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		/* PB11 -->RX */
		PinCfg.GPIO_PinNumber = GPIO_PIN_11;
		PinCfg.GPIO_MODE = GPIO_MODE_ALT_INPUT;
		MCAL_GPIO_Init(GPIOB, &PinCfg);



		if(Global_UART_Config->HwFlowCtl == HwFlowCtl_CTS || Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS_CTS)
		{
			/* PB13 --> CTS */
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}
		if(Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS || Global_UART_Config->HwFlowCtl == HwFlowCtl_RTS_CTS)
		{
			/* PA14 --> RTS */
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_PP;
			PinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
			MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
	}

}

void MCAL_UART_Wait_TC(USART_Typedef* USARTx)
{
	/* Wait till TC flag is set in the SR */
	while(!(USARTx->SR & 1<<6));
}




void USART1_IRQHandler(void)
{
	Global_UART_Config->P_IRQ_CallBack();
}
void USART2_IRQHandler(void)
{
	Global_UART_Config->P_IRQ_CallBack();
}
void USART3_IRQHandler(void)
{
	Global_UART_Config->P_IRQ_CallBack();
}















