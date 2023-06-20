/*
 * ADC_config.h
 *
 *  Created on: Feb 20, 2021
 *      Author: DELL
 */

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_
/*voltage reference*/
/*RANGE: ADC_VCC , ADC_INTERNAL_VREF , ADC_EXT_VREF*/

#define ADC_VREF	ADC_VCC

/*ADC MODE*/
/*Range: ADC_INT , ADC_POLL*/

#define ADC_MOD		ADC_POLL

/*Result adjustment*/
/*Range: ADC_RIGHT , ADC_LEFT*/

#define ADC_RES_ADJUST	ADC_RIGHT

#define AUTO_TRIGGER	DISABLE

#define AUTO_TRIGGER_SOURCE	TIMER1_OVF

#define CLOCK PRESCALER_64

#endif /* ADC_CONFIG_H_ */
