/*
 * AM2320_prog.c
 *
 *  Created on: Jun 19, 2023
 *      Author: mahmo
 */

#include "LIB/TYPES.h"
#include "TWI_interface.h"
#include "AM2320_INTERFACE.h"

u32 AM2320_u32GetRegistersValue()
{
		u8 data[8];
		TWI_vidStart();
		if(TWI_u8CheckStatus() != START)
			return 0xFFFF;
		TWI_vidSendSLA_W(0x5C);
		TWI_vidSend(0x03);
		TWI_vidSend(0x00);
		TWI_vidSend(0x04);
		TWI_vidStop();
		TWI_vidStart();
		if(TWI_u8CheckStatus() != START)
			return 0xFFFF;
		TWI_vidSendSLA_R(0x5C);
		if(TWI_u8CheckStatus() == SLA_R_NACK)
			return 0xFFFF;
		for(u8 i;i<8;i++)
		{
			data[i] = TWI_u8ReceiveACK();
			if(TWI_u8CheckStatus() == DATA_R_NACK)
				return 0xFFFF;
		}
		TWI_vidStop();
		return (((u32)data[2] << 24) | ((u32)data[3] << 16) | ((u32)data[4] << 8) | (u32)data[5]);
}

u16 AM2320_u8GetTemperature(u32 data)
{
	return data;
}

u16 AM2320_u8GetHumidity(u32 data)
{
	return data >> 16;
}
