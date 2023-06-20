/*
 * Dio_interface.h
 *
 *  Created on: Jan 22, 2021
 *      Author: DELL
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/****************************************************/
/******************Public functions******************/
/****************************************************/

void DIO_vidSetPinVal(u8 portid,u8 pinid,u8 pinval);
void DIO_vidSetPinDir(u8 portid,u8 pinid,u8 pinval);
void DIO_vidSetPortVal(u8 portid,u8 portval);
void DIO_vidSetPortDir(u8 portid,u8 portval);
void DIO_vidTogglePinVal(u8 portid,u8 pinid);
u8 DIO_u8GetPinVal(u8 portid,u8 pinid);

/****************************************************/
/********************Public Macros*******************/
/****************************************************/

/*Output status*/
#define DIO_HIGH	1
#define DIO_LOW		0
#define DIO_PORT_HIGH	0XFF
#define DIO_PORT_LOW	0X00
/*Direction status*/
#define DIO_OUTPUT	1
#define DIO_INPUT	0
#define DIO_PORT_OUTPUT	0XFF
#define DIO_PORT_INPUT	0X00
/*Port IDs*/
#define DIO_PORTA	0
#define DIO_PORTB	1
#define DIO_PORTC	2
#define DIO_PORTD	3
/*Pins IDs*/
#define DIO_PIN0	0
#define DIO_PIN1	1
#define DIO_PIN2	2
#define DIO_PIN3	3
#define DIO_PIN4	4
#define DIO_PIN5	5
#define DIO_PIN6	6
#define DIO_PIN7	7

#endif /* DIO_INTERFACE_H_ */
