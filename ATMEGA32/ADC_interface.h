/*
 * ADC_interface.h
 *
 *  Created on: Feb 20, 2021
 *      Author: DELL
 */

#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

/*********************************************************/
/********************Public Macros************************/
/*********************************************************/

#define	ADC_CH0		0
#define ADC_CH1		1
#define ADC_CH2		2
#define ADC_CH3		3
#define ADC_CH4		4
#define ADC_CH5		5
#define ADC_CH6		6
#define ADC_CH7		7

#define FREE_RUNNING_MODE		0b000
#define ANALOG_COMPARATOR		0b001
#define EXTERNAL_INTERRUPT_0	0b010
#define TIMER0_CMP				0b011
#define TIMER0_OVF				0b100
#define TIMER_CMP_B				0b101
#define TIMER1_OVF				0b110
#define TIMER1_CV				0b111

#define PRESCALER_2			0b000
#define PRESCALER_4			0b010
#define PRESCALER_8			0b011
#define PRESCALER_16		0b100
#define PRESCALER_32		0b101
#define PRESCALER_64		0b110
#define PRESCALER_128		0b111

#define ENABLE	1
#define DISABLE	0



/*********************************************************/
/******************Public Functions***********************/
/*********************************************************/

void ADC_vidInit();

u16 ADC_u16GetADCRead(u8 chid);

void ADC_vidStartConversion(u8 chid);

u16 ADC_u16GetConverted();

void ADC_vidEnable();

void ADC_vidDisable();

#endif /* ADC_INTERFACE_H_ */
