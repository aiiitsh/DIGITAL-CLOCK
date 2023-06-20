/*
 * TIM2_prv.h
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */

#ifndef TIMR2_PRV_H_
#define TIMR2_PRV_H_

#define TCCR2  *((volatile u8*)0x45)
#define TCNT2  *((volatile u8*)0x44)
#define OCR2   *((volatile u8*)0x43)
#define ASSR   *((volatile u8*)0x42)
#define TIMSK  *((volatile u8*)0x59)
#define TIFR   *((volatile u8*)0x58)

#define CS20  0
#define CS21  1
#define CS22  2
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2  7

#define TOIE2 6
#define OCIE2 7

#define TOV2  6
#define OCF2  7

#endif /* TIMR2_PRV_H_ */
