/*
 * TIM1_INTERFACE.h
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */

#ifndef TIMR0_INTERFACE_H_
#define TIMR0_INTERFACE_H_

//MAIN FUNCTIONS
/*************************************/
void TIMR0_vidInit();

void TIMR0_vidStart();

void TIMR0_vidStop();

void TIMR0_vidForceCompareChannel();

void TIMR0_vidSET_TCNT0(u8 data);

void TIMR0_vidSET_OCR0(u8 data);

u8  TIMR0_u8GET_TCNT0();

u8  TIMR0_u8GET_OCR0();

u8	 TIMR0_u8GetOCFlag();

u8	 TIMR0_u8GetOVFlag();
/*************************************/

//MODES of wave generation
/***************************************************************************************************************/
#define NORMAL									0b00		//TOP: 0xFFFF	UOF OCR1x: IMMEDIATE	TOV1: MAX
#define PWM_PHASE_CORRECT						0b01		//TOP: 0x00FF	UOF OCR1x: TOP      	TOV1: BOTTOM
#define CTC										0b10		//TOP: 0x01FF	UOF OCR1x: TOP      	TOV1: BOTTOM
#define FAST_PWM								0b11		//TOP: 0x03FF	UOF OCR1x: TOP      	TOV1: BOTTOM
/***************************************************************************************************************/

//MODES of compare output
/***********************************************************/
//NON PWM & CTC
#define NON_PWM_DISCONNECTED							0b00
#define NON_PWM_TOGGLE									0b01
#define NON_PWM_CLEAR									0b10
#define NON_PWM_SET										0b11
//FAST PWM
#define FAST_PWM_DISCONNECTED							0b00
#define FAST_PWM_TOGGLE									0b01
#define FAST_PWM_CLEAR_ON_CMP_SET_ON_TOP				0b10
#define FAST_PWM_SET_ON_CMP_CLEAR_ON_TOP				0b11
//PHASE CORRECT PWM
#define P_CORRECT_DISCONNECTED							0b00
#define P_CORRECT_CLEAR_UP_COUNTING_SET_DOWN_COUNTING	0b10
#define P_CORRECT_SET_UP_COUNTING_CLEAR_DOWN_COUNTING	0b11
/***********************************************************/

//CLOCK SELECT
/********************************/
#define NO_CLOCK			0b000
#define NO_PRESCALER		0b001
#define PRESCALER_8			0b010
#define PRESCALER_64		0b011
#define PRESCALER_256		0b100
#define PRESCALER_1024		0b101
#define EXTERNAL_FALLING	0b110
#define EXTERNAL_RISING		0b111
/********************************/

//IMORTANT MACROS FOR MODES SELECTIONS
/********************/
#define FALLING		0
#define RISING		1
#define ACTIVATE	1
#define DEACTIVATE	0
#define ENABLE		1
#define DISABLE		0
/********************/

#endif /* TIMR0_INTERFACE_H_ */
