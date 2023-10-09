/*
 * BitField.h
 *
 * Created: 9/23/2023 6:37:14 PM
 *  Author: Ahmed
 */ 


#ifndef BITFIELD_H_
#define BITFIELD_H_

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* GENERAL REGISTER -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

/*******************  Bit definition for SFIOR register  ********************/
#define SFIOR_PUD_Pos							(2)
#define SFIOR_PUD_Mask							(0x1 << SFIOR_PUD_Pos)			/*!< 0x04 */
#define SFIOR_PUD								(SFIOR_PUD_Mask)				/*!< Pull-up Disable >*/

#define SFIOR_ACME_Pos							(3)
#define SFIOR_ACME_Mask							(0x1 << SFIOR_ACME_Pos)			/*!< 0x08 */
#define SFIOR_ACME								(SFIOR_ACME_Mask)

#define SFIOR_ADTSn_Pos							(5)
#define SFIOR_ADTSn_Mask						(0x7 << SFIOR_ADTSn_Pos)		/*!< 0xE0 */
#define SFIOR_ADTSn								(SFIOR_ADTSn_Mask)				/*!< ADC Auto Trigger Source [n = 2:0] >*/

/*******************  Bit definition for MCUCR register  ********************/
#define MCUCR_ISC0n_Pos							(0)
#define MCUCR_ISC0n_Mask						(0x3 << MCUCR_ISC0n_Pos)		/*!< 0x03 */
#define MCUCR_ISC0n								(MCUCR_ISC0n_Mask)				/*!< Interrupt Sense Control 1 Bit 1 and Bit 0 [n = 1:0] >*/

#define MCUCR_ISC1n_Pos							(2)
#define MCUCR_ISC1n_Mask						(0x3 << MCUCR_ISC1n_Pos)		/*!< 0x0C */
#define MCUCR_ISC1n								(MCUCR_ISC1n_Mask)				/*!< Interrupt Sense Control 0 Bit 1 and Bit 0 [n = 1:0] >*/

/*******************  Bit definition for MCUCSR register  ********************/
#define MCUCSR_ISC2_Pos							(6)
#define MCUCSR_ISC2_Mask						(0x1 << MCUCSR_ISC2_Pos)		/*!< 0x40 */
#define MCUCSR_ISC2								(MCUCSR_ISC2_Mask)				/*!< Interrupt Sense Control 2 >*/


// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* I2C -*-*-*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-

/*******************  Bit definition for I2C_TWCR register  ********************/
#define I2C_TWCR_TWIE_Pos						(0)
#define I2C_TWCR_TWIE_Mask						(0x1 << I2C_TWCR_TWIE_Pos)		/*!< 0x01 */
#define I2C_TWCR_TWIE							(I2C_TWCR_TWIE_Mask)			/*!< TWI Interrupt Enable */

#define I2C_TWCR_TWEN_Pos						(2)
#define I2C_TWCR_TWEN_Mask						(0x1 << I2C_TWCR_TWEN_Pos)		/*!< 0x04 */
#define I2C_TWCR_TWEN							(I2C_TWCR_TWEN_Mask)			/*!< TWI Enable */

#define I2C_TWCR_TWWC_Pos						(3)
#define I2C_TWCR_TWWC_Mask						(0x1 << I2C_TWCR_TWWC_Pos)		/*!< 0x08 */
#define I2C_TWCR_TWWC							(I2C_TWCR_TWWC_Mask)			/*!< TWI Write Collision Flag */

#define I2C_TWCR_TWSTO_Pos						(4)
#define I2C_TWCR_TWSTO_Mask						(0x1 << I2C_TWCR_TWSTO_Pos)		/*!< 0x10 */
#define I2C_TWCR_TWSTO							(I2C_TWCR_TWSTO_Mask)			/*!< TWI STOP Condition */

