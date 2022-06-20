#include <stdint.h>
#include <stdio.h>

#include "lib.h"

int main (){
	GPIO_INITIALIZATION();
	while (1)
	{
		AlarmMonitor();
	}

}
