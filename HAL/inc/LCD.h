/*
 * LCD.h
 *
 * Created: 8/30/2023 6:22:50 PM
 *  Author: Ahmed
 */ 


#ifndef LCD_H_
#define LCD_H_

#define F_CPU	8000000UL

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "atmega32_GPIO_Driver.h"

#include <util/delay.h>

// ==========================================================
// ================== User Type Definitions =================
// ==========================================================

#define _4_BIT_DATA_LINE		0
#define _8_BIT_DATA_LINE		1

#define DATA_LINE				_4_BIT_DATA_LINE

typedef struct  
{
	GPIO_TypeDef	*LCD_controlPort;				/* This specifies the port contains the control pins of lcd.
														This parameter must be a value of @ref LCD_CTRL_PORT_define.
														*/
													
	uint8_t			LCD_RS_pin;						/* This specifies the control pin RS for LCD.
														This parameter must be a value of @ref LCD_CTRL_PIN_define.
														*/
	
	uint8_t			LCD_EN_pin;						/* This specifies the control pin EN for LCD.
														This parameter must be a value of @ref LCD_CTRL_PIN_define.
														*/
	
} LCD_controlConfig_t;


#define LCD_dataPort			LCD_DATA_PORT_C			// This specifies the port contains the control pins of lcd.
														//  This parameter must be a value of @ref LCD_DATA_PORT_define.


#define LCD_DB0_pin				LCD_DATA_DB_PIN_0			// This specifies the data pin DB0 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.
															
#define LCD_DB1_pin				LCD_DATA_DB_PIN_1			// This specifies the data pin DB1 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.

#define LCD_DB2_pin				LCD_DATA_DB_PIN_2			// This specifies the data pin DB2 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.

#define LCD_DB3_pin				LCD_DATA_DB_PIN_3			// This specifies the data pin DB3 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.

#define LCD_DB4_pin				LCD_DATA_DB_PIN_4			// This specifies the data pin DB4 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.

#define LCD_DB5_pin				LCD_DATA_DB_PIN_5			// This specifies the data pin DB5 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.

#define LCD_DB6_pin				LCD_DATA_DB_PIN_6			// This specifies the data pin DB6 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.

#define LCD_DB7_pin				LCD_DATA_DB_PIN_7			// This specifies the data pin DB7 for LCD.
															//  This parameter must be a value of @ref LCD_DATA_DB_PIN_define.
															

// ===================================================================
// ================== Macros Configuration Reference =================
// ===================================================================

// @ref LCD_CTRL_PORT_define.
#define LCD_CTRL_PORT_A									GPIOA
#define LCD_CTRL_PORT_B									GPIOB
#define LCD_CTRL_PORT_C									GPIOC
#define LCD_CTRL_PORT_D									GPIOD

// @ref LCD_CTRL_PIN_define.
#define LCD_CTRL_PIN_0									GPIO_PIN_0
#define LCD_CTRL_PIN_1									GPIO_PIN_1
#define LCD_CTRL_PIN_2									GPIO_PIN_2
#define LCD_CTRL_PIN_3									GPIO_PIN_3
#define LCD_CTRL_PIN_4									GPIO_PIN_4
#define LCD_CTRL_PIN_5									GPIO_PIN_5
#define LCD_CTRL_PIN_6									GPIO_PIN_6
#define LCD_CTRL_PIN_7									GPIO_PIN_7

// @ref LCD_DATA_PORT_define.
#define LCD_DATA_PORT_A									GPIOA
#define LCD_DATA_PORT_B									GPIOB
#define LCD_DATA_PORT_C									GPIOC
#define LCD_DATA_PORT_D									GPIOD

// @ref LCD_DATA_DB_PIN_define.
#define LCD_DATA_DB_PIN_0                              GPIO_PIN_0
#define LCD_DATA_DB_PIN_1                              GPIO_PIN_1
#define LCD_DATA_DB_PIN_2                              GPIO_PIN_2
#define LCD_DATA_DB_PIN_3                              GPIO_PIN_3
#define LCD_DATA_DB_PIN_4                              GPIO_PIN_4
#define LCD_DATA_DB_PIN_5                              GPIO_PIN_5
#define LCD_DATA_DB_PIN_6                              GPIO_PIN_6
#define LCD_DATA_DB_PIN_7                              GPIO_PIN_7


// ===================================================
// ================== APIs Functions =================
// ===================================================
void HAL_LCD_Init(LCD_controlConfig_t *config);

void HAL_LCD_Clear(LCD_controlConfig_t *config);
void HAL_LCD_Home(LCD_controlConfig_t *config);
void HAL_LCD_GoXY(LCD_controlConfig_t *config, uint8_t x, uint8_t y);

void HAL_LCD_writeChar(LCD_controlConfig_t *config, uint8_t singleChar);
void HAL_LCD_writeString(LCD_controlConfig_t *config, uint8_t *str);

void HAL_LCD_writeInteger(LCD_controlConfig_t *config, uint32_t intNumber);
void HAL_LCD_writeFloat(LCD_controlConfig_t *config, float64_t floatNumber);

void HAL_LCD_autoShiftLeft(LCD_controlConfig_t *config);
void HAL_LCD_noAutoShiftLeft(LCD_controlConfig_t *config);

void HAL_LCD_autoShiftRight(LCD_controlConfig_t *config);
void HAL_LCD_noAutoShiftRight(LCD_controlConfig_t *config);

void HAL_LCD_displayOn(LCD_controlConfig_t *config);
void HAL_LCD_displayOff(LCD_controlConfig_t *config);

void HAL_LCD_cursorOn(LCD_controlConfig_t *config);
void HAL_LCD_cursorOff(LCD_controlConfig_t *config);

void HAL_LCD_cursorBlinkOn(LCD_controlConfig_t *config);
void HAL_LCD_cursorBlinkOff(LCD_controlConfig_t *config);

void HAL_LCD_moveCursorLeft(LCD_controlConfig_t *config);
void HAL_LCD_moveCursorRight(LCD_controlConfig_t *config);

void HAL_LCD_moveDisplayLeft(LCD_controlConfig_t *config);
void HAL_LCD_moveDisplayRight(LCD_controlConfig_t *config);


void send(LCD_controlConfig_t *config, uint8_t _Byte, uint8_t rsState);


#endif /* LCD_H_ */