/*
 * UART_interface.h
 *
 *  Created on: Mar 20, 2021
 *      Author: DELL
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

void UART_vidInit();

void UART_vidTransmit(u8 Byte);

u8 UART_u8Receive();

#endif /* UART_INTERFACE_H_ */
