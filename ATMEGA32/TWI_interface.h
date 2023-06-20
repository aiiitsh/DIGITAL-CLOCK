/*
 * TWI_interface.h
 *
 *  Created on: Mar 27, 2021
 *      Author: DELL
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

void	TWI_vidInit();

void	TWI_vidStart();

void	TWI_vidStop();

void	TWI_vidSendSLA_R(u8 Sla);

void	TWI_vidSendSLA_W(u8 Sla);

void	TWI_vidSend(u8 data);

u8		TWI_u8CheckStatus();

u8		TWI_u8ReceiveACK();

u8		TWI_u8ReceiveNACK();


#define NO_PRESCALER	0b00
#define PRESCALER_4		0b01
#define PRESCALER_16	0b10
#define PRESCALER_64	0b11

#define ENABLE		1
#define DISABLE		0

#define START			0x08
#define	R_START			0x10
#define SLA_W_ACK		0x18
#define SLA_W_NACK		0x20
#define DATA_W_ACK		0x28
#define DATA_W_NACK		0x30
#define ARBITRATION_L	0x38
#define SLA_R_ACK		0x40
#define SLA_R_NACK		0x48
#define DATA_R_ACK		0x50
#define DATA_R_NACK		0x58

#endif /* TWI_INTERFACE_H_ */
