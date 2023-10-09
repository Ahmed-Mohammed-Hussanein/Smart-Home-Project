/*
 * atmega32_GPIO_Driver.h
 *
 * Created: 9/18/2022 12:01:49 AM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_GPIO_DRIVER_H_
#define ATMEGA32_GPIO_DRIVER_H_

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "Utils.h"

#include "atmega32_device_header.h"


// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

typedef struct
{
	uint8_t GPIO_PinNumber;	 /* This specifies which pin in GPIO to be configured.
								This parameter must be a value of @ref GPIO_PIN_define.
								*/
							
	uint8_t GPIO_PinMode;	 /* This specifies what the mode of GPIO pin is.
								This parameter must be a value of @ref GPIO_MODE_define.
								*/
	
}	GPIO_PinConfig_t;


// ===================================================================
// ================== Macros Configuration Reference =================
// =================================================================== 

// @ref GPIO_PIN_define
// GPIO_MASK_CONFIG is used to configure more than one pin at the same time but must be at the same port.
// You can write your configuration as following:
// 0b PIN7 PIN6 PIN5 PIN4 PIN3 PIN2 PIN1 PIN0
//#define GPIOA_MASK_GONFIG	(uint8_t_t) (0b11111111)
#define GPIO_PIN_0			(uint8_t) (0x01)
#define GPIO_PIN_1			(uint8_t) (0x02)
#define GPIO_PIN_2			(uint8_t) (0x04)
#define GPIO_PIN_3			(uint8_t) (0x08)
#define GPIO_PIN_4			(uint8_t) (0x10)
#define GPIO_PIN_5			(uint8_t) (0x20)
#define GPIO_PIN_6			(uint8_t) (0x40)
#define GPIO_PIN_7			(uint8_t) (0x80)
#define GPIO_ALL_PINS		(uint8_t) (0xFF)

// @ref GPIO_MODE_define
#define GPIO_MODE_INPUT			   0
#define GPIO_MODE_OUTPUT		   1
#define GPIO_MODE_INPUT_PUR		   2

/* This specifies the output and input states */
// @ref GPIO_STATE_define
#define GPIO_STATE_LOW				0
#define GPIO_STATE_HIGH				1

// ===================================================
// ================== APIs Functions =================
// =================================================== 
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t *PinConfig);

void MCAL_GPIO_writePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t value);
void MCAL_GPIO_writePins(GPIO_TypeDef *GPIOx, uint8_t PinNumber, uint8_t value);
void MCAL_GPIO_writePort(GPIO_TypeDef *GPIOx, uint8_t value);

uint8_t MCAL_GPIO_readPin(GPIO_TypeDef *GPIOx, uint8_t PinNumber);
uint8_t MCAL_GPIO_readPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_togglePin(GPIO_TypeDef *GPIOx, uint8_t PinNumber);
void MCAL_GPIO_togglePort(GPIO_TypeDef *GPIOx);


#endif /* ATMEGA32_GPIO_DRIVER_H_ */