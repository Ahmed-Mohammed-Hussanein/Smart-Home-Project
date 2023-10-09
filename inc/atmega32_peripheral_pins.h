/*
 * atmega32_peripheral_pins.h
 *
 * Created: 9/27/2023 11:08:44 PM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_PERIPHERAL_PINS_H_
#define ATMEGA32_PERIPHERAL_PINS_H_

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* Timer 0 -*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define TIM0_PORT			GPIOB
#define TIM0_OC0_pin		GPIO_PIN_3
#define TIM0_T0_pin			GPIO_PIN_0


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* EXTI -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define EXTI0_PORT			GPIOD
#define EXTI0_PIN			GPIO_PIN_2

#define EXTI1_PORT			GPIOD
#define EXTI1_PIN			GPIO_PIN_3

#define EXTI2_PORT			GPIOB
#define EXTI2_PIN			GPIO_PIN_2


#endif /* ATMEGA32_PERIPHERAL_PINS_H_ */