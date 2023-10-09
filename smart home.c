/*
 * smart_home.c
 *
 * Created: 10/6/2023 1:33:38 AM
 *  Author: Ahmed
 */ 

#define F_CPU	1000000UL

#include <util/delay.h>

#include "SS_pushButtons.h"
#include "SS_algorithm.h"
#include "SS_7segment.h"
#include "SS_buzzer.h"

#include "FF_alogrithm.h"
#include "FF_led1.h"
#include "UserInterface.h"

#include "ADC_Interface.h"
#include "LS_algorithm.h"
#include "LS_led2.h"

#include "CS_receiver.h"

#include "SecuritySystem.h"


int main(void)
{
	// Security System
	LCD_Init();
	SecuritySystem_Init();
	SecuritySystem_checkPassword();
	
	// Sound System
	SS_PB_Init();
	SS_Init();
	SEG_Init();
	Buzzer_Init();
	
	// Fire Alarm System
	ADC_Init();
	FF_Init();
	LED1_Init();
	
	// Lighting System
	LightSystem_Init();
	LS_LED2_Init();
	
	// Curtains System
	CS_Rx_Init();
		
    while(1)
    {
        //TODO:: Please write your application code 
		// Sound System
		p2SS_PB_state();
		p2SS_state();
		p2SEG_state();
		p2Buzzer_state();
		
		// Fire Alarm System
		p2FF_state();
		p2LED1_state();
		p2LCD_state();
		
		// Lighting System
		p2LightSystem_state();
		p2LS_LED2_state();
		
		// Curtains System
		p2CS_Rx_state();
		p2LCD_state();
    }
}

