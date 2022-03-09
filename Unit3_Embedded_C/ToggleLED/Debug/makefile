################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Online_Diploma_Mahmoud.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Online_Diploma_Mahmoud.list \

OBJCOPY_HEX += \
Online_Diploma_Mahmoud.hex \

OBJCOPY_BIN += \
Online_Diploma_Mahmoud.bin \


# All Target
all: Online_Diploma_Mahmoud.elf secondary-outputs

# Tool invocations
Online_Diploma_Mahmoud.elf: $(OBJS) $(USER_OBJS) E:\Work\STM32CubeIDE\Online_Diploma_Mahmoud\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -o "Online_Diploma_Mahmoud.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"E:\Work\STM32CubeIDE\Online_Diploma_Mahmoud\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Online_Diploma_Mahmoud.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Online_Diploma_Mahmoud.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Online_Diploma_Mahmoud.list"
	@echo 'Finished building: $@'
	@echo ' '

Online_Diploma_Mahmoud.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Online_Diploma_Mahmoud.hex"
	@echo 'Finished building: $@'
	@echo ' '

Online_Diploma_Mahmoud.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Online_Diploma_Mahmoud.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