#define I2C_TWCR_TWSTA_Pos						(5)
#define I2C_TWCR_TWSTA_Mask						(0x1 << I2C_TWCR_TWSTA_Pos)		/*!< 0x20 */
#define I2C_TWCR_TWSTA							(I2C_TWCR_TWSTA_Mask)			/*!< TWI START Condition */

#define I2C_TWCR_TWEA_Pos						(6)
#define I2C_TWCR_TWEA_Mask						(0x1 << I2C_TWCR_TWEA_Pos)		/*!< 0x40 */
#define I2C_TWCR_TWEA							(I2C_TWCR_TWEA_Mask)			/*!< TWI Enable Acknowledge */

#define I2C_TWCR_TWINT_Pos						(7)
#define I2C_TWCR_TWINT_Mask						(0x1 << I2C_TWCR_TWINT_Pos)		/*!< 0x80 */
#define I2C_TWCR_TWINT							(I2C_TWCR_TWINT_Mask)			/*!< TWI Interrupt Flag */

/*******************  Bit definition for I2C_TWSR register  ********************/
#define I2C_TWSR_TWPSn_Pos						(0)
#define I2C_TWSR_TWPSn_Mask						(0x3 << I2C_TWSR_TWPSn_Pos)		/*!< 0x03 */
#define I2C_TWSR_TWPSn							(I2C_TWSR_TWPSn_Mask)			/*!< TWI Prescaler [n = 1:0] */

#define I2C_TWSR_TWSn_Pos						(3)
#define I2C_TWSR_TWSn_Mask						(0x1F << I2C_TWSR_TWSn_Pos)		/*!< 0xF8 */
#define I2C_TWSR_TWSn							(I2C_TWSR_TWSn_Mask)			/*!< TWI Status Bit 7 [n = 7:3] */

/*******************  Bit definition for I2C_TWAR register  ********************/
#define I2C_TWAR_TWGCE_Pos						(0)
#define I2C_TWAR_TWGCE_Mask						(0x1 << I2C_TWAR_TWGCE_Pos)		/*!< 0x01 */
#define I2C_TWAR_TWGCE							(I2C_TWAR_TWGCE_Mask)			/*!< TWI General Call Recognition Enable Bit */

#define I2C_TWAR_TWAn_Pos						(1)
#define I2C_TWAR_TWAn_Mask						(0x3F << I2C_TWAR_TWAn_Pos)		/*!< 0xFE */
#define I2C_TWAR_TWAn							(I2C_TWAR_TWAn_Mask)			/*!< TWI (Slave) Address [n = 6:0] */

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* Timer 0 -*-*-*-
// *-*-*-*-*-*-*-*-*-*-*-*-*-

/*******************  Bit definition for TIM0_TCCR0 register  ********************/
#define TIM0_TCCR0_CS0n_Pos						(0)
#define TIM0_TCCR0_CS0n_Mask					(0x7 << TIM0_TCCR0_CS0n_Pos)	/*!< 0x7 */
#define TIM0_TCCR0_CS0n							(TIM0_TCCR0_CS0n_Mask)			/*!< Clock Select [n = 2:0] */

#define TIM0_TCCR0_WGM01_Pos					(3)
#define TIM0_TCCR0_WGM01_Mask					(0x1 << TIM0_TCCR0_WGM01_Pos)	/*!< 0x8 */
#define TIM0_TCCR0_WGM01						(TIM0_TCCR0_WGM01_Mask)			/*!< Waveform Generation Mode */

#define TIM0_TCCR0_COM0n_Pos					(4)
#define TIM0_TCCR0_COM0n_Mask					(0x3 << TIM0_TCCR0_COM0n_Pos)	/*!< 0x30 */
#define TIM0_TCCR0_COM0n						(TIM0_TCCR0_COM0n_Mask)			/*!< Compare Match Output Mode [n = 1:0] */

#define TIM0_TCCR0_WGM00_Pos					(6)
#define TIM0_TCCR0_WGM00_Mask					(0x1 << TIM0_TCCR0_WGM00_Pos)	/*!< 0x40 */
#define TIM0_TCCR0_WGM00						(TIM0_TCCR0_WGM00_Mask)			/*!< Waveform Generation Mode */

