/*
 * Stm32_F103C6_I2C_Driver.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

#ifndef INC_STM32_F103C6_I2C_DRIVER_H_
#define INC_STM32_F103C6_I2C_DRIVER_H_


//-----------------------------
//--------- Includes ----------
//-----------------------------

#include "stm32f013x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"
#include "Stm32_F103C6_RCC_Driver.h"

//-----------------------------
//User type definitions (structures, enums)
//-----------------------------
struct S_I2C_Slave_Device_Address
{
	uint16_t Enable_Dual_Address ; 	//1-Enable	0-disable
	uint16_t Primary_Slave_Address;
	uint16_t Secondary_Slave_Address;
};


//@ref Slave_State_define
typedef enum
{
	I2C_EV_STOP,
	I2C_EV_ADDR_Matched,
	I2C_EV_DATA_REQ,
	I2C_EV_DATA_RCV
}Slave_State;

typedef struct
{
	uint32_t  Bus_Mode;								//select SMBus / I2C Mode
													//@ref Bus_Mode_define

	uint32_t  I2C_ClockSpeed;						//configure I2C communication Speed Mode( SM or FM)
													//@ref I2C_ClockSpeed_define

	uint32_t  I2C_Clock_Stretch;					//enable or disable Stretch_Mode
													//@ref I2C_Clock_Stretch_Define

	uint32_t I2C_Addressing_Mode;					//select addressing mode(7-bit/10-bit)
													//@ref I2C_Addressing_Mode_define

	struct S_I2C_Slave_Device_Address I2C_Slave_Device_Address;


	uint32_t I2C_ACK_Control;						//enable or disable the ACK of transmitted data
													//@ref I2C_ACK_Define

	uint32_t G_CallAddress_Detection;				//enable or disable General Call Address Detection
													//@ref General_CallAddress_Define

	uint32_t I2C_IRQ_Enable;						//enable or disable I2C IRQ Event/Error
													//@ref I2C_IRQ_Enable_define

	void (*P_IRQ_CallBack)(Slave_State state);		//pointer to IRQ call back function which will be called once IRQ happened
													//Slave State is the source of IRQ @ref Slave_State_define
}I2C_Config_t;

//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref I2C_ClockSpeed_define
#define I2C_ClockSpeed_SM_50K 			(0x50000U)
#define I2C_ClockSpeed_SM_100K 			(100000U)
#define I2C_ClockSpeed_FM_200K 			(0x50000U)	/* Fast Mode Not Supported yet */
#define I2C_ClockSpeed_FM_400K 			(0x50000U)	/* Fast Mode Not Supported yet */

//@ref I2C_Clock_Stretch_Define
//Bit 7 NOSTRETCH: Clock stretching disable (Slave mode) --> CR1 Register
#define I2C_Clock_Stretch_Enabled  			 (0x00000000U)
#define	I2C_Clock_Stretch_Disabled			 I2C_CR1_NOSTRETCH

//@ref Bus_Mode_define
//Bit 1 SMBUS: SMBus mode --> CR1 Register
//0: I2C mode
//1: SMBus mode
#define Bus_Mode_I2C					(0x00000000U)
#define Bus_Mode_SMBus					I2C_CR1_SMBUS


//@ref I2C_Addressing_Mode_define
//I2C_OAR1.ADDMODE
//Bit 15 ADDMODE Addressing mode (slave mode)
#define	Addressing_Mode_7Bits	(0x00000000U)
#define	Addressing_Mode_10Bits	(uint16_t))(1 << 15)

//@ref I2C_ACK_Define
//Bit 10 ACK: Acknowledge enable
//This bit is set and cleared by software and cleared by hardware when PE=0.
//0: No acknowledge returned
//1: Acknowledge returned after a byte is received (matched address or data)
#define I2C_ACK_Enable	I2C_CR1_ACK
#define	I2C_ACK_Disable	((uint16_t)0x0000)

//@ref General_CallAddress_Define
//Bit 6 ENGC: General call enable
//0: General call disabled. Address 00h is NACKed.
//1: General call enabled. Address 00h is ACKed.
#define General_CallAddress_Enable	I2C_CR1_ENGC
#define General_CallAddress_Disable	(0x00000000U)

//@ref I2C_IRQ_Enable_define
#define I2C_IRQ_ENABLE_Disable 						(uint16_t)(~(7<<5))
#define I2C_IRQ_ENABLE_I2C_EV						(uint16_t)(1<<9)
#define I2C_IRQ_ENABLE_I2C_ER						(uint16_t)(1<<8)

//******************************************
typedef enum
{
	with_stop,
	without_stop
}Stop_State;

typedef enum
{
	start,
	repeated_Start
}Repeated_Start;

typedef enum
{
	disable,
	enable
}FunctionalState;

typedef enum
{
	reset,
	set
}flagStatus;

typedef enum
{
	ddisable,
	eenable
}EN_DIS;

typedef enum
{
	I2C_Direction_Transmit,
	I2C_Direction_Recive
}I2C_Direction;
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING		((uint32_t)0x00070080)
typedef enum
{
	I2C_Flag_BUSY,
	EV5,  	//	EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	EV6,	//  EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
	EV8,	//  EV8: TxE=1, shift register not empty, data register empty, cleared by writing DR register
	EV8_1,  //  EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR
	EV7,
	MASTER_BYTE_TRANSMITTING = ((uint32_t)0x00070080)

}status;



/*
 * =============================================================================================
 * 								APIs Supported by "MCAL I2C DRIVER"
 * =============================================================================================
 */

void MCAL_I2C_Init(I2C_Typedef* I2Cx, I2C_Config_t* I2C_Config);
void MCAL_I2C_DeInit(I2C_Typedef* I2Cx);
void MCAL_I2C_GPIO_Set_Pins(I2C_Typedef* I2Cx);


void MCAL_I2C_Master_TX(I2C_Typedef *I2Cx , uint16_t Address , uint8_t* PTXBuffer , uint32_t DataLen , Stop_State Stop , Repeated_Start Start);
void MCAL_I2C_Master_RX(I2C_Typedef *I2Cx , uint16_t Address , uint8_t* PRXBuffer , uint32_t DataLen , Stop_State Stop , Repeated_Start Start);

/* TODO Slave Receive and Transmit */
//uint8_t MCAL_I2C_Slave_RX(I2C_Typedef *I2Cx );
//void MCAL_I2C_Slave_TX(I2C_Typedef *I2Cx ,uint8_t PTXBuffer);



/*
 * =============================================================================================
 * 								Generic APIs
 * =============================================================================================
 */
void I2C_GenerateStart(I2C_Typedef* I2Cx, FunctionalState NewState, Repeated_Start Start);
flagStatus I2C_GetFlagStatus(I2C_Typedef* I2Cx, status flag);
void I2C_SendAddress(I2C_Typedef* I2Cx, uint16_t address, I2C_Direction Direction);
void I2C_GenerateSTOP(I2C_Typedef* I2Cx, EN_DIS NewState);
void I2C_AcknowledgeConfig(I2C_Typedef* I2Cx, EN_DIS NewState);


#endif /* INC_STM32_F103C6_I2C_DRIVER_H_ */
