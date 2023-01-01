################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.c 

OBJS += \
./Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.o 

C_DEPS += \
./Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/%.o Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/%.su: ../Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/%.c Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/LCD_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/SPI_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/RCC_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/UART_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/I2C_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/KeyPad_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/GPIO_Driver" -I../Inc -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/inc" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/EXTI_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers-2f-HAL-2f-I2C_Slave_EEPROM

clean-Stm32_F103C6_Drivers-2f-HAL-2f-I2C_Slave_EEPROM:
	-$(RM) ./Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.d ./Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.o ./Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM/I2C_Slave_EEPROM.su

.PHONY: clean-Stm32_F103C6_Drivers-2f-HAL-2f-I2C_Slave_EEPROM