#define TIM0_TCCR0_FOC0_Pos						(7)
#define TIM0_TCCR0_FOC0_Mask					(0x1 << TIM0_TCCR0_FOC0_Pos)	/*!< 0x80 */
#define TIM0_TCCR0_FOC0							(TIM0_TCCR0_FOC0_Mask)			/*!< Force Output Compare */

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* Interrupt Registers -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

/*******************  Bit definition for GICR register  ********************/
#define GICR_IVCE_Pos							(0)
#define GICR_IVCE_Mask							(0x1 << GICR_IVCE_Pos)			/*!< 0x01 */
#define GICR_IVCE								(GICR_IVCE_Mask)				/*!< Interrupt Vector Change Enable */

#define GICR_IVSEL_Pos							(1)
#define GICR_IVSEL_Mask							(0x1 << GICR_IVSEL_Pos)			/*!< 0x02 */
#define GICR_IVSEL								(GICR_IVSEL_Mask)				/*!< Interrupt Vector Select */

#define GICR_INT2_Pos							(5)
#define GICR_INT2_Mask							(0x1 << GICR_INT2_Pos)			/*!< 0x20 */
#define GICR_INT2								(GICR_INT2_Mask)				/*!< External Interrupt Request 2 Enable */

#define GICR_INT0_Pos							(6)
#define GICR_INT0_Mask							(0x1 << GICR_INT0_Pos)			/*!< 0x40 */
#define GICR_INT0								(GICR_INT0_Mask)				/*!< External Interrupt Request 0 Enable */

#define GICR_INT1_Pos							(7)
#define GICR_INT1_Mask							(0x1 << GICR_INT1_Pos)			/*!< 0x80 */
#define GICR_INT1								(GICR_INT1_Mask)				/*!< External Interrupt Request 1 Enable */

/*******************  Bit definition for GIFR register  ********************/
#define GIFR_INTF2_Pos							(5)
#define GIFR_INTF2_Mask							(0x1 << GIFR_INTF2_Pos)			/*!< 0x20 */
#define GIFR_INTF2								(GIFR_INTF2_Mask)				/*!< External Interrupt Flag 2 */

#define GIFR_INTF0_Pos							(6)
#define GIFR_INTF0_Mask							(0x1 << GIFR_INTF0_Pos)			/*!< 0x40 */
#define GIFR_INTF0								(GIFR_INTF0_Mask)				/*!< External Interrupt Flag 0 */

#define GIFR_INTF1_Pos							(7)
#define GIFR_INTF1_Mask							(0x1 << GIFR_INTF1_Pos)			/*!< 0x80 */
#define GIFR_INTF1								(GIFR_INTF1_Mask)				/*!< External Interrupt Flag 1 */

/*******************  Bit definition for TIMSK register  ********************/
#define TIMSK_TOIE0_Pos							(0)
#define TIMSK_TOIE0_Mask						(0x1 << TIMSK_TOIE0_Pos)		/*!< 0x01 */
#define TIMSK_TOIE0								(TIMSK_TOIE0_Mask)				/*!< Timer/Counter0 Overflow Interrupt Enable */

#define TIMSK_OCIE0_Pos							(1)
#define TIMSK_OCIE0_Mask						(0x1 << TIMSK_OCIE0_Pos)		/*!< 0x02 */
#define TIMSK_OCIE0								(TIMSK_OCIE0_Mask)				/*!< Timer/Counter0 Output Compare Match Interrupt Enable */

#define TIMSK_TOIE1_Pos							(2)
#define TIMSK_TOIE1_Mask						(0x1 << TIMSK_TOIE1_Pos)		/*!< 0x04 */
#define TIMSK_TOIE1								(TIMSK_TOIE1_Mask)				/*!< Timer/Counter1, Overflow Interrupt Enable */

