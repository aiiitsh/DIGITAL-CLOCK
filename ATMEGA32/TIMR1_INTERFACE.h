/*
 * TIM1_INTERFACE.h
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */

#ifndef TIMR1_INTERFACE_H_
#define TIMR1_INTERFACE_H_

//MAIN FUNCTIONS
/*************************************/
void TIMR1_vidInit();

void TIMR1_vidForceCompareChannel_A();

void TIMR1_vidForceCompareChannel_B();

void TIMR1_vidSET_TCNT1(u16 data);

void TIMR1_vidSET_OCR1A(u16 data);

void TIMR1_vidSET_OCR1B(u16 data);

void TIMR1_vidSET_ICR1(u16 data);

void TIMR1_vidChangeClock(u8 clock);

u16  TIMR1_u16GET_TCNT1();

u16  TIMR1_u16GET_OCR1A();

u16  TIMR1_u16GET_OCR1B();

u16  TIMR1_u16GET_ICR1();

u8	 TIMR1_u8GetICUFlag();

u8	 TIMR1_u8GetOCAFlag();

u8	 TIMR1_u8GetOCBFlag();

u8	 TIMR1_u8GetOVFlag();
/*************************************/

//MODES of wave generation
/***************************************************************************************************************/
#define NORMAL									0b0000		//TOP: 0xFFFF	UOF OCR1x: IMMEDIATE	TOV1: MAX
#define PWM_PHASE_CORRECT_8BIT					0b0001		//TOP: 0x00FF	UOF OCR1x: TOP      	TOV1: BOTTOM
#define PWM_PHASE_CORRECT_9BIT					0b0010		//TOP: 0x01FF	UOF OCR1x: TOP      	TOV1: BOTTOM
#define PWM_PHASE_CORRECT_10BIT					0b0011		//TOP: 0x03FF	UOF OCR1x: TOP      	TOV1: BOTTOM
#define CTC_OCR1A								0b0100		//TOP: OCR1A	UOF OCR1x: IMMEDIATE	TOV1: MAX
#define FAST_PWM_8BIT							0b0101		//TOP: 0x00FF	UOF OCR1x: TOP      	TOV1: TOP
#define FAST_PWM_9BIT							0b0110		//TOP: 0x01FF	UOF OCR1x: TOP      	TOV1: TOP
#define FAST_PWM_10BIT							0b0111		//TOP: 0x03FF	UOF OCR1x: TOP      	TOV1: TOP
#define PWM_PHASE_AND_FREQUENCY_CORRECT_ICR1	0b1000		//TOP: ICR1 	UOF OCR1x: BOTTOM   	TOV1: BOTTOM
#define PWM_PHASE_AND_FREQUENCY_CORRECT_OCR1A	0b1001		//TOP: OCR1A	UOF OCR1x: BOTTOM   	TOV1: BOTTOM
#define PWM_PHASE_CORRECT_ICR1					0b1010		//TOP: ICR1 	UOF OCR1x: TOP      	TOV1: BOTTOM
#define PWM_PHASE_CORRECT_OCR1A					0b1011		//TOP: OCR1A	UOF OCR1x: TOP      	TOV1: BOTTOM
#define CTC_ICR1								0b1100		//TOP: ICR1 	UOF OCR1x: IMMEDIATE	TOV1: MAX
#define FAST_PWM_ICR1							0b1110		//TOP: ICR1 	UOF OCR1x: TOP      	TOV1: TOP
#define FAST_PWM_OCR1A							0b1111		//TOP: OCR1A	UOF OCR1x: TOP      	TOV1: TOP
/***************************************************************************************************************/

//MODES of compare output
/***********************************************************/
//NON PWM
#define NON_PWM_DISCONNECTED							0b00
#define NON_PWM_TOGGLE									0b01
#define NON_PWM_CLEAR									0b10
#define NON_PWM_SET										0b11
//FAST PWM
#define FAST_PWM_DISCONNECTED							0b00
#define FAST_PWM_TOGGLE									0b01
#define FAST_PWM_CLEAR_ON_CMP_SET_ON_TOP				0b10
#define FAST_PWM_SET_ON_CMP_CLEAR_ON_TOP				0b11
//PHASE CORRECT & PHASE AND FREQUENCY CORRECT
#define PF_CORRECT_DISCONNECTED							0b00
#define PF_CORRECT_TOGGLE								0b01
#define PF_CORRECT_CLEAR_UP_COUNTING_SET_DOWN_COUNTING	0b10
#define PF_CORRECT_SET_UP_COUNTING_CLEAR_DOWN_COUNTING	0b11
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

#endif /* TIMR1_INTERFACE_H_ */
