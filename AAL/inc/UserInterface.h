/*
 * UserInterface.h
 *
 * Created: 10/7/2023 4:07:08 PM
 *  Author: Ahmed
 */ 


#ifndef USERINTERFACE_H_
#define USERINTERFACE_H_

#include "state.h"

typedef enum
{
	LCD_Idle,
	LCD_UpdateTemperature,
	LCD_UpdateMotorStatus
	
} e_LCD_StateId_t;


extern void (*p2LCD_state)(void);


void LCD_Init(void);
void LCD_clear(void);
void LCD_writeChar(uint8_t chr);
void LCD_write(uint8_t *p2str);
void LCD_setCursor(uint8_t x, uint8_t y);
void LCD_autoScroll(void);
void LCD_noAutoScroll(void);
STATE_fn(LCD_Idle);
STATE_fn(LCD_UpdateTemperature);
STATE_fn(LCD_UpdateMotorStatus);



#endif /* USERINTERFACE_H_ */