#define TIMSK_OCIE1B_Pos						(3)
#define TIMSK_OCIE1B_Mask						(0x1 << TIMSK_OCIE1B_Pos)		/*!< 0x08 */
#define TIMSK_OCIE1B							(TIMSK_OCIE1B_Mask)				/*!< Timer/Counter1, Output Compare B Match Interrupt Enable */

#define TIMSK_OCIE1A_Pos						(4)
#define TIMSK_OCIE1A_Mask						(0x1 << TIMSK_OCIE1A_Pos)		/*!< 0x10 */
#define TIMSK_OCIE1A							(TIMSK_OCIE1A_Mask)				/*!< Timer/Counter1, Output Compare A Match Interrupt Enable */

#define TIMSK_TICIE1_Pos						(5)
#define TIMSK_TICIE1_Mask						(0x1 << TIMSK_TICIE1_Pos)		/*!< 0x20 */
#define TIMSK_TICIE1							(TIMSK_TICIE1_Mask)				/*!< Timer/Counter1, Input Capture Interrupt Enable */

#define TIMSK_TOIE2_Pos							(6)
#define TIMSK_TOIE2_Mask						(0x1 << TIMSK_TOIE2_Pos)		/*!< 0x40 */
#define TIMSK_TOIE2								(TIMSK_TOIE2_Mask)				/*!< Timer/Counter2 Overflow Interrupt Enable */

#define TIMSK_OCIE2_Pos							(7)
#define TIMSK_OCIE2_Mask						(0x1 << TIMSK_OCIE2_Pos)		/*!< 0x80 */
#define TIMSK_OCIE2								(TIMSK_OCIE2_Mask)				/*!< Timer/Counter2 Output Compare Match Interrupt Enable */

/*******************  Bit definition for TIMSK register  ********************/
#define TIMSK_TOV0_Pos							(0)
#define TIMSK_TOV0_Mask							(0x1 << TIMSK_TOV0_Pos)			/*!< 0x01 */
#define TIMSK_TOV0								(TIMSK_TOV0_Mask)				/*!< Timer/Counter0 Overflow Flag */

#define TIMSK_OCF0_Pos							(1)
#define TIMSK_OCF0_Mask							(0x1 << TIMSK_OCF0_Pos)			/*!< 0x02 */
#define TIMSK_OCF0								(TIMSK_OCF0_Mask)				/*!< Output Compare Flag 0 */

#define TIMSK_TOV1_Pos							(2)
#define TIMSK_TOV1_Mask							(0x1 << TIMSK_TOV1_Pos)			/*!< 0x04 */
#define TIMSK_TOV1								(TIMSK_TOV1_Mask)				/*!< Timer/Counter1, Overflow Flag */

#define TIMSK_OCF1B_Pos							(3)
#define TIMSK_OCF1B_Mask						(0x1 << TIMSK_OCF1B_Pos)		/*!< 0x08 */
#define TIMSK_OCF1B								(TIMSK_OCF1B_Mask)				/*!< Timer/Counter1, Output Compare B Match Flag */

#define TIMSK_OCF1A_Pos							(4)
#define TIMSK_OCF1A_Mask						(0x1 << TIMSK_OCF1A_Pos)		/*!< 0x10 */
#define TIMSK_OCF1A								(TIMSK_OCF1A_Mask)				/*!< Timer/Counter1, Output Compare A Match Flag */

#define TIMSK_ICF1_Pos							(5)
#define TIMSK_ICF1_Mask							(0x1 << TIMSK_ICF1_Pos)			/*!< 0x20 */
#define TIMSK_ICF1								(TIMSK_ICF1_Mask)				/*!< Timer/Counter1, Input Capture Flag */

#define TIMSK_TOV2_Pos							(6)
#define TIMSK_TOV2_Mask							(0x1 << TIMSK_TOV2_Pos)			/*!< 0x40 */
#define TIMSK_TOV2								(TIMSK_TOV2_Mask)				/*!< Timer/Counter2 Overflow Flag */

