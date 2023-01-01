################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/LCD_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/I2C_Slave_EEPROM" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/SPI_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/RCC_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/UART_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/I2C_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/KeyPad_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/GPIO_Driver" -I../Inc -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/inc" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/EXTI_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

