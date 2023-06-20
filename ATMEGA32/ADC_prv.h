/*
 * ADC_prv.h
 *
 *  Created on: Feb 20, 2021
 *      Author: DELL
 */

#ifndef ADC_PRV_H_
#define ADC_PRV_H_

#define ADC_VCC				1
#define ADC_INTERNAL_VREF	3
#define ADC_EXT_VREF		0

#define ADC_RIGHT			0
#define ADC_LEFT			1

#define ADC_ADCSRA		*((volatile u8*)0x26)
#define ADC_ADMUX		*((volatile u8*)0x27)
#define ADC_ADCRES		*((volatile u16*)0x24)
#define SFIOR			*((volatile u16*)0x24)

/*ADCSRA bits*/
#define ADPS0				0
#define ADPS1				1
#define ADPS2				2
#define ADIE				3
#define ADIF				4
#define ADATE				5
#define ADSC				6
#define ADEN				7

/*ADMUX bits*/
#define MUX0				0
#define MUX1				1
#define MUX2				2
#define MUX3				3
#define MUX4				4
#define ADLAR				5
#define REFS0				6
#define REFS1				7

/*SFIOR bits*/
#define ADTS0				5
#define ADTS1				6
#define ADTS2				7

#define ADC_POLL			0
#define ADC_INT				1

#endif /* ADC_PRV_H_ */
