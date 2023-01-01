/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Mahmoud Essam
 */

#ifndef HAL_I2C_SLAVE_EEPROM_I2C_SLAVE_EEPROM_H_
#define HAL_I2C_SLAVE_EEPROM_I2C_SLAVE_EEPROM_H_

#include "Stm32_F103C6_I2C_Driver.h"

#define EEPROM_Slave_Address 	0x2A

void EEPROM_Init(void);
unsigned char EEPROM_Write_NBytes(unsigned int Memory_Address, unsigned char* bytes, uint8_t DataLength);
unsigned char EEPROM_read_Byte(unsigned int address, uint8_t dataOut, uint8_t DataLength);

#endif /* HAL_I2C_SLAVE_EEPROM_I2C_SLAVE_EEPROM_H_ */
