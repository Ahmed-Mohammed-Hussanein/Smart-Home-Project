/*
 * atmega32_USART_Driver.c
 *
 * Created: 9/3/2023 10:54:01 PM
 *  Author: Ahmed
 */ 

// =============================================
// ================== Includes =================
// =============================================

#include <avr/interrupt.h>

#include "Utils.h"

#include "atmega32_USART_Driver.h"
#include "atmega32_GPIO_Driver.h"

/*
 * ===========================================================================
 * ================================= Private Macros ==========================
 * ===========================================================================
 */

/* UBBRH */
#define _URSEL						7
#define _UBRR						0


/* UCSRC */
#define _URSEL						7
#define _UMSEL						6
#define _UPM1						5
#define _UPM0						4
#define _USBS						3
#define _UCSZ1						2
#define _UCSZ0						1
#define _UCPOL						0

/* UCSRB */
#define _RXCIE						7
#define _TXCIE						6
#define _UDRIE						5
#define _RXEN						4
#define _TXEN						3
#define _UCSZ2						2
#define _RXB8						1
#define _TXB8						0

/* UCSRA */
#define _RXC						7
#define _TXC						6
#define _UDRE						5
#define _FE							4
#define _DOR						3
#define _PE							2
#define _U2X						1
#define _MPCM						0



/*
 * ===========================================================================
 * ================================= Generic Macros ==========================
 * ===========================================================================
 */


#define NULL (void*)0



/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

/**================================================================
* @Fn				- MCAL_USART_Init
* @brief			- This is used to configure and initialize USART.
* @param [in] 		- config: This carries the configuration for USART.
* @retval 			- None.
* Note				- None.
*/
void MCAL_USART_Init(USART_Config_t *config)
{
	// Configure TX pin as output
	GPIO_PinConfig_t pin;
	
	pin.GPIO_PinNumber		= GPIO_PIN_1;
	pin.GPIO_PinMode		= GPIO_MODE_OUTPUT;
	MCAL_GPIO_Init(GPIOD, &pin);
	
	// Configure RX pin as Input
	pin.GPIO_PinNumber		= GPIO_PIN_0;
	pin.GPIO_PinMode		= GPIO_MODE_INPUT;
	MCAL_GPIO_Init(GPIOD, &pin);
	
	// Set Baud Rate.
	USART->_UBRRL					= config->USART_baudRate;
	CLEAR_BIT(USART->_UCSRC_UBRRH, _URSEL);									// this bit should be 0 when read or write UBRRH register
	WRITE_MASK(USART->_UCSRC_UBRRH, 0x0F, (config->USART_baudRate >> 8));
	
	// Set Character Size.
	SET_BIT(USART->_UCSRC_UBRRH, _URSEL);								// this bit should be 1 when read or write UCSRC register
	WRITE_MASK_POS(USART->_UCSRC_UBRRH, 0x3, _UCSZ0, config->USART_characterSize);
	WRITE_MASK_POS(USART->_UCSRB, 0x1, _UCSZ2, config->USART_characterSize >> 2);
	
	// Communication Mode.
	SET_BIT(USART->_UCSRC_UBRRH, _URSEL);								// this bit should be 1 when read or write UCSRC register
	WRITE_MASK_POS(USART->_UCSRC_UBRRH, 0x1, _UMSEL, config->USART_communicationMode >> 1);
	
	switch (config->USART_communicationMode)
	{
		case USART_MODE_ASYNC_NORMAL:
		CLEAR_BIT(USART->_UCSRA, _U2X);
		break;
		
		case USART_MODE_ASYNC_DOUBLE:
		SET_BIT(USART->_UCSRA, _U2X);
		break;
	}
	
	// Parity Mode.
	SET_BIT(USART->_UCSRC_UBRRH, _URSEL);								// this bit should be 1 when read or write UCSRC register
	WRITE_MASK_POS(USART->_UCSRC_UBRRH, 0x3, _UPM0, config->USART_parityMode);
	
	// Stop Bit.
	WRITE_MASK_POS(USART->_UCSRC_UBRRH, 0x1, _USBS, config->USART_stopBit);
	
	// Enable Interrupts.
	if (config->USART_INT_EN != USART_INT_DISABLE)
	{
		WRITE_MASK_POS(USART->_UCSRB, 0x7, _UDRIE, config->USART_INT_EN);
		
		Enable_Global_INT();
	}
	
	
	// Enable Tx & Rx.
	SET_BIT(USART->_UCSRB, _TXEN);
	SET_BIT(USART->_UCSRB, _RXEN);
}

