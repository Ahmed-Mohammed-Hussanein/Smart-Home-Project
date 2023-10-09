/*
 * atmega32_USART_Driver.h
 *
 * Created: 9/3/2023 10:54:31 PM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_USART_DRIVER_H_
#define ATMEGA32_USART_DRIVER_H_


// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "Utils.h"

#include "atmega32_device_header.h"


// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

// XCK --> PB0
// PD0 --> RXD
// PD1 --> TXD

typedef struct
{
	uint16_t USART_baudRate;			/* This specifies the speed of transmission and receiving.
										This parameter must be a value of @ref USART_BAUDRATE_define.
									*/
	
	uint8_t USART_characterSize;		/* This specifies frame's payload character size.
									  This parameter must be a value of @ref USART_CHARSIZE_define.
									*/
	
	uint8_t USART_clockPolarity;		 /* This specifies the edge of the clock where the data is sampled.
										This parameter must be a value of @ref USART_PLORITY_define.
										*/
	
	uint8_t USART_communicationMode;	/* This specifies the mode of communication between Tx and Rx.
										This parameter must be a value of @ref USART_MODE_define.
										*/
	
	uint8_t USART_parityMode;			/* This specifies the parity bit in the frame.
										This parameter must be a value of @ref USART_PARITYMODE_define.
										*/

	uint8_t USART_stopBit;				/* This specifies the number of stop bit in the frame.
										  This parameter must be a value of @ref USART_STOPBIT_define.
										  */
	
	uint8_t USART_INT_EN;				/* This is used to enable the interrupt or disable it.
										This parameter must be a value of @ref USART_INT_define.
										*/
	
}	USART_Config_t;


// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

// @ref USART_DAUDRATE_define.
// @ f = 8MHz and Normal speed mode
#define USART_BAUDRATE_NORMAL_2400				207		// error 0.2%
#define USART_BAUDRATE_NORMAL_4800				103		// error 0.2%


// @ f = 8MHz and Double speed mode
#define USART_BAUDRATE_DOUBLE_4800				207		// error 0.2%
#define USART_BAUDRATE_DOUBLE_9600				103		// error 0.2%

// @ref USART_CHARSIZE_define.
#define USART_CHARSIZE_5						0
#define USART_CHARSIZE_6						1
#define USART_CHARSIZE_7						2
#define USART_CHARSIZE_8						3
#define USART_CHARSIZE_9						7

// @ref USART_PLORITY_define. // for synchronous mode only
#define USART_PLORITY_FALLING					0
#define USART_PLORITY_RISING					1

// @ref USART_MODE_define.
#define USART_MODE_ASYNC_NORMAL					0
#define USART_MODE_ASYNC_DOUBLE					1
#define USART_MODE_SYNC_MASETER					2
#define USART_MODE_SYNC_SLAVE					3

// @ref USART_PARITYMODE_define.
#define USART_PARITYMODE_DISABLE				0
#define USART_PARITYMODE_EVEN					2
#define USART_PARITYMODE_ODD					3

// @ref USART_STOPBIT_define
#define USART_STOPBIT_1							0
#define USART_STOPBIT_2							1

// @ref USART_INT_define.
#define USART_INT_DISABLE						0
#define USART_INT_UDRE_ENABLE					1
#define USART_INT_TXC_ENABLE					2
#define USART_INT_RXC_ENABLE					4


// ===================================================
// ================== APIs Functions =================
// ===================================================
void MCAL_USART_Init(USART_Config_t *config);

void MCAL_USART_sendData(uint8_t TxBuffer);
void MCAL_USART_sendString(uint8_t strTxBuffer[]);
void MCAL_USART_sendInt32(uint32_t number32);

void MCAL_USART_receiveData(uint8_t *RxData);
void MCAL_USART_receiveString(uint8_t strRxBuffer[]);
void MCAL_USART_receiveInt32(uint32_t *number32);



/* CallBack Function */
void USART_RXComplete_IRQHandle(void);
void USART_DataRegisterEmpty_IRQHandle(void);
void USART_TXComplete_IRQHandle(void);





#endif /* ATMEGA32_USART_DRIVER_H_ */