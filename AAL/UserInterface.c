/*
 * UserInterface.c
 *
 * Created: 10/7/2023 4:07:25 PM
 *  Author: Ahmed
 */ 


#include "Platform_Types.h"

#include "LCD.h"

#include "UserInterface.h"

static sint8_t					lcd_newTempVal		= 0;
static sint8_t					lcd_oldTempVal		= 0;
static uint8_t					lcd_oldMotorStatus	= 'S';
static uint8_t					lcd_newMotorStatus	= 'S';
static uint8_t					lcd_flag			= 1;
LCD_controlConfig_t		lcd_config;

void (*p2LCD_state)(void);

e_LCD_StateId_t LCD_state;


void lcd_get_temp(sint8_t tempVal, uint8_t lcd_emergency)
{
	// state transition
	
	if (tempVal != lcd_oldTempVal)
	{
		lcd_newTempVal = tempVal;
		if (lcd_emergency == 1)
		{
			STATE(LCD_UpdateTemperature)();
		}
		else
		{
			p2LCD_state = STATE(LCD_UpdateTemperature);
		}
	}
}

void lcd_get_motorStatus(uint8_t motorStatus)
{
	// state transition
	
	if (motorStatus != lcd_oldMotorStatus)
	{
		lcd_newMotorStatus = motorStatus;
		
		p2LCD_state = STATE(LCD_UpdateMotorStatus);
	}
}

void LCD_Init(void)
{
	// state name
	LCD_state = LCD_Idle;

	// state init
	lcd_config.LCD_controlPort		= LCD_CTRL_PORT_C;
	lcd_config.LCD_RS_pin			= LCD_CTRL_PIN_2;
	lcd_config.LCD_EN_pin			= LCD_CTRL_PIN_3;
	HAL_LCD_Init(&lcd_config);
	
	//HAL_LCD_GoXY(&lcd_config, 0, 0);
	//HAL_LCD_writeString(&lcd_config, (uint8_t*)"Motor:Stopped.");

	// state transition
	p2LCD_state = STATE(LCD_Idle);
}


STATE_fn(LCD_Idle)
{
	// state name
	LCD_state = LCD_Idle;

	// state action
	

	// state transition
	p2LCD_state = STATE(LCD_Idle);
}

STATE_fn(LCD_UpdateTemperature)
{
	// state name
	LCD_state = LCD_UpdateTemperature;

	// state action
	if (lcd_newTempVal >= 60)
	{
		HAL_LCD_Clear(&lcd_config);
		HAL_LCD_writeString(&lcd_config, (uint8_t*)"System Stopped.");
		lcd_flag = 1;
	}
	else
	{
		if (lcd_flag == 1)
		{
			HAL_LCD_Clear(&lcd_config);
			HAL_LCD_writeString(&lcd_config, (uint8_t*)"Motor:");
			switch (lcd_newMotorStatus)
			{
				case 'F':
				HAL_LCD_writeString(&lcd_config, (uint8_t*)"Forward   ");
				break;
				
				case 'B':
				HAL_LCD_writeString(&lcd_config, (uint8_t*)"Backward  ");
				break;
				
				case 'S':
				HAL_LCD_writeString(&lcd_config, (uint8_t*)"Stopped   ");
				break;
			}
		}
		lcd_flag = 0;
	}
	HAL_LCD_GoXY(&lcd_config, 0, 1);
	HAL_LCD_writeString(&lcd_config, (uint8_t*)"Temperature:");
	HAL_LCD_writeInteger(&lcd_config, lcd_newTempVal);
	HAL_LCD_writeString(&lcd_config, (uint8_t*)"\xDF\x43");
	
	lcd_oldTempVal = lcd_newTempVal;

	// state transition
	p2LCD_state = STATE(LCD_Idle);
}

STATE_fn(LCD_UpdateMotorStatus)
{
	// state name
	LCD_state = LCD_UpdateMotorStatus;

	// state action
	HAL_LCD_GoXY(&lcd_config, 0, 0);
	HAL_LCD_writeString(&lcd_config, (uint8_t*)"Motor:");
	switch (lcd_newMotorStatus)
	{
		case 'F':
		HAL_LCD_writeString(&lcd_config, (uint8_t*)"Forward   ");
		break;
		
		case 'B':
		HAL_LCD_writeString(&lcd_config, (uint8_t*)"Backward  ");
		break;
		
		case 'S':
		HAL_LCD_writeString(&lcd_config, (uint8_t*)"Stopped   ");
		break;
	}
	
	lcd_oldMotorStatus = lcd_newMotorStatus;

	// state transition
	p2LCD_state = STATE(LCD_Idle);
}


void LCD_clear(void)
{
	HAL_LCD_Clear(&lcd_config);
}

void LCD_writeChar(uint8_t chr)
{
	HAL_LCD_writeChar(&lcd_config, chr);
}

void LCD_write(uint8_t *p2str)
{
	HAL_LCD_writeString(&lcd_config, p2str);
}

void LCD_setCursor(uint8_t x, uint8_t y)
{
	HAL_LCD_GoXY(&lcd_config, x, y);
}

void LCD_autoScroll(void)
{
	HAL_LCD_autoShiftLeft(&lcd_config);
}

void LCD_noAutoScroll(void)
{
	HAL_LCD_noAutoShiftLeft(&lcd_config);
}