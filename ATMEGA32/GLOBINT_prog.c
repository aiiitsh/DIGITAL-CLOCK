/*
 * GLOBINT_prog.c
 *
 *  Created on: Feb 19, 2021
 *      Author: DELL
 */
#include "LIB/TYPES.h"
#include "LIB/Bit_Math.h"
#include "GLOBINT_interface.h"
#include "GLOBINT_prv.h"

void GLOBINT_vidEnable()
{
	SET_BIT(SREG,7);
}

void GLOBINT_vidDisable()
{
	CLR_BIT(SREG,7);
}
