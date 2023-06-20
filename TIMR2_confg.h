/*
 * TIMR2_confg.h
 *
 *  Created on: May 2, 2023
 *      Author: mahmo
 */

#ifndef TIMR2_CONFG_H_
#define TIMR2_CONFG_H_

#define WAVE_GENERATION_MODE				CTC

#define COMPARE_OUTPUT_MODE					NON_PWM_DISCONNECTED

#define CLOCK								PRESCALER_256

#define OC_INTERRUPT						ENABLE

#define OVF_INTERRUPT						DISABLE

#endif /* TIMR2_CONFG_H_ */
