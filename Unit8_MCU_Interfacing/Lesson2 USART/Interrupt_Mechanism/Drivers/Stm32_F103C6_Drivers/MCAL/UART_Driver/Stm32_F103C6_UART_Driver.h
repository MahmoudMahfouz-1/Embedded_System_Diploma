/*
 * Stm32_F103C6_UART_Driver.h
 *
 *  Created on: Sep 20, 2022
 *      Author: Mahmoud Essam
 */

#ifndef INC_STM32_F103C6_UART_DRIVER_H_
#define INC_STM32_F103C6_UART_DRIVER_H_


//-----------------------------
//--------- Includes ----------
//-----------------------------

#include "stm32f013x6.h"
#include "Stm32_F103C6_GPIO_Driver.h"
#include "Stm32_F103C6_RCC_Driver.h"

//-----------------------------
//User type definitions (structures)
//-----------------------------

typedef struct
{
	uint8_t 		USART_Mode ;		// Specifies TX/Rx Mode
										// The parameter can be a value of @ref USART_Mode_define

	uint32_t		BaudRate ;			// Specifies Baud Rate
										// The parameter can be a value of @ref BaudRate_define

	uint8_t 		Payload_Length;		// Specifies 8bit data or 9bit data
										// The parameter can be a value of @ref Payload_Length_define

	uint8_t			Parity;				// Specifies parity mode Odd/Even
										// The parameter can be a value of @ref Parity_define

	uint8_t			StopBits;			// Specifies Number of stop Bits 0.5 or 1 or 1.5 or 2
										// The parameter can be a value of @ref StopBits_define

	uint8_t			HwFlowCtl;			// Specifies weather hardware flow control is enabled or disabled
										// The parameter can be a value of @ref HwFlowCtl_define

	uint8_t			IRQ_Enable;			// Enable and Disable USART IQR TX/RX
										// The parameter can be a value of @ref IRQ_Enable_define

	void(* P_IRQ_CallBack)(void) ;		// Set the C func which will be called once the IRQ happen

}USART_Config;


//-----------------------------
//Macros Configuration References
//-----------------------------

//@ref USART_Mode_define
#define USART_Mode_TX			((uint32_t)1 << 3) 		// Transmitter enable
#define USART_Mode_RX			((uint32_t)1 << 2)		// Receiver enable
#define USART_Mode_TX_RX		((uint32_t)1 << 3 | 1 << 2)		// Transmitter&Receiver enable


//@ref BaudRate_define
#define BaudRate_2400				2400
#define BaudRate_9600				9600
#define BaudRate_19200				19200
#define BaudRate_57600				57600
#define BaudRate_115200				115200
#define BaudRate_230400				230400
#define BaudRate_460800				460800
#define BaudRate_921600				921600
#define BaudRate_2250000			2250000
#define BaudRate_4500000			4500000


//@ref Payload_Length_define
#define Payload_Length_8B	(uint32_t)(0)				// 8 Bits Pat load length
#define Payload_Length_9B	(uint32_t)(1 << 12)			// 9 Bits Pat load length


//@ref Parity_define
#define Parity_None			(uint32_t)(0)					// Parity Disabled
#define Parity_Even			((uint32_t)1 << 10)				// Parity Even Enabled
#define Parity_Odd			((uint32_t)1 << 10 | 1 << 9)	// Parity Odd Enabled


//@ref StopBits_define
#define StopBits_half       ((uint32_t)1 << 12)
#define StopBits_1	 		(uint32_t)(0)
#define StopBits_1_half 	((uint32_t)3 << 12)
#define StopBits_2			((uint32_t)2 << 12)


//@ref HwFlowCtl_define
#define HwFlowCtl_None  	(uint32_t)(0)
#define HwFlowCtl_RTS 		((uint32_t)1 << 8)
#define HwFlowCtl_CTS 		((uint32_t)1 << 9)
#define HwFlowCtl_RTS_CTS 	((uint32_t)1 << 8 | 1 << 9)


//@ref IRQ_Enable_define
#define IRQ_Enable_CTS 			((uint32_t)1 << 10)		// CTS interrupt enable
#define IRQ_Enable_PE 			((uint32_t)1 << 8)		// Parity Error interrupt enable
#define IRQ_Enable_TC			((uint32_t)1 << 6)		// Transmission complete interrupt enable
#define IRQ_Enable_RXNEIE 		((uint32_t)1 << 5)		// RXNE(Receive Not Empty) interrupt enable
#define IRQ_Enable_None 		(uint32_t)(0)			// NO interrupt enabled

////@ref UART_IRQ_Event_define
//enum UART_IRQ_Event
//{
//	UART_IRQ_TXE,	// Transmit data register empty
//	UART_IRQ_TC,	// Transmission complete
//	UART_IRQ_RXNE,	// Received data ready to be read
//	UART_IRQ_ORE,	// Overrun error detected
//	UART_IRQ_PE		// Parity error
//};

//@ref polling_mechanism
enum polling_mechanism
{
	enable,
	disable
};

//-----------------------------
//   Baud Rate Calculations
//-----------------------------

// USARTDIV = fclk / (16 * Baudrate)
// USARTDIV_MUL100 = uint32((100 * fclk ) / ( 16 * Baudrate) == (25 * fclk) / (4 * Baudrate))
// DIV_Mantissa_MUL100 = Integer Part (USARTDIV) * 100
// DIV_Mantissa = Integer Part (USARTDIV)
// DIV_Fraction = (( USARTDIV_MUL100 - DIV_Mantissa_MUL100 ) *16) / 100

#define USARTDIV(_PCLK_, _BAUD_)				(uint32_t) (_PCLK_/(16 * _BAUD_ ))
#define USARTDIV_MUL100(_PCLK_, _BAUD_)			(uint32_t) ((25 * _PCLK_ ) / (4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_, _BAUD_)			(uint32_t) (USARTDIV(_PCLK_, _BAUD_) * 100)
#define Mantissa(_PCLK_, _BAUD_)				(uint32_t) (USARTDIV(_PCLK_, _BAUD_ ))
#define DIV_Fraction(_PCLK_, _BAUD_)			(uint32_t) (((USARTDIV_MUL100(_PCLK_, _BAUD_) - Mantissa_MUL100(_PCLK_, _BAUD_) )*16) / 100)
#define UART_BRR_Register(_PCLK_, _BAUD_)		(( Mantissa (_PCLK_, _BAUD_ ) ) << 4 )|((DIV_Fraction(_PCLK_, _BAUD_)) & 0xF )



/*
 * =============================================================================================
 * 								APIs Supported by "MCAL UART DRIVER"
 * =============================================================================================
 */

void MCAL_UART_Init(USART_Typedef* USARTx, USART_Config* UART_Config );
void MCAL_UART_DeInit(USART_Typedef* USARTx);
void MCAL_UART_GPIO_SetPins(USART_Typedef* USARTx);
void MCAL_UART_SendData(USART_Typedef* USARTx, uint16_t* pTxBuffer, enum polling_mechanism PollingEn);
void MCAL_UART_ReceiveData(USART_Typedef* USARTx, uint16_t* pTxBuffer, enum polling_mechanism PollingEn);
void MCAL_UART_Wait_TC(USART_Typedef* USARTx);



#endif /* INC_STM32_F103C6_UART_DRIVER_H_ */
