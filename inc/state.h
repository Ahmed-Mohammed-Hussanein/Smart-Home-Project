/*
 * state.h
 *
 * Created: 10/6/2023 3:56:56 AM
 *  Author: Ahmed
 */ 


#ifndef STATE_H_
#define STATE_H_

#include "Platform_Types.h"

#define STATE_fn(STATE_NAME)	void STATE_NAME##_state(void)
#define STATE(STATE_NAME)			 STATE_NAME##_state


void SS_receive_PB_state(sint8_t state);
void SEG_getVal(sint8_t newValue);
void buzzer_turnOn(void);
void FF_setTempValue(sint8_t tVal);
void turn_led1_off(void);
void turn_led1_on(uint8_t led_emergency);
void lcd_get_temp(sint8_t tempVal, uint8_t lcd_emergency);

void LS_setResValue(sint8_t rVal);
void LS_LED2_setIntensity(uint8_t led_intensity);

void lcd_get_motorStatus(uint8_t motorStatus);



#endif /* STATE_H_ */