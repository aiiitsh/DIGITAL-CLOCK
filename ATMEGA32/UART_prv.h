/*
 * UART_prv.h
 *
 *  Created on: Mar 20, 2021
 *      Author: DELL
 */

#ifndef UART_PRV_H_
#define UART_PRV_H_

#define UART_UDR	*((volatile u8*)0x2C)
#define UART_UCSRA	*((volatile u8*)0x2B)
#define UART_UCSRB	*((volatile u8*)0x2A)
#define UART_UCSRC	*((volatile u8*)0x40)
#define UART_UBRRL	*((volatile u8*)0x29)
#define UART_UBRRH	*((volatile u8*)0x40)

#define BAUD_RATE	(((8000000UL)/(BAUD*16UL))-1)

#define UART_TXB8	0
#define UART_RXB8	1
#define UART_UCSZ2	2
#define UART_TXEN	3
#define UART_RXEN	4
#define UART_UDRIE	5
#define UART_TXCIE	6
#define UART_RXCIE	7

#define UART_MPCM	0
#define UART_U2X	1
#define UART_PE		2
#define UART_DOR	3
#define UART_FE		4
#define UART_UDRE	5
#define UART_TXC	6
#define UART_RXC	7

#define UART_UCPOL	0
#define UART_UCSZ0	1
#define UART_UCSZ1	2
#define UART_USBS	3
#define UART_UPM0	4
#define UART_UPM1	5
#define UART_UMSEL	6
#define UART_URSEL	7



#endif /* UART_PRV_H_ */
