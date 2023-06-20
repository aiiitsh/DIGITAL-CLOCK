/*
 * UART_prog.c
 *
 *  Created on: Mar 20, 2021
 *      Author: DELL
 */
#include"LIB/types.h"
#include"UART_prv.h"
#include"UART_confg.h"
#include"UART_interface.h"

void UART_vidInit()
{
	UART_UBRRH= (BAUD_RATE>>8) ;
	UART_UBRRL=BAUD_RATE;
	UART_UCSRB= (1<<UART_TXEN)|(1<<UART_RXEN);
	UART_UCSRC= (1<<UART_URSEL)|(1<<UART_UCSZ0)|(1<<UART_UCSZ1);
}

void UART_vidTransmit(u8 Byte)
{
	//while(!(UART_UCSRA&(1<<UART_UDRE)));
	UART_UDR=Byte;
}

u8 UART_u8Receive()
{
	while(!(UART_UCSRA&(1<<UART_RXC)));
	return UART_UDR;
}
