/*
 * MACROS.h
 *
 *  Created on: Jun 12, 2023
 *      Author: mahmo
 */

#ifndef MACROS_H_
#define MACROS_H_

#define HOUR_24	1
#define HOUR_12	0

#define TRUE	1
#define FALSE	0

#define main_display	0
#define main_menu		1

#define ALARM			2
#define TIMER			3
#define CONTRAST		4
#define BRIGHTNESS		5
#define ADJUST			6
#define CANCEL			7

#define SELECT			0b01111
#define LEFT			0b10111
#define RIGHT			0b11011
#define UP				0b11101
#define DOWN			0b11110

#define UPDATE_MINUTE	0
#define UPDATE_HOUR		1
#define UPDATE_TIME		2
#define UPDATE_DATE		3
#define UPDATE_SENSOR	4
#define NOTHING			10

#define STOP			0x00
#define FIRE_ALARM		0x03
#define FIRE_TIMER		0x09
#define GET_TEMPERATURE	0x12
#define GET_HUMIDITY	0x15

#endif /* MACROS_H_ */
