/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Mahmoud Essam
 */


#include "I2C_Slave_EEPROM.h"


void EEPROM_Init(void)
{
	/* I2C Init */
	I2C_Config_t I2C1Cfg;

	I2C1Cfg.G_CallAddress_Detection = General_CallAddress_Enable;
	I2C1Cfg.I2C_ACK_Control = I2C_ACK_Enable;
	I2C1Cfg.I2C_ClockSpeed = I2C_ClockSpeed_SM_100K;
	I2C1Cfg.Bus_Mode = Bus_Mode_I2C;
	I2C1Cfg.P_IRQ_CallBack = NULL;
	I2C1Cfg.I2C_Clock_Stretch = I2C_Clock_Stretch_Enabled;

	MCAL_I2C_GPIO_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C1Cfg);
}
unsigned char EEPROM_Write_NBytes(unsigned int Memory_Address, unsigned char* bytes, uint8_t DataLength)
{

	uint8_t i =0;
	uint8_t buffer[256];
	buffer[0] = (uint8_t)(Memory_Address >> 8) ; // Upper Byte Memory Address
	buffer[1] = (uint8_t)(Memory_Address) 	   ; // Lower Byte Memory Address

	for(i = 2; i < (DataLength+2) ; i++)
	{ buffer[i] = bytes[i-2]; }

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, buffer, (DataLength+2), with_stop, start);

	return 0;
}
unsigned char EEPROM_read_Byte(unsigned int address, uint8_t dataOut, uint8_t DataLength)
{

	unsigned char buffer[2];
	buffer[0] = (uint8_t)(address >> 8) ; // Upper Byte Memory Address
	buffer[1] = (uint8_t)(address) 	   ; // Lower Byte Memory Address

	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_Address, &buffer, 2, with_stop, start); // write address only


	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_Address, dataOut, DataLength, with_stop, repeated_Start); // read address





}
