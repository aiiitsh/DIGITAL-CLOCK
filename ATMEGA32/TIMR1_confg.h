/*
 * TIMR1_confg.h
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */

#ifndef TIMR1_CONFG_H_
#define TIMR1_CONFG_H_

#define WAVE_GENERATION_MODE				FAST_PWM_10BIT

#define COMPARE_OUTPUT_MODE_A				FAST_PWM_SET_ON_CMP_CLEAR_ON_TOP

#define COMPARE_OUTPUT_MODE_B				FAST_PWM_SET_ON_CMP_CLEAR_ON_TOP

#define INPUT_NOISE_CANCELER				DEACTIVATE

#define INPUT_CAPTURE_EDGE					FALLING

#define CLOCK								NO_PRESCALER

#define ICU_INTERRUPT						DISABLE

#define OCA_INTERRUPT						DISABLE

#define OCB_INTERRUPT						DISABLE

#define OVF_INTERRUPT						DISABLE

#endif /* TIMR1_CONFG_H_ */
