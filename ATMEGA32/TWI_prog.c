/*
 * TWI_prog.c
 *
 *  Created on: Mar 27, 2021
 *      Author: DELL
 */
#include "LIB/types.h"
#include "LIB/Bit_Math.h"
#include "TWI_prv.h"
#include "TWI_interface.h"
#include "TWI_config.h"
#include "LCD_interface.h"


void	TWI_vidInit()
{
	TWI_TWBR = 32;
	TWI_TWCR |= (1<<TWI_TWEN)|(1 << TWI_TWEA);
}

void	TWI_vidStart()
{
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWSTA)|(1<<TWI_TWEN);
	while(!GET_BIT(TWI_TWCR,TWI_TWINT));
}

void	TWI_vidStop()
{
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWSTO);
}

void	TWI_vidSendSLA_R(u8 Sla)
{
	TWI_TWDR = Sla << 1 | 1;
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);
	while(!GET_BIT(TWI_TWCR,TWI_TWINT));
 }

void	TWI_vidSendSLA_W(u8 Sla)
{
	TWI_TWDR = Sla << 1;
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);
	while(!GET_BIT(TWI_TWCR,TWI_TWINT));
}

u8		TWI_u8CheckStatus()
{
	return (TWI_TWSR & 0xF8);
}

void		TWI_vidSend(u8 data)
{
	TWI_TWDR = data;
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);
	while(!GET_BIT(TWI_TWCR,TWI_TWINT));
}

u8		TWI_u8ReceiveNACK()
{
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN);
	while(!GET_BIT(TWI_TWCR,TWI_TWINT));
	return TWI_TWDR;
}

u8		TWI_u8ReceiveACK()
{
	TWI_TWCR = (1<<TWI_TWINT)|(1<<TWI_TWEN)|(1<<TWI_TWEA);
	while(!GET_BIT(TWI_TWCR,TWI_TWINT));
	return TWI_TWDR;
}
