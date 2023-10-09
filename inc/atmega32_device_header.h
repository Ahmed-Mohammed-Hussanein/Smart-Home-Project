/*
 * MemMap.h
 *
 * Created: 9/5/2022 7:16:37 PM
 *  Author: Ahmed
 */ 


#ifndef ATMEGA32_DEVICE_HEADER_H_
#define ATMEGA32_DEVICE_HEADER_H_

// =============================================
// ================== Includes =================
// =============================================

#include "Platform_Types.h"
#include "Utils.h"


// ==========================================================
// ================== Memory Base Addresses =================
// ==========================================================

#define FLUSH_BASE		0x0
#define SRAM_BASE		0x60


// ==============================================================
// ================== General Registers Address =================
// ==============================================================
#define SFIOR_BASE		0x50
#define MCUR_BASE		0x54
#define INT_BASE		0x58

// ==============================================================
// ================== Peripheral Base Addresses =================
// ==============================================================

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* GPIO -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define GPIOA_BASE		0x39
#define GPIOB_BASE		0x36
#define GPIOC_BASE		0x33
#define GPIOD_BASE		0x30


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* USART -*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define USART_BASE		0x29


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* SPI -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define SPI_BASE		0x2D


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* I2C -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define I2C_BASE		0x20


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* TIM0 -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define TIM0_BASE		0x52


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* ADC -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define ADC_BASE		0x24


// =========================================================
// ================== Peripheral Registers =================
// =========================================================

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* Interrupt Registers -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
	vuint8_t _TIFR;
	vuint8_t _TIMSK;
	vuint8_t _GIFR;
	vuint8_t _GICR;
	
} INT_TypeDef;

typedef struct
{
	vuint8_t _MCUCSR;
	vuint8_t _MCUCR;
	
} MCUR_TypeDef;

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* GPIO -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
	vuint8_t PIN;
	vuint8_t DDR;
	vuint8_t PORT;
	
} GPIO_TypeDef;

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* UsART -*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
	vuint8_t _UBRRL;
	vuint8_t _UCSRB;
	vuint8_t _UCSRA;
	vuint8_t _UDR;
	vuint8_t _reserved[19];
	vuint8_t _UCSRC_UBRRH;
	
} USART_TypeDef;


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* SPI -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
	vuint8_t _SPCR;
	vuint8_t _SPSR;
	vuint8_t _SPDR;
	
} SPI_TypeDef;

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* I2C -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
	vuint8_t _TWBR;
	vuint8_t _TWSR;
	vuint8_t _TWAR;
	vuint8_t _TWDR;
	vuint8_t _reserved[50];
	vuint8_t _TWCR;
	
} I2C_TypeDef;


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* TIM0 -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
	vuint8_t _TCNT0;
	vuint8_t _TCCR0;
	vuint8_t _reserved[8];
	vuint8_t _OCR0;
	
} TIM0_TypeDef;


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* ADC -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-

typedef struct
{
	vuint8_t _ADCL;
	vuint8_t _ADCH;
	vuint8_t _ADCSRA;
	vuint8_t _ADMUX;
	
} ADC_TypeDef;

// =========================================================
// ================== Peripheral Instances =================
// =========================================================

#define _SFIOR				((vuint8_t*)SFIOR_BASE)

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* GPIO -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-

#define GPIOA				 ((GPIO_TypeDef*)GPIOA_BASE)
#define GPIOB				 ((GPIO_TypeDef*)GPIOB_BASE)
#define GPIOC				 ((GPIO_TypeDef*)GPIOC_BASE)
#define GPIOD				 ((GPIO_TypeDef*)GPIOD_BASE)


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* USART -*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define USART				 ((USART_TypeDef*)USART_BASE)


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* SPI -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define SPI				 ((SPI_TypeDef*)SPI_BASE)

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* I2C -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define I2C				 ((I2C_TypeDef*)I2C_BASE)

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* TIM0 -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define TIM0			 ((TIM0_TypeDef*)TIM0_BASE)


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* ADC -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-
#define _ADC				 ((ADC_TypeDef*)ADC_BASE)


// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* Interrupt Registers -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
#define INT				((INT_TypeDef*)INT_BASE)
#define MCUR			((MCUR_TypeDef*)MCUR_BASE)

#define Enable_Global_INT()		sei()
#define Disable_Global_INT()	cli()

#endif /* MEMMAP_H_ */