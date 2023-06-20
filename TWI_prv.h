/*
 * TWI_prv.h
 *
 *  Created on: Mar 27, 2021
 *      Author: DELL
 */

#ifndef TWI_PRV_H_
#define TWI_PRV_H_

#define TWI_TWCR	*((volatile u8*)0x56)
#define TWI_TWDR	*((volatile u8*)0x23)
#define TWI_TWAR	*((volatile u8*)0x22)
#define TWI_TWSR	*((volatile u8*)0x21)
#define TWI_TWBR	*((volatile u8*)0x20)

#define TWI_TWBR7	7
#define	TWI_TWBR6	6
#define	TWI_TWBR5	5
#define	TWI_TWBR4	4
#define	TWI_TWBR3	3
#define	TWI_TWBR2	2
#define	TWI_TWBR1	1
#define	TWI_TWBR0	0

#define	TWI_TWINT	7
#define	TWI_TWEA	6
#define	TWI_TWSTA	5
#define	TWI_TWSTO	4
#define	TWI_TWWC	3
#define	TWI_TWEN	2
#define	TWI_TWIE	0

#define	TWI_TWS7	7
#define	TWI_TWS6	6
#define	TWI_TWS5	5
#define	TWI_TWS4	4
#define	TWI_TWS3	3
#define	TWI_TWPS1	1
#define	TWI_TWPS0	0

#define TWI_TWD7	7
#define TWI_TWD6	6
#define TWI_TWD5	5
#define TWI_TWD4	4
#define TWI_TWD3	3
#define TWI_TWD2	2
#define TWI_TWD1	1
#define TWI_TWD0	0

#define TWI_TWA6	7
#define TWI_TWA5	6
#define TWI_TWA4	5
#define TWI_TWA3	4
#define TWI_TWA2	3
#define TWI_TWA1	2
#define TWI_TWA0	1
#define TWI_TWGCE	0

#endif /* TWI_PRV_H_ */
