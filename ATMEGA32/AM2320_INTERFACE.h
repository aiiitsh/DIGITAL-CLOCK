/*
 * AM2320_INTERFACE.h
 *
 *  Created on: Jun 19, 2023
 *      Author: mahmo
 */

#ifndef AM2320_INTERFACE_H_
#define AM2320_INTERFACE_H_

u32 AM2320_u32GetRegistersValue();

u16 AM2320_u8GetTemperature(u32 data);

u16 AM2320_u8GetHumidity(u32 data);

#endif /* AM2320_INTERFACE_H_ */
