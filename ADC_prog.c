/*
 * ADC_prog.c
 *
 *  Created on: Feb 20, 2021
 *      Author: DELL
 */
#include "LIB/TYPES.h"
#include "LIB/Bit_Math.h"
#include "ADC_prv.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "GLOBINT_interface.h"
#include <avr/interrupt.h>

static u16 RES;

void ADC_vidInit()
{
	SFIOR |= (AUTO_TRIGGER_SOURCE << ADTS0);
	ADC_ADMUX = (ADC_VREF << REFS0)|(ADC_RES_ADJUST<<ADLAR);
	ADC_ADCSRA = (1 << ADEN)|(ADC_MOD<<ADIE)|(AUTO_TRIGGER << ADATE)|CLOCK;
#if(ADC_MOD == ADC_INT)
	GLOBINT_vidEnable();
#endif

}
#if(ADC_MOD == ADC_POLL)
u16 ADC_u16GetADCRead(u8 chid)
{
	chid &= 0x07;
	ADC_ADMUX = (ADC_ADMUX & 0xF8) | chid;
	ADC_ADCSRA |= (1<<ADSC);
	while(!GET_BIT(ADC_ADCSRA,ADIF));
	return ADC_ADCRES;
}
#endif
#if(ADC_MOD == ADC_INT)
void ADC_vidStartConversion(u8 chid)
{
	chid &= 0x07;
	ADC_ADMUX = (ADC_ADMUX & 0xF8) | chid;
	ADC_ADCSRA |= (1<<ADSC);
}
#endif
void ADC_vidEnable()
{
	SET_BIT(ADC_ADCSRA,ADEN);
}

void ADC_vidDisable()
{
	CLR_BIT(ADC_ADCSRA,ADEN);
}
#if(ADC_MOD == ADC_INT)
ISR(ADC_vect)
{
	RES = ADC_ADCRES;
}
#endif
u16 ADC_u16GetConverted()
{
	return RES;
}


void ADC_vidSetADCChannel(u8 chid)
{
	chid &= 0x07;
	ADC_ADMUX = (ADC_ADMUX & 0xF8) | chid;
}
