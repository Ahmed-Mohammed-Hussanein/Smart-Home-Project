/*
 * SecuritySystem.c
 *
 * Created: 10/8/2023 5:37:20 PM
 *  Author: Ahmed
 */ 

#define F_CPU		1000000UL
#include <util/delay.h>
#include <string.h>

#include "keypad.h"
#include "UserInterface.h"
#include "SecuritySystem.h"

static uint8_t keys[] = KEYPAD_LAYOUT;
static uint8_t password[] = PassWord;

void SecuritySystem_Init(void)
{
	uint8_t i;
	uint8_t welMessage[] = "Welcome to Smart Home Project.";
	
	HAL_Keypad_Init();
	
	for (i = 0; i < 10; i++)
	{
		LCD_writeChar((uint8_t)welMessage[i]);
		_delay_ms(50);
	}
	
	LCD_autoScroll();
	for (i = 10; i < 30; i++)
	{
		LCD_writeChar((uint8_t)welMessage[i]);
		_delay_ms(50);
	}
	LCD_noAutoScroll();
	LCD_clear();
}

static uint8_t isCorrect(void)
{
	uint8_t key, i = 0, flag = 1;
	uint8_t passwordLength = strlen((const char *)password);
	
	LCD_setCursor( 0, 1);
	while(1)
	{
		key = HAL_Keypad_getKey((uint8_t (*)[])keys);
		if (key != '\0')
		{
			LCD_write((uint8_t*)"*");
			if (key != password[i])
			{
				flag = 0;
			}
			
			i++;
			if (i >= passwordLength)
			{
				break;
			}
		}
	}
	
	return flag;
}

void SecuritySystem_checkPassword(void)
{
	LCD_write((uint8_t*)"Enter Your Pass");
	while (1)
	{
		if (isCorrect())
		{
			LCD_clear();
			LCD_write((uint8_t*)"Correct!");
			_delay_ms(50);
			break;
		}
		else
		{
			LCD_clear();
			LCD_write((uint8_t*)"Wrong!Try Again.");
		}
		
	}
}