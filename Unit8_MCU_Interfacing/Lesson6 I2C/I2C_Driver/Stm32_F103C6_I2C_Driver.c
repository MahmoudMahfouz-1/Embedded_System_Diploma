/*
 * Stm32_F103C6_I2C_Driver.c
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

//-----------------------------
//--------- Includes ----------
//-----------------------------
#include "Stm32_F103C6_I2C_Driver.h"

//==================================
/*
 * =============================================================================================
 * 								Generic Variables
 * =============================================================================================
 */

I2C_Config_t Global_I2C_Config[2] = {NULL, NULL};


/*
 * =============================================================================================
 * 								Generic Macros
 * =============================================================================================
 */

#define I2C1_index	0
#define I2C2_index  1



/*
 * =============================================================================================
 * 									   APIs
 * =============================================================================================
 */

/**================================================================
 * @Fn			-MCAL_I2C_Init
 * @brief 		-Initializes I2C
 * @param [in] 	-*I2Cx where x can be (1 .. 2)
 * @param [in] 	-I2C_config_t all I2C configuration
 * @retval		-None
 * Note			-only 7bit Mode Supported
 */
void MCAL_I2C_Init(I2C_Typedef* I2Cx, I2C_Config_t* I2C_Config)
{
	uint16_t tmpreg=0, freqRange = 0, result = 0 ;
	uint32_t pclk1 = 8000000 ;
	// Enable RCC Clock
	if(I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_index] = *I2C_Config ;
		RCC_I2C1_CLK_EN() ;
	}
	else
	{
		Global_I2C_Config[I2C2_index] = *I2C_Config ;
		RCC_I2C2_CLK_EN() ;
	}

	// Check Bus Mode
	if(I2C_Config ->Bus_Mode == Bus_Mode_I2C)
	{
		/**	Init Timing **/
		tmpreg = I2Cx->CR2 ;
		// Clear Frequency [0:5] Bits
		tmpreg &= ~(I2C_CR2_FREQ);
		// Get Pclk1 frequency
		pclk1 = MCAL_RCC_GetPCLK1Freq();
		//set frequency bits depending on pclk1 value
		freqRange = (uint16_t)(pclk1 / 1000000 );

		tmpreg |= freqRange;
		// Set I2C_CR2 reg value
		I2Cx->CR2 = tmpreg ;

		// Configue clock control registers (I2C_CCR)
		// Disable I2C
		I2Cx->CR2 &= ~(I2C_CR1_PE);
		tmpreg = 0;

		if(I2C_Config->I2C_ClockSpeed == I2C_ClockSpeed_SM_50K || I2C_Config->I2C_ClockSpeed == I2C_ClockSpeed_SM_100K)
		{
			result = (uint16_t)( pclk1 / (I2C_Config->I2C_ClockSpeed << 1)) ;
			tmpreg = I2Cx->CCR ;

			tmpreg |= result ;

			I2Cx->CCR = tmpreg ;

			I2Cx->TRISE = ( freqRange+ 1) ;
		}
		else
		{
			//			Fast Mode Not Supported
		}
		tmpreg = 0;
		tmpreg = I2Cx->CR1 ;
		tmpreg |= (uint16_t)(I2C_Config->I2C_ACK_Control | I2C_Config->G_CallAddress_Detection | I2C_Config->I2C_Clock_Stretch | I2C_Config->Bus_Mode) ;

		I2Cx->CR1 |= tmpreg ;

		/*------------------------------- I2C_OAR1 & OAR2 Configurations -------------------------------*/
		tmpreg = 0;
		if(I2C_Config->I2C_Slave_Device_Address.Enable_Dual_Address == 1)
		{
			tmpreg = I2C_OAR2_ENDUAL;
			tmpreg |= I2C_Config->I2C_Slave_Device_Address.Secondary_Slave_Address << I2C_OAR2_ADD2_Pos;
			I2Cx->OAR2 = tmpreg;
		}
		tmpreg = 0;
		tmpreg |= I2C_Config->I2C_Slave_Device_Address.Primary_Slave_Address << 1;
		tmpreg |= I2C_Config->I2C_Addressing_Mode;

		I2Cx->OAR1 = tmpreg;

		//Interrupt Mode in Slave mode
		//Check if the pointer != NULL if yes Enable interrupts
		if(I2C_Config->P_IRQ_CallBack != NULL)
		{
			//Enable IRQ
			I2Cx->CR2 |= I2C_CR2_ITBUFEN;
			I2Cx->CR2 |= I2C_CR2_ITERREN;
			I2Cx->CR2 |= I2C_CR2_ITEVTEN;
			if(I2Cx == I2C1)
			{
				NVIC_IRQ31_I2C1_EV_Enable;
				NVIC_IRQ32_I2C1_ER_Enable;
			}
			else if (I2Cx == I2C2)
			{
				NVIC_IRQ33_I2C2_EV_Enable;
				NVIC_IRQ34_I2C2_ER_Enable;
			}
		}

		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;


		// Enable I2C Peripheral
		I2Cx->CR1 |= I2C_CR1_PE;
	}
	else
	{
		//SMBus Not Supported
	}

}
void MCAL_I2C_DeInit(I2C_Typedef* I2Cx)
{
	if(I2Cx == I2C1)
	{
		RCC_I2C1_CLK_Reset();
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
	}
	else if (I2Cx == I2C2)
	{
		RCC_I2C2_CLK_Reset();
		NVIC_IRQ33_I2C2_EV_Disable;
		NVIC_IRQ34_I2C2_ER_Disable;
	}
}