#define TIMSK_OCF2_Pos							(7)
#define TIMSK_OCF2_Mask							(0x1 << TIMSK_OCF2_Pos)			/*!< 0x80 */
#define TIMSK_OCF2								(TIMSK_OCF2_Mask)				/*!< Output Compare Flag 2 */

// *-*-*-*-*-*-*-*-*-*-*-*-*-
// -*-*-*-*-* ADC -*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-

/*******************  Bit definition for ADC_ADCSRA register  ********************/
#define ADC_ADCSRA_ADPSn_Pos					(0)
#define ADC_ADCSRA_ADPSn_Mask					(0x7 << ADC_ADCSRA_ADPSn_Pos)	/*!< 0x07 */
#define ADC_ADCSRA_ADPSn						(ADC_ADCSRA_ADPSn_Mask)			/*!< ADC Prescaler Select [n = 2:0] >*/

#define ADC_ADCSRA_ADIE_Pos						(3)
#define ADC_ADCSRA_ADIE_Mask					(0x1 << ADC_ADCSRA_ADIE_Pos)	/*!< 0x08 */
#define ADC_ADCSRA_ADIE							(ADC_ADCSRA_ADIE_Mask)			/*!< ADC Interrupt Enable >*/

#define ADC_ADCSRA_ADIF_Pos						(4)
#define ADC_ADCSRA_ADIF_Mask					(0x1 << ADC_ADCSRA_ADIF_Pos)	/*!< 0x10 */
#define ADC_ADCSRA_ADIF							(ADC_ADCSRA_ADIF_Mask)			/*!< ADC Interrupt Flag >*/

#define ADC_ADCSRA_ADATE_Pos					(5)
#define ADC_ADCSRA_ADATE_Mask					(0x1 << ADC_ADCSRA_ADATE_Pos)	/*!< 0x20 */
#define ADC_ADCSRA_ADATE						(ADC_ADCSRA_ADATE_Mask)			/*!< ADC Auto Trigger Enable >*/

#define ADC_ADCSRA_ADSC_Pos						(6)
#define ADC_ADCSRA_ADSC_Mask					(0x1 << ADC_ADCSRA_ADSC_Pos)	/*!< 0x40 */
#define ADC_ADCSRA_ADSC							(ADC_ADCSRA_ADSC_Mask)			/*!< ADC Start Conversion >*/

#define ADC_ADCSRA_ADEN_Pos						(7)
#define ADC_ADCSRA_ADEN_Mask					(0x1 << ADC_ADCSRA_ADEN_Pos)	/*!< 0x80 */
#define ADC_ADCSRA_ADEN							(ADC_ADCSRA_ADEN_Mask)			/*!< ADC Enable >*/

/*******************  Bit definition for ADC_ADMUX register  ********************/
#define ADC_ADMUX_MUXn_Pos						(0)
#define ADC_ADMUX_MUXn_Mask						(0x1F << ADC_ADMUX_MUXn_Pos)	/*!< 0x1F */
#define ADC_ADMUX_MUXn							(ADC_ADMUX_MUXn_Mask)			/*!< Analog Channel Selection [n = 4:0] >*/

#define ADC_ADMUX_ADLAR_Pos						(5)
#define ADC_ADMUX_ADLAR_Mask					(0x1 << ADC_ADMUX_ADLAR_Pos)	/*!< 0x20 */
#define ADC_ADMUX_ADLAR							(ADC_ADMUX_ADLAR_Mask)			/*!< ADC Left Adjust Result >*/

#define ADC_ADMUX_REFSn_Pos						(6)
#define ADC_ADMUX_REFSn_Mask					(0x3 << ADC_ADMUX_REFSn_Pos)	/*!< 0xC0 */
#define ADC_ADMUX_REFSn							(ADC_ADMUX_REFSn_Mask)			/*!< Reference Selection [n = 1:0] >*/

#endif /* BITFIELD_H_ */