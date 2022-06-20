// Startup.c
// Eng.Mahmoud Essam
#include "stdint.h"
void Reset_Handler(void);
void Defaut_Handler(void);
extern int main(void);
void Defaut_Handler(void)
{
	Reset_Handler();
}

void NMI_Handler(void) __attribute__((weak, alias("Defaut_Handler")));
void H_fault_Handler(void) __attribute__((weak, alias("Defaut_Handler")));
void MM_Fault_Handler(void) __attribute__((weak, alias("Defaut_Handler")));
void Bus_Fault(void) __attribute__((weak, alias("Defaut_Handler")));
void Usage_Fault_Handler(void) __attribute__((weak, alias("Defaut_Handler")));
extern unsigned int _stack_top; 
uint32_t vectors[]__attribute__((section(".vectors"))) =
{
	(uint32_t) &_stack_top,
	(uint32_t) &Reset_Handler,
	(uint32_t) &NMI_Handler,
	(uint32_t) &H_fault_Handler,
	(uint32_t) &MM_Fault_Handler,
	(uint32_t) &Bus_Fault,
	(uint32_t) &Usage_Fault_Handler,
};
extern unsigned int _E_TEXT_;
extern unsigned int _S_DATA_;
extern unsigned int _E_DATA_;
extern unsigned int _S_BSS_;
extern unsigned int _E_BSS_;


void Reset_Handler(void)
{
	// Copy .data section from flash to sram
	unsigned int DATA_size = (unsigned char*)&_E_DATA_ - (unsigned char*)&_S_DATA_;
	unsigned char* p_src = (unsigned char*)&_E_TEXT_; // end of flash
	unsigned char* p_dst = (unsigned char*)&_S_DATA_; // start of sram
	for(int i = 0; i < DATA_size ; i++)
	{
		*p_dst++ = *p_src++;
	}
	// Init .bss section
	unsigned int BSS_size = (unsigned char*)&_E_BSS_ - (unsigned char*)&_S_BSS_ ;
	p_dst = (unsigned char*)&_S_BSS_;
	for(int i = 0; i < BSS_size ; i++)
	{
		*p_dst++ = (unsigned char)0;
	}
	// Jumb main
	

	main();
}
