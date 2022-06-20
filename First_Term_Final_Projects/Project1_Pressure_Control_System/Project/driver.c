#include "driver.h"
#include <stdint.h>
#include <stdio.h>

void Delay(int nCount)
{
	for(; nCount != 0; nCount--);
}


void GPIO_INITIALIZATION (){
	SET_BIT(APB2ENR, 2);
	GPIOA_CRL &= 0xFF0FFFFF;
	GPIOA_CRL |= 0x00000000;
	GPIOA_CRH &= 0xFF0FFFFF;
	GPIOA_CRH |= 0x22222222;
}
