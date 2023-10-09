/*
 * CS_receiver.c
 *
 * Created: 10/8/2023 12:42:38 AM
 *  Author: Ahmed
 */ 


#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"
#include "atmega32_USART_Driver.h"

#include "CS_receiver.h"

static uint8_t					CS_Rx_chr = 0;

void (*p2CS_Rx_state)(void);

e_CS_Rx_StateId_t CS_Rx_state;

void CS_Rx_Init(void)
{
	// state name
	CS_Rx_state = CS_Rx_Idle;

	// state init
	GPIO_PinConfig_t motor_pins = {GPIO_PIN_4 | GPIO_PIN_5, GPIO_MODE_OUTPUT};
	MCAL_GPIO_Init(GPIOD, &motor_pins);
	
	USART_Config_t uart_init = {12, USART_CHARSIZE_8, USART_PLORITY_FALLING, USART_MODE_ASYNC_DOUBLE, 
		USART_PARITYMODE_DISABLE, USART_STOPBIT_1, USART_INT_RXC_ENABLE};
	
	MCAL_USART_Init(&uart_init);

	// state transition
	p2CS_Rx_state = STATE(CS_Rx_Idle);
}


STATE_fn(CS_Rx_Idle)
{
	// state name
	CS_Rx_state = CS_Rx_Idle;

	// state action
	

	// state transition
	p2CS_Rx_state = STATE(CS_Rx_Idle);
}

STATE_fn(CS_Rx_Check)
{
	// state name
	CS_Rx_state = CS_Rx_Check;

	// state action
	lcd_get_motorStatus(CS_Rx_chr);
	

	// state transition
	switch (CS_Rx_chr)
	{
		case 'F':
		p2CS_Rx_state = STATE(CS_Rx_Forwarding);
		break;
		
		case 'B':
		p2CS_Rx_state = STATE(CS_Rx_Backwarding);
		break;
		
		case 'S':
		p2CS_Rx_state = STATE(CS_Rx_Stopped);
		break;
	}
}

STATE_fn(CS_Rx_Forwarding)
{
	// state name
	CS_Rx_state = CS_Rx_Forwarding;

	// state action
	MCAL_GPIO_writePins(GPIOD, GPIO_PIN_4 | GPIO_PIN_5, (1<<4));

	// state transition
	p2CS_Rx_state = STATE(CS_Rx_Idle);
}

STATE_fn(CS_Rx_Backwarding)
{
	// state name
	CS_Rx_state = CS_Rx_Backwarding;

	// state action
	MCAL_GPIO_writePins(GPIOD, GPIO_PIN_4 | GPIO_PIN_5, (1<<5));

	// state transition
	p2CS_Rx_state = STATE(CS_Rx_Idle);
}

STATE_fn(CS_Rx_Stopped)
{
	// state name
	CS_Rx_state = CS_Rx_Backwarding;

	// state action
	MCAL_GPIO_writePins(GPIOD, GPIO_PIN_4 | GPIO_PIN_5, 0x0);

	// state transition
	p2CS_Rx_state = STATE(CS_Rx_Idle);
}

void USART_RXComplete_IRQHandle(void)
{
	MCAL_USART_receiveData(&CS_Rx_chr);
	MCAL_USART_sendData(CS_Rx_chr);
	p2CS_Rx_state = STATE(CS_Rx_Check);
}