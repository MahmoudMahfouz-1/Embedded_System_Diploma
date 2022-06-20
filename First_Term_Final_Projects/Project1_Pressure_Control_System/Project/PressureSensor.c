
#include "PressureSensor.h"

// Function to read the value from the sensor
int getPressureVal()
{
	return (GPIOA_IDR & 0xFF);
}