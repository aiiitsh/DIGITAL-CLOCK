/*
 * WDT_prv.h
 *
 *  Created on: Jun 19, 2023
 *      Author: mahmo
 */

#ifndef WDT_PRV_H_
#define WDT_PRV_H_

#define WDTCR *((volatile u8*)0x41)

#define WDP0	0
#define WDP1	1
#define WDP2	2
#define WDE		3
#define WDTOE	4

#endif /* WDT_PRV_H_ */
