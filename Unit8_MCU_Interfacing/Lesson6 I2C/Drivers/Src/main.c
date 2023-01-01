
/*
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Essam
 * @brief          : Main program body
 ******************************************************************************
/*
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

//#include "LCD.h"
//#include "KeyPad.h"
#include "stm32f013x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"
#include "Stm32_F103C6_EXTI_Driver.h"
//#include "Stm32_F103C6_UART_Driver.h"
#include "Stm32_F103C6_SPI_Driver.h"
#include "Stm32_F103C6_I2C_Driver.h"
#include "I2C_Slave_EEPROM.h"
//#define MCU_Act_As_Master
#define MCU_Act_As_Slave


void clock_init(void)
{
	// GPIOA clock enable
	RCC_GPIOA_CLK_EN();

	// GPIOB clock enable
	RCC_GPIOB_CLK_EN();

	// AFIO clock enable
	RCC_AFIO_CLK_EN();
}

//unsigned char data;
//
//void Mahmoud_SPI1_IRQ_Callback(struct S_IRQ_SRC irq_src)
//{
//#ifdef MCU_Act_As_Slave
//	if(irq_src.RXNE)
//	{
//		data = 0xf;
//		MCAL_SPI_TX_RX(SPI1,&data,SPI_disable);
//		MCAL_UART_SendData(USART1, &data, enable);
//	}
//#endif
//}

//void Mahmoud_UART_IRQ_CallBack(void)
//{
//#ifdef MCU_Act_As_Master
//	MCAL_UART_ReceiveData(USART1, &data, disable);
//	MCAL_UART_SendData(USART1, &data, enable);
//	/* Send Data to SPI */
//	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0); /* Slave Select is 0 to send the data */
//	MCAL_SPI_TX_RX(SPI1, &data, SPI_enable);
//	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1); /* Slave Select is 1 to end the data Transition */
//#endif
//}


int main(void)
{
	clock_init();

	//	// ================== UART Init ==================
	//	USART_Config USART1_Config;
	//
	//	USART1_Config.BaudRate = BaudRate_115200;
	//	USART1_Config.HwFlowCtl = HwFlowCtl_None;
	//	USART1_Config.IRQ_Enable = IRQ_Enable_RXNEIE;
	//
	//	USART1_Config.P_IRQ_CallBack = Mahmoud_UART_IRQ_CallBack;
	//
	//	USART1_Config.Parity = Parity_None;
	//	USART1_Config.Payload_Length = Payload_Length_8B;
	//	USART1_Config.StopBits = StopBits_1;
	//	USART1_Config.USART_Mode = USART_Mode_TX_RX;
	//
	//	MCAL_UART_Init(USART1, &USART1_Config);
	//	MCAL_UART_GPIO_SetPins(USART1);
	//
	//
	//	// ================== SPI Init ==================
	//	// PA4 : SPI_NSS
	//	// PA5 : SPI_SCK
	//	// PA6 : SPI_MISO
	//	// PA7 : SPI_MOSI
	//
	//	// Common Configurations
	//	SPI_Config_t SPI1_CFG;
	//	SPI1_CFG.CLK_Phase = CLK_PHASE_SECOND;
	//	SPI1_CFG.CLK_Polarity = CLK_POLARITY_IDLE_HIGH;
	//	SPI1_CFG.Frame_Size = FRAME_SIZE_8BIT;
	//	SPI1_CFG.Frame_Format= FRAME_FORMAT_MSB_FIRST;
	//	SPI1_CFG.BaudRate_Prescaler = BAUDERATE_PRESCALER_8;
	//	SPI1_CFG.Communication_Mode = COMMUNICATION_MODE_2LINE_FULL_DUPLEX;
	//
	//#ifdef MCU_Act_As_Master
	//	SPI1_CFG.SPI_Mode = SPI_MODE_MASTER;
	//	SPI1_CFG.IRQ_Enable = IRQ_DISABLE;
	//	SPI1_CFG.NSS = NSS_SW_SSI_SET;
	//	SPI1_CFG.P_IRQ_CallBack = NULL;
	//
	//
	//	// Configure SS On PORT A 4 By GPIO
	//	GPIO_PinConfig PinCfg;
	//	PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	//	PinCfg.GPIO_PinNumber = GPIO_PIN_4;
	//	PinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	//
	//	MCAL_GPIO_Init(GPIOA, &PinCfg);
	//
	//	/* Force Slave Select High in Idle Mode */
	//	MCAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	//#endif
	//
	//
	//#ifdef MCU_Act_As_Slave
	//	SPI1_CFG.SPI_Mode = SPI_MODE_SLAVE;
	//	SPI1_CFG.IRQ_Enable = IRQ_ENABLE_RXNEIE;
	//	SPI1_CFG.NSS = NSS_HW_SLAVE;
	//	SPI1_CFG.P_IRQ_CallBack = Mahmoud_SPI1_IRQ_Callback;
	//#endif
	//	MCAL_SPI_Init(SPI1, &SPI1_CFG);
	//	MCAL_SPI_GPIO_Set_Pins(SPI1);

	unsigned char ch1[] = {0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7};
	unsigned char ch2[7] = {0};

	// Test Case 1
	EEPROM_Init();
	EEPROM_Write_NBytes(0xAF, ch1, 7);
	EEPROM_read_Byte(0xAF, ch2, 7);


	// Test Case 2
	ch1[0] = 0xA;
	ch1[1] = 0xB;
	ch1[2] = 0xC;
	ch1[3] = 0xD;

	EEPROM_Write_NBytes(0xFFF, ch1, 4);
	EEPROM_read_Byte(0xFFF, ch2, 4);

	/* Super Loop */
	while(1)
	{}
}

