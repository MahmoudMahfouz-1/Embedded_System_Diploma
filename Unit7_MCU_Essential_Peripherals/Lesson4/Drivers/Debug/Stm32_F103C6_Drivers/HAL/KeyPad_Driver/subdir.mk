################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/HAL/KeyPad_Driver/KeyPad.c 

OBJS += \
./Stm32_F103C6_Drivers/HAL/KeyPad_Driver/KeyPad.o 

C_DEPS += \
./Stm32_F103C6_Drivers/HAL/KeyPad_Driver/KeyPad.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/HAL/KeyPad_Driver/KeyPad.o: ../Stm32_F103C6_Drivers/HAL/KeyPad_Driver/KeyPad.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/LCD_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/HAL/KeyPad_Driver" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/GPIO_Driver" -I../Inc -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/inc" -I"X:/Projects/STM32CupeIDE/Drivers/Stm32_F103C6_Drivers/MCAL/EXTI_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/HAL/KeyPad_Driver/KeyPad.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

