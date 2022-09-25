/*
 * LCD Driver.c
 *
 * Created: 9/24/2022 10:26:08 PM
 * Author : Mahmoud Essam
 */ 

#include "LCD_Driver/LCD.h"
#include "KeyPad_Driver/KeyPad.h"

int main(void)
{
    /* Replace with your application code */
	LCD_INIT();
	KEYPAD_Init();
	char pressed_key;
    while (1) 
    {
		pressed_key = KEYPAD_Get_Char();
		switch (pressed_key)
		{
			case '!':
				LCD_CLEAR_SCREEN();
				break;
			case 'N':
				break;
			default:
				LCD_WRITE_CHAR(pressed_key);
				break; 
		}
    }
}

