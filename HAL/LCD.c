/*
 * LCD.c
 *
 * Created: 8/30/2023 6:22:34 PM
 *  Author: Ahmed
 */ 


// =============================================
// ================== Includes =================
// =============================================

#include "Utils.h"
#include "Platform_Types.h"

#include "atmega32_GPIO_Driver.h"
#include "LCD.h"

#include <stdio.h>

/*
 * ===========================================================================
 * ================================= Generic Macros ==========================
 * ===========================================================================
 */

#define EN_DELAY_us							2
	
#define clear								0x1
#define home								0x2

/** entery mode **/
#define S_BIT								0
#define I_D_BIT								1
#define NO_SHIFT_DEC						0xFC
#define NO_SHIFT_INC						0x2
#define SHIFT_LEFT							0x3
#define SHIFT_RIGHT							0x1

/** display on/off **/
#define D_BIT								2
#define DISPLAY_ON							0x0c
#define DISPLAY_OFF							0x0B

#define C_BIT								1
#define CURSOR_ON							0x0A
#define CURSOR_OFF							0x0D

#define B_BIT								0
#define BLINK_ON							0x09
#define BLINK_OFF							0x0E

/** Cursor or Display Shift **/
#define R_L_BIT								2
#define S_C_BIT								3

#define MOVE_CURSOR_LEFT					0x0
#define MOVE_CURSOR_RIGHT					0x1

#define MOVE_DISPLAY_LEFT					0x2
#define MOVE_DISPLAY_RIGHT					0x3


/** Function Set **/
#define _4BIT		0x20
#define _8BIT		0x30

#define _2LINE		0x28
#define _1LINE		0x20

#define _5x10DOTS	0x24
#define _5x8DOTS	0x20

/** DDRAM address **/
#define DDRAM_COMMAND					0x80
#define FIRST_LINE_ADDRESS				0x00
#define SECOND_LINE_ADDRESS				0x40


#define COMMAND							GPIO_STATE_LOW
#define DATA							GPIO_STATE_HIGH

/*
 * ==============================================================================
 * ================================= Generic Variables ==========================
 * ==============================================================================
 */

static uint8_t EntryModeSet			= NO_SHIFT_INC | 0x4;
static uint8_t DisplayControl		= (DISPLAY_ON | CURSOR_ON) & BLINK_OFF;
static uint8_t CursorDisplayShift	= (MOVE_CURSOR_RIGHT << R_L_BIT) | 0x10;

#if (DATA_LINE == _8_BIT_DATA_LINE)

static uint8_t FunctionSet			= _8BIT | _2LINE | _5x8DOTS;

#elif (DATA_LINE == _4_BIT_DATA_LINE)

static uint8_t FunctionSet			= _4BIT | _2LINE | _5x8DOTS;

#endif


/*
 * ========================================================================================
 * ================================= Generic Function Definition ==========================
 * ========================================================================================
 */

static void pulseEnable(LCD_controlConfig_t *config)
{
	MCAL_GPIO_writePin(config->LCD_controlPort, config->LCD_EN_pin, GPIO_STATE_HIGH);
	_delay_us(EN_DELAY_us);
	MCAL_GPIO_writePin(config->LCD_controlPort, config->LCD_EN_pin, GPIO_STATE_LOW);
}

void send(LCD_controlConfig_t *config, uint8_t _Byte, uint8_t rsState)
{
	//while(readBusyFlag(config) == 1);
	
	MCAL_GPIO_writePin(config->LCD_controlPort, config->LCD_RS_pin, rsState);
	
	#if (DATA_LINE == _8_BIT_DATA_LINE)
	
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB0_pin, READ_BIT(_Byte, 0));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB1_pin, READ_BIT(_Byte, 1));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB2_pin, READ_BIT(_Byte, 2));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB3_pin, READ_BIT(_Byte, 3));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB4_pin, READ_BIT(_Byte, 4));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB5_pin, READ_BIT(_Byte, 5));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB6_pin, READ_BIT(_Byte, 6));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB7_pin, READ_BIT(_Byte, 7));
	
	pulseEnable(config);
	
	#elif (DATA_LINE == _4_BIT_DATA_LINE)
	
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB4_pin, READ_BIT(_Byte, 4));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB5_pin, READ_BIT(_Byte, 5));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB6_pin, READ_BIT(_Byte, 6));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB7_pin, READ_BIT(_Byte, 7));
	
	pulseEnable(config);
	
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB4_pin, READ_BIT(_Byte, 0));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB5_pin, READ_BIT(_Byte, 1));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB6_pin, READ_BIT(_Byte, 2));
	MCAL_GPIO_writePin(LCD_dataPort, LCD_DB7_pin, READ_BIT(_Byte, 3));
	
	pulseEnable(config);

	#endif
	
	_delay_ms(2);
}


/*
 * =====================================================================================
 * ================================= APIs Function Definition ==========================
 * =====================================================================================
 */