void MCAL_I2C_GPIO_Set_Pins(I2C_Typedef* I2Cx)
{
	//	I2Cx_SCL I2C clock Alternate function open drain
	//	I2Cx_SDA I2C Data I/O Alternate function open drain
	GPIO_PinConfig pinCfg;
	if(I2Cx == I2C1)
	{
		//	I2C1
		//	PB6 -> SCL
		pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_OD;
		pinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
		pinCfg.GPIO_PinNumber = GPIO_PIN_6;
		MCAL_GPIO_Init(GPIOB, &pinCfg);

		//  PB7 -> SDA
		pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_OD;
		pinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
		pinCfg.GPIO_PinNumber = GPIO_PIN_7;
		MCAL_GPIO_Init(GPIOB, &pinCfg);
	}
	else if (I2Cx == I2C2)
	{
		//	I2C2
		//	PB10 -> SCL
		pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_OD;
		pinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
		pinCfg.GPIO_PinNumber = GPIO_PIN_10;
		MCAL_GPIO_Init(GPIOB, &pinCfg);
		//  PB11 -> SDA
		pinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_ALT_OD;
		pinCfg.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
		pinCfg.GPIO_PinNumber = GPIO_PIN_11;
		MCAL_GPIO_Init(GPIOB, &pinCfg);
	}
}



void MCAL_I2C_Master_TX(I2C_Typedef *I2Cx , uint16_t Address , uint8_t* PTXBuffer , uint32_t DataLen , Stop_State Stop , Repeated_Start Start)
{
	int i = 0;

	//1- Generate Start Condition
	I2C_GenerateStart(I2Cx, enable, start);

	//2- wait for EV5
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	//3- Send Address
	I2C_SendAddress(I2Cx, Address, I2C_Direction_Transmit);

	//4- wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagStatus(I2Cx, EV6));

	//5- check /* TRA, BUSY, MSL TXE */ Flags
	while(!I2C_GetFlagStatus(I2Cx, MASTER_BYTE_TRANSMITTING));

	//6- Send data
	for( i = 0; i < DataLen; i++)
	{
		// Write in the DR the data to be sent
		I2Cx->DR = PTXBuffer[i];
		//6.1- wait for EV8
		//EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register
		while( !I2C_GetFlagStatus(I2Cx, EV8) );
	}

	//7- Generate Stop Condition
	if(Stop == with_stop)
	{
		I2C_GenerateSTOP(I2Cx, eenable);
	}
}



