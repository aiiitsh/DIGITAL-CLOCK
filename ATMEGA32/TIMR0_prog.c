/*
 * TIM0_prog.c
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */


#include	"LIB/TYPES.h"
#include	"LIB/Bit_Math.h"
#include 	"TIMR0_interface.h"
#include	"TIMR0_confg.h"
#include	"TIMR0_prv.h"

void TIMR0_vidInit()
{
	TCCR0 = (WAVE_GENERATION_MODE & 0b01) << WGM00 | ((WAVE_GENERATION_MODE & 0b10) >> 1) << WGM01 | COMPARE_OUTPUT_MODE << COM00;
	TIMSK = ((OC_INTERRUPT << OCIE0) | (OVF_INTERRUPT << TOIE0)) | ((0xFC) & TIMSK);
}

void TIMR0_vidForceCompareChannel()
{
	SET_BIT(TCCR0, FOC0);
}

void TIMR0_vidStart()
{
	TCCR0 |= CLOCK;
}

void TIMR0_vidStop()
{
	TCCR0 &= 7;
}

u8	 TIMR0_u8GetOCFlag()
{
	return GET_BIT(TIFR, OCF0);
}

u8	 TIMR0_u8GetOVFlag()
{
	return GET_BIT(TIFR, TOV0);
}

void TIMR0_vidSET_TCNT0(u8 data)
{
	TCNT0 = data;
}

void TIMR0_vidSET_OCR0(u8 data)
{
	OCR0 = data;
}

u8  TIMR0_u8GET_TCNT0()
{
	return TCNT0;
}

u8  TIMR0_u8GET_OCR0()
{
	return OCR0;
}