void HAL_LCD_Init(LCD_controlConfig_t *config)
{
	GPIO_PinConfig_t pin;
	pin.GPIO_PinMode		= GPIO_MODE_OUTPUT;
	
	pin.GPIO_PinNumber		= config->LCD_EN_pin | config->LCD_RS_pin;
	MCAL_GPIO_Init(config->LCD_controlPort, &pin);
	
	pin.GPIO_PinNumber		= LCD_DB4_pin | LCD_DB5_pin | LCD_DB6_pin | LCD_DB7_pin;
	MCAL_GPIO_Init(LCD_dataPort, &pin);
	
	#if (DATA_LINE == _8_BIT_DATA_LINE)
	
	pin.GPIO_PinNumber		= LCD_DB0_pin | LCD_DB1_pin | LCD_DB2_pin | LCD_DB3_pin;
	MCAL_GPIO_Init(LCD_dataPort, &pin);
	
	#elif (DATA_LINE == _4_BIT_DATA_LINE)
	
	send(config, FunctionSet >> 4, COMMAND);

	#endif
	
	send(config, FunctionSet, COMMAND);
	send(config, EntryModeSet, COMMAND);
	send(config, DisplayControl, COMMAND);
	send(config, CursorDisplayShift, COMMAND);
	send(config, clear, COMMAND);
}


void HAL_LCD_Clear(LCD_controlConfig_t *config)
{
	send(config, clear, COMMAND);
}

void HAL_LCD_Home(LCD_controlConfig_t *config)
{
	send(config, home, COMMAND);
}

void HAL_LCD_GoXY(LCD_controlConfig_t *config, uint8_t x, uint8_t y)
{
	if (y == 0)
	{
		if (x >= 0 && x < 16)
		{
			send(config, (DDRAM_COMMAND | FIRST_LINE_ADDRESS ) + x, COMMAND);
		}
	}
	else if(y == 1)
	{
		if (x >= 0 && x < 16)
		{
			send(config, (DDRAM_COMMAND | SECOND_LINE_ADDRESS ) + x, COMMAND);
		}
	}
}

void HAL_LCD_writeChar(LCD_controlConfig_t *config, uint8_t singleChar)
{
	send(config, singleChar, DATA);
}

void HAL_LCD_writeString(LCD_controlConfig_t *config, uint8_t *str)
{
	while (*str != '\0')
	{
		send(config, *str++, DATA);
	}
}

void HAL_LCD_writeInteger(LCD_controlConfig_t *config, uint32_t intNumber)
{
	uint8_t temp[16];
	
	sprintf((char*)temp, "%lu", intNumber);
	
	HAL_LCD_writeString(config, temp);
}

void HAL_LCD_writeFloat(LCD_controlConfig_t *config, float64_t floatNumber)
{
	uint8_t temp[16];
	
	uint32_t tempInt;
	uint32_t tempFraction;
	
	uint8_t *tempSign = floatNumber < 0 ? (uint8_t*)"-" : (uint8_t*)"";
	
	floatNumber		= floatNumber < 0 ? -floatNumber : floatNumber;
	tempInt			= (uint32_t)floatNumber;
	tempFraction	= (floatNumber - tempInt) * 1000;
	
	sprintf((char*)temp, "%s%lu.%lu", (char*)tempSign, tempInt, tempFraction);
	
	HAL_LCD_writeString(config, temp);
}

void HAL_LCD_autoShiftLeft(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(EntryModeSet, 0x3, S_BIT, SHIFT_LEFT);
	send(config, EntryModeSet, COMMAND);
}

void HAL_LCD_noAutoShiftLeft(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(EntryModeSet, 0x3, S_BIT, NO_SHIFT_INC);
	send(config, EntryModeSet, COMMAND);
}

void HAL_LCD_autoShiftRight(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(EntryModeSet, 0x3, S_BIT, SHIFT_RIGHT);
	send(config, EntryModeSet, COMMAND);
}

void HAL_LCD_noAutoShiftRight(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(EntryModeSet, 0x3, S_BIT, NO_SHIFT_INC);
	send(config, EntryModeSet, COMMAND);
}

void HAL_LCD_displayOn(LCD_controlConfig_t *config)
{
	SET_BIT(DisplayControl, D_BIT);
	send(config, DisplayControl, COMMAND);
}

void HAL_LCD_displayOff(LCD_controlConfig_t *config)
{
	CLEAR_BIT(DisplayControl, D_BIT);
	send(config, DisplayControl, COMMAND);
}

void HAL_LCD_cursorOn(LCD_controlConfig_t *config)
{
	SET_BIT(DisplayControl, C_BIT);
	send(config, DisplayControl, COMMAND);
}

void HAL_LCD_cursorOff(LCD_controlConfig_t *config)
{
	CLEAR_BIT(DisplayControl, C_BIT);
	send(config, DisplayControl, COMMAND);
}

void HAL_LCD_cursorBlinkOn(LCD_controlConfig_t *config)
{
	SET_BIT(DisplayControl, B_BIT);
	send(config, DisplayControl, COMMAND);
}

void HAL_LCD_cursorBlinkOff(LCD_controlConfig_t *config)
{
	CLEAR_BIT(DisplayControl, B_BIT);
	send(config, DisplayControl, COMMAND);
}

void HAL_LCD_moveCursorLeft(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(CursorDisplayShift, 0x3, R_L_BIT, MOVE_CURSOR_LEFT);
	send(config, CursorDisplayShift, COMMAND);
}

void HAL_LCD_moveCursorRight(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(CursorDisplayShift, 0x3, R_L_BIT, MOVE_CURSOR_RIGHT);
	send(config, CursorDisplayShift, COMMAND);
}

void HAL_LCD_moveDisplayLeft(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(CursorDisplayShift, 0x3, R_L_BIT, MOVE_DISPLAY_LEFT);
	send(config, CursorDisplayShift, COMMAND);	
}

void HAL_LCD_moveDisplayRight(LCD_controlConfig_t *config)
{
	WRITE_MASK_POS(CursorDisplayShift, 0x3, R_L_BIT, MOVE_DISPLAY_RIGHT);
	send(config, CursorDisplayShift, COMMAND);
}