/**================================================================
* @Fn				- MCAL_USART_sendData
* @brief			- This is used to send one byte over the USART.
* @param [in] 		- TxBuffer: This parameter carries the byte needed to be sent.
* @retval 			- None.
* Note				- None.
*/
void MCAL_USART_sendData(uint8_t TxBuffer)
{
	// check if UDRE register is still empty or not.
	while(!READ_BIT(USART->_UCSRA, _UDRE));
	
	USART->_UDR = TxBuffer;
}

/**================================================================
* @Fn				- MCAL_USART_sendString
* @brief			- This is used to send a string over the USART.
* @param [in] 		- strBuffer: a pointer to string.
* @retval 			- None.
* Note				- None.
*/
void MCAL_USART_sendString(uint8_t *strBuffer)
{
	while (*strBuffer != '\0')
	{
		MCAL_USART_sendData(*strBuffer++);
	}
}

/**================================================================
* @Fn				- MCAL_USART_sendInt32
* @brief			- This is used to send a 32-bit number over the USART.
* @param [in] 		- number32: the number.
* @retval 			- None.
* Note				- None.
*/
void MCAL_USART_sendInt32(uint32_t number32)
{
	do 
	{
		MCAL_USART_sendData(number32 & 0xFF);
		
	} while (number32 >>= 8);
}

/**================================================================
* @Fn				- MCAL_USART_receiveData
* @brief			- This is used to receive one byte over the USART.
* @param [in] 		- RxData: is a pointer to variable that carries the received byte.
* @retval 			- The error flag.
* Note				- None.
*/
void MCAL_USART_receiveData(uint8_t *RxData)
{
	// check if any byte is received or not.
	while (!READ_BIT(USART->_UCSRA, _RXC));
	
	*RxData = USART->_UDR;
}

/**================================================================
* @Fn				- MCAL_USART_receiveString
* @brief			- This is used to receive a string over the USART.
* @param [in] 		- strBuffer: is a pointer to variable that carries the received byte.
* @retval 			- The error flag.
* Note				- None.
*/
void MCAL_USART_receiveString(uint8_t *strBuffer)
{
	uint8_t chr;
	do 
	{
		MCAL_USART_receiveData(&chr);
		*strBuffer = chr;
	} 
	while(*strBuffer++ != '\0');
}


/**================================================================
* @Fn				- MCAL_USART_receiveString
* @brief			- This is used to receive a 32 bit number over the USART.
* @param [in] 		- number32: is a pointer to variable of 32 bit.
* @retval 			- The error flag.
* Note				- None.
*/
void MCAL_USART_receiveInt32(uint32_t *number32)
{
	uint8_t i = 0;
	uint32_t x;
	uint8_t *ptr = (uint8_t*)&x;
	do
	{
		MCAL_USART_receiveData(ptr + i);
	}
	while((++i) < 4);
	
	*number32 = x;
}

/*
 * =====================================================================================
 * ================================= ISR  ==============================================
 * =====================================================================================
 */

ISR(USART_RXC_vect)
{
	USART_RXComplete_IRQHandle();
}

ISR(USART_UDRE_vect)
{
	USART_DataRegisterEmpty_IRQHandle();
}

ISR(USART_TXC_vect)
{
	USART_TXComplete_IRQHandle();
}



/*
 * =====================================================================================
 * ================================= CALLBACK Functions ================================
 * =====================================================================================
 */

__attribute__ ((weak)) void USART_RXComplete_IRQHandle(void)
{
	
	while (1)
	{
	}
}

__attribute__ ((weak)) void USART_DataRegisterEmpty_IRQHandle(void)
{
	
	while (1)
	{
	}
}

__attribute__ ((weak)) void USART_TXComplete_IRQHandle(void)
{
	
	while(1)
	{
	}
}