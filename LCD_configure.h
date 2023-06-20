/*
 * LCD_configure.h
 *
 *  Created on: Jan 23, 2021
 *      Author: DELL
 */

#ifndef LCD_CONFIGURE_H_
#define LCD_CONFIGURE_H_

/****************************************/
/********Send data on that port**********/
/****************************************/
#define LCD_DATA_PORT		DIO_PORTB

/****************************************/
/******Send commands on that port********/
/****************************************/

#define LCD_CONTROL_PORT	DIO_PORTC

/****************************************/
/********command/data on that pin********/
/****************************************/

#define LCD_RS_PIN			DIO_PIN4

/****************************************/
/********read/write on that pin********/
/****************************************/

#define LCD_RW_PIN			DIO_PIN3

/****************************************/
/***********pulses on that pin***********/
/****************************************/

#define LCD_E_PIN			DIO_PIN2


#endif /* LCD_CONFIGURE_H_ */
