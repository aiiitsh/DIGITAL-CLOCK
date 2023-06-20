/*
 * WDT_prog.c
 *
 *  Created on: Jun 19, 2023
 *      Author: mahmo
 */

#include "LIB/TYPES.h"
#include "LIB/Bit_Math.h"
#include "WDT_prv.h"
#include "WDT_INTERFACE.h"

void WDT_vidEnable()
{
	SET_BIT(WDTCR,WDE);
}

void WDT_vidDisable()
{
	WDTCR = (WDTCR & 0b111) | 0b11000;
}

void WDT_vidSetClock(u8 prescaler)
{
	WDTCR |= prescaler;
}