void MCAL_I2C_Master_RX(I2C_Typedef *I2Cx , uint16_t Address , uint8_t* PRXBuffer , uint32_t DataLen , Stop_State Stop , Repeated_Start Start)
{
	uint8_t index =    (I2Cx == I2C1) ? I2C1_index : I2C2_index ;
	int i = 0;

	//1- Generate Start Condition
	I2C_GenerateStart(I2Cx, enable, start);

	//2- wait for EV5
	while(!I2C_GetFlagStatus(I2Cx, EV5));

	//3- Send Address
	I2C_SendAddress(I2Cx, Address, I2C_Direction_Recive);

	//4- wait for EV6
	//EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	while(!I2C_GetFlagStatus(I2Cx, EV6));

	//5- Open Acknowledge Configuration
	I2C_AcknowledgeConfig(I2Cx, eenable);

	//6- Check if datalen exist
	if(DataLen)
	{
		for(i = DataLen; i > 1; i--)
		{
			//5.1- wait for EV7 --> RXNE not Empty
			while(!I2C_GetFlagStatus(I2Cx, EV7));
			*PRXBuffer = I2Cx->DR;
			PRXBuffer++;
		}
	}
	//7- Disable the Acknowledge
	I2C_AcknowledgeConfig(I2Cx, ddisable);

	//8- Generate Stop Condition
	if(Stop == with_stop)
	{
		I2C_GenerateSTOP(I2Cx, eenable);
	}

	//9- activate the Acknowledge
	if(Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
	{
		I2C_AcknowledgeConfig(I2Cx, eenable);
	}
}


/*
 * =============================================================================================
 * 								Generic Functions
 * =============================================================================================
 */

flagStatus I2C_GetFlagStatus(I2C_Typedef* I2Cx, status flag)
{
	volatile uint32_t dummyread;
	flagStatus bitstatus = reset;
	uint32_t flag1= 0, flag2 = 0;
	uint32_t lastevent = 0;
	switch(flag)
	{
	case I2C_Flag_BUSY:
	{
		if( (I2Cx->SR2) & (I2C_SR2_BUSY) )
			bitstatus = set;
		else
			bitstatus = reset;
		break;

	}
	case EV5:
	{
		//	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
		//	Bit 0 SB: Start bit (Master mode)
		//	0: No Start condition
		//	1: Start condition generated.
		if((I2Cx->SR1) & (I2C_SR1_SB) )
			bitstatus = set;
		else
			bitstatus = reset;
		break;
	}
	case EV6:
	{
		//		Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
		//		This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
		//		when PE=0.
		//		Address matched (Slave)
		//		0: Address mismatched or not received.
		//		1: Received address matched.
		//		– Set by hardware as soon as the received slave address matched with the OAR registers
		//		content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert
		//		is recognized. (when enabled depending on configuration).
		if((I2Cx->SR1) & (I2C_SR1_ADDR) )
			bitstatus = set;
		else
			bitstatus = reset;
		dummyread = I2Cx->SR2;
		break;
	}
	case MASTER_BYTE_TRANSMITTING:
	{
		flag1 = I2Cx->SR1;
		flag2 = I2Cx->SR2;
		flag2 = flag2 << 16;
		lastevent = ( (flag1 | flag2)  & (uint32_t)0x00FFFFFF);
		if( (lastevent & flag )== flag)
			bitstatus = set;
		else
			bitstatus = reset;
		break;
	}
	case EV8_1:
	case EV8:
	{
		//EV8: TxE=1, shift register not empty, d . ata register empty, cleared by writing DR register
		if( (I2Cx->SR1) & (I2C_SR1_TXE) )
			bitstatus = set;
		else
			bitstatus = reset;
		break;
	}
	case EV7:
	{
		//		Bit 6 RxNE: Data register not empty (receivers) I2C_SR1
		//		0: Data register empty
		//		1: Data register not empty
		//		– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
		//		– Cleared by software reading or writing the DR register or by hardware when PE=0.
		//		RxNE is not set in case of ARLO event.
		if((I2Cx->SR1) & (I2C_SR1_RXNE))
			bitstatus = set;
		else
			bitstatus = reset;
		break;
	}

	}


	return bitstatus;
}


void I2C_AcknowledgeConfig(I2C_Typedef* I2Cx, EN_DIS NewState)
{
	//	Bit 10 ACK: Acknowledge enable
	//	This bit is set and cleared by software and cleared by hardware when PE=0.
	//	0: No acknowledge returned
	//	1: Acknowledge returned after a byte is received (matched address or data)
	if(NewState != ddisable)
	{
		I2Cx->CR1 |= I2C_CR1_ACK;
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_ACK);
	}
}


void I2C_SendAddress(I2C_Typedef* I2Cx, uint16_t address, I2C_Direction Direction)
{
	address = (address << 1);
	if(Direction != I2C_Direction_Transmit)
	{
		/* set the address bit 0 to read */
		address |= 1<<0;
	}
	else
	{
		/* set the address bit 1 to write */
		address &= ~(1<<0);
	}
	I2Cx->DR = address;
}




void I2C_GenerateStart(I2C_Typedef* I2Cx, FunctionalState NewState, Repeated_Start Start)
{
	if(Start != repeated_Start)
	{
		// Check if the bus is busy
		while(I2C_GetFlagStatus(I2Cx, I2C_Flag_BUSY) );
	}
	if(NewState != disable )
	{
		//Generate Start Condition
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		//Disable start condition generation
		I2Cx->CR1 &= ~(I2C_CR1_START);
	}
}



void I2C_GenerateSTOP(I2C_Typedef* I2Cx, EN_DIS NewState)
{
	if(NewState != ddisable)
	{
		I2Cx->CR1 |= (I2C_CR1_STOP);
	}
	else
	{
		I2Cx->CR1 &= ~(I2C_CR1_STOP);
	}


}




