/*
 * TIM2_INTERFACE.h
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */

#ifndef TIMR2_INTERFACE_H_
#define TIMR2_INTERFACE_H_

//MAIN FUNCTIONS
/*************************************/
void TIMR2_vidInit();

void TIMR2_vidStart();

void TIMR2_vidStop();

void TIMR2_vidForceCompareChannel();

void TIMR2_vidSET_TCNT2(u8 data);

void TIMR2_vidSET_OCR2(u8 data);

u8  TIMR2_u8GET_TCNT2();

u8  TIMR2_u8GET_OCR2();

u8	 TIMR2_u8GetOCFlag();

u8	 TIMR2_u8GetOVFlag();
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
#define PRESCALER_32		0b011
#define PRESCALER_64		0b100
#define PRESCALER_128		0b101
#define PRESCALER_256		0b110
#define PRESCALER_1024		0b111
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

#endif /* TIMR2_INTERFACE_H_ */
