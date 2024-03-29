/*
 * KeyPad.c
 *
 *  Created on: Sep 27, 2022
 *      Author: Mahmoud Essam
 */

#include "keypad.h"

uint32_t keypad_R[] = {R0, R1, R2, R3}; // Rows of the keypad
uint32_t keypad_C[] = {C0, C1, C2, C3}; // Columns of the keypad



void HAL_KEYPAD_INIT(void)
{


	GPIO_PinConfig PinConfig;

	PinConfig.GPIO_PinNumber = R0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R2;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = R3;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C0;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C1;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C2;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	PinConfig.GPIO_PinNumber = C3;
	PinConfig.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	PinConfig.GPIO_Output_Speed = GPIO_OUTPUT_SPEED_10_MHz;
	MCAL_GPIO_Init(KEYPAD_PORT, &PinConfig);

	MCAL_GPIO_WritePort(KEYPAD_PORT, 0xFF);
}


char HAL_KEYPAD_GET_KEY(void)
{
	int i, j;

	for (i = 0; i < 4; i++)
	{

		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_C[0], GPIO_STATUS_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_C[1], GPIO_STATUS_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_C[2], GPIO_STATUS_SET);
		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_C[3], GPIO_STATUS_SET);

		MCAL_GPIO_WritePin(KEYPAD_PORT, keypad_C[i], GPIO_STATUS_RESET);

		for (j = 0; j < 4; j++)
		{
			if (MCAL_GPIO_ReadPin(KEYPAD_PORT, keypad_R[j]) == 0)
			{
				while (MCAL_GPIO_ReadPin(KEYPAD_PORT, keypad_R[j]) == 0);// Wait for the key to be released (Single pressed)

				switch (i)
				{
				case 0:
					if (j == 0) return '7';
					else if(j == 1) return '4';
					else if(j == 2) return '1';
					else if(j == 3) return '?';
					break;

				case 1:
					if (j == 0) return '8';
					else if(j == 1) return '5';
					else if(j == 2) return '2';
					else if(j == 3) return '0';
					break;

				case 2:
					if (j == 0) return '9';
					else if(j == 1) return '6';
					else if(j == 2) return '3';
					else if(j == 3) return '=';
					break;

				case 3:
					if (j == 0) return '/';
					else if(j == 1) return '*';
					else if(j == 2) return '-';
					else if(j == 3) return '+';
					break;
				}
			}
		}
	}
	return 'A'; // Return 'A' if no key is pressed
}
