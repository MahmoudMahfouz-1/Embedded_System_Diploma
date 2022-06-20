#include "lib.h"
#define threshold 20
int x = 0;
void AlarmMonitor()
{
	x = getPressureVal();
	// if pressure value > threshold start alarm
	if( x > threshold)
	{
		Set_Alarm_actuator(1);
		Delay(100000);
		Set_Alarm_actuator(0);
		Delay(100000);
	}

}