/*
 * TIM2_prog.c
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */


#include	"LIB/TYPES.h"
#include	"LIB/Bit_Math.h"
#include 	"TIMR2_interface.h"
#include	"TIMR2_confg.h"
#include	"TIMR2_prv.h"

void TIMR2_vidInit()
{
	TCCR2 = (WAVE_GENERATION_MODE & 0b01) << WGM20 | ((WAVE_GENERATION_MODE & 0b10) >> 1) << WGM21 | COMPARE_OUTPUT_MODE << COM20;
	TIMSK = ((OC_INTERRUPT << OCIE2) | (OVF_INTERRUPT << TOIE2)) | ((0x3F) & TIMSK);
}

void TIMR2_vidForceCompareChannel()
{
	SET_BIT(TCCR2, FOC2);
}

void TIMR2_vidStart()
{
	TCCR2 |= CLOCK;
}

void TIMR2_vidStop()
{
	TCCR2 &= 7;
}

u8	 TIMR2_u8GetOCFlag()
{
	return GET_BIT(TIFR, OCF2);
}

u8	 TIMR2_u8GetOVFlag()
{
	return GET_BIT(TIFR, TOV2);
}

void TIMR2_vidSET_TCNT2(u8 data)
{
	TCNT2 = data;
}

void TIMR2_vidSET_OCR2(u8 data)
{
	OCR2 = data;
}

u8  TIMR2_u8GET_TCNT2()
{
	return TCNT2;
}

u8  TIMR2_u8GET_OCR2()
{
	return OCR2;
}
