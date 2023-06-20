/*
 * TIM1_prog.c
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */


#include	"LIB/TYPES.h"
#include	"LIB/Bit_Math.h"
#include 	"TIMR1_interface.h"
#include	"TIMR1_confg.h"
#include	"TIMR1_prv.h"

void TIMR1_vidInit()
{
	TCCR1A = (COMPARE_OUTPUT_MODE_A << COM1A0) | (COMPARE_OUTPUT_MODE_B << COM1B0) | (WAVE_GENERATION_MODE & 0b11);
	TCCR1B = (INPUT_NOISE_CANCELER << ICNC1) | (INPUT_CAPTURE_EDGE  << ICES1) | (((WAVE_GENERATION_MODE & 0b1100) >> 2) << WGM12) | (CLOCK);
	TIMSK = ((ICU_INTERRUPT << TICIE1) | (OCA_INTERRUPT << OCIE1A) | (OCB_INTERRUPT << OCIE1B) | (OVF_INTERRUPT << TOIE1)) | ((0xC3) & TIMSK);
}

void TIMR1_vidForceCompareChannel_A()
{
	SET_BIT(TCCR1A, FOC1A);
}

void TIMR1_vidForceCompareChannel_B()
{
	SET_BIT(TCCR1A, FOC1B);
}

void TIMR1_vidChangeClock(u8 clock)
{
	TCCR1B = (TCCR1B & 0b11111000)|clock;
}

u8	 TIMR1_u8GetICUFlag()
{
	return GET_BIT(TIFR, ICF1);
}

u8	 TIMR1_u8GetOCAFlag()
{
	return GET_BIT(TIFR, OCF1A);
}

u8	 TIMR1_u8GetOCBFlag()
{
	return GET_BIT(TIFR, OCF1B);
}

u8	 TIMR1_u8GetOVFlag()
{
	return GET_BIT(TIFR, TOV1);
}

void TIMR1_vidSET_TCNT1(u16 data)
{
	TCNT1 = data;
}

void TIMR1_vidSET_OCR1A(u16 data)
{
	OCR1A = data;
}

void TIMR1_vidSET_OCR1B(u16 data)
{
	OCR1B = data;
}

void TIMR1_vidSET_ICR1(u16 data)
{
	ICR1 = data;
}

u16  TIMR1_u16GET_TCNT1()
{
	return TCNT1;
}

u16  TIMR1_u16GET_OCR1A()
{
	return OCR1A;
}

u16  TIMR1_u16GET_OCR1B()
{
	return OCR1B;
}

u16  TIMR1_u16GET_ICR1()
{
	return ICR1;
}
