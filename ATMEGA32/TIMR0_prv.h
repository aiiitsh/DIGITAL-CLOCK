/*
 * TIM0_prv.h
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */

#ifndef TIMR0_PRV_H_
#define TIMR0_PRV_H_

#define TCCR0 *((volatile u8*)0x53)
#define TCNT0  *((volatile u8*)0x52)
#define OCR0  *((volatile u8*)0x5C)
#define TIMSK  *((volatile u8*)0x59)
#define TIFR   *((volatile u8*)0x58)

#define CS00  0
#define CS01  1
#define CS02  2
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7

#define TOIE0 0
#define OCIE0 1

#define TOV0  0
#define OCF0  1

#define TIMR0_OVF	*((volatile u16*)0x16)
#define TIMR0_COMP	*((volatile void*)0x14)

#endif /* TIMR0_PRV_H_ */
