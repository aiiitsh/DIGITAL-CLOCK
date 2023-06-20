/*
 * VARIABLES.h
 *
 *  Created on: Jun 12, 2023
 *      Author: mahmo
 */

#ifndef VARIABLES_H_
#define VARIABLES_H_

u8 counter = 0;
u8 second = 50;
u8 minute = 58;
u8 hour = 11;
u8 day = 14;
u8 month = 6;
u16 year = 2023;
u8 day_night[] = " PM";
bool alarm_set = FALSE;
bool timer_set = FALSE;
u8 alarm_minute = 48;
u8 alarm_hour = 9;
u8 timer_second = 1;
u8 timer_minute = 0;
u8 timer_hour = 0;
bool timer_update = FALSE;
u8 alarm_day = 12;
u8 alarm_month = 6;
u8 alarm_day_night[] = " PM";
bool time_update = FALSE;
bool leap_year = FALSE;
u8 name_of_day = 0;
u8 hour_format = HOUR_12;
u8 display = main_display;
u8 date_size;
u8 contrast = 75;
u8 brightness = 75;
bool sensor_update = TRUE;
bool auto_brightness = TRUE;
bool timer_ended = FALSE;
bool alarm_ended = FALSE;
u16 battery = 1024;

const u8 * days_names[] = {"Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun"};
const u8 * months_names[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sept", "Oct", "Nov", "Dec"};
u8 max_month_days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#endif /* VARIABLES_H_ */
