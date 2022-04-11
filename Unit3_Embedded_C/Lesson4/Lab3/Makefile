# Makefile for ARM-CortexM3
# Eng.Mahmoud
CC=arm-none-eabi-
CFLAGS=-mcpu=cortex-m4 -gdwarf-2 -g
INCS=-I .
LIBS=
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
As=$(wildcard *.s)
AsOBJ=$(As:.s=.o)
Project_name=Unit3-Lab4-CortexM4
all: $(Project_name).bin
	@echo "=============== Build is Done ==============="

%.o: %.c
	$(CC)gcc.exe -c $(CFLAGS) $(INCS) $< -o $@

$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map-file.map
	cp $(Project_name).elf $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy.exe -O binary $< $@
	
sym:
	$(CC)nm.exe $(Project_name).elf
dumb:
	$(CC)objdump.exe -h $(Project_name).elf

clean:
	rm *.elf *.bin 

clean_all:
	rm *.o *.elf *.bin

