/*
 * HELPER_FUNCTIONS.h
 *
 *  Created on: Jun 12, 2023
 *      Author: mahmo
 */

#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

void DISABLE_RESPONSES()
{
	TIMR1_vidChangeClock(NO_PRESCALER);
	UART_vidTransmit(STOP);
	alarm_ended = FALSE;
	timer_ended = FALSE;
}

void ALARM_RESPONSE()
{
	TIMR1_vidChangeClock(0b101);
	UART_vidTransmit(FIRE_ALARM);
	alarm_ended = TRUE;
}

u8 Size_Of_Date()
{
	u8 sum = 16;
	if(name_of_day == 1)
	{
		sum++;
	}
	else if(name_of_day == 3)
	{
		sum+=2;
	}
	if(month == 8)
	{
		sum++;
	}
	if(day > 9)
	{
		sum++;
	}
	if(sum%2)
		sum++;
	return sum;
}

bool IS_LEAP_YEAR()
{
	if (!(year % 4))
	{
		if (!(year % 100))
		{
			if (!(year % 400))
			{
				return TRUE;
			}
		}
		else
		{
			return TRUE;
		}
	}
	return FALSE;
}

int Day_Of_Week(u8 day, u8 month, u16 year) {
	if (month < 3)
	{
		month += 12;
		year--;
	}
	u16 k = year % 100;
	u16 j = year / 100;
	u16 h = (day + 13 * (month + 1) / 5 + k + k / 4 + j / 4 + 5 * j) % 7;
	// Adjust the result to match the day of the week (0 - Sunday, 1 - Monday, etc.)
	return (h + 5) % 7;
}

void SECOND_PRINTER()
{
	switch(hour_format)
	{
		case HOUR_12:
			LCD_vidCursorXY(11,2);
			break;
		case HOUR_24:
			LCD_vidCursorXY(13,2);
			break;
	}
	LCD_vidSendTimeElement(second);
}

void MINUTE_PRINTER()
{
	switch(hour_format)
	{
		case HOUR_12:
			LCD_vidCursorXY(8,2);
			break;
		case HOUR_24:
			LCD_vidCursorXY(10,2);
			break;
	}
	LCD_vidSendTimeElement(minute);
}

void HOUR_PRINTER()
{
	switch(hour_format)
	{
		case HOUR_12:
			LCD_vidCursorXY(5,2);
			LCD_vidSendTimeElement(hour);
			LCD_vidCursorXY(14,2);
			LCD_vidWriteStr(day_night);
		break;
		case HOUR_24:
			LCD_vidCursorXY(7,2);
			if(day_night[1] == 'P')
			{
				switch(hour)
				{
					case 12:
						LCD_vidSendTimeElement(12);
						break;
					default:
						LCD_vidSendTimeElement(hour + 12);
				}
			}
			else
			{
				switch(hour)
				{
					case 12:
						LCD_vidSendTimeElement(0);
						break;
					default:
						LCD_vidSendTimeElement(hour);
				}
			}
		break;
	}
}

void DATE_PRINTER()
{
	LCD_vidCursorXY(((20-date_size)/2)+1,3);
	LCD_vidWriteStr(days_names[name_of_day]);
	LCD_vidWriteStr(", ");
	LCD_vidSendDayElement(day);
	LCD_vidSendChar(' ');
	LCD_vidWriteStr(months_names[month - 1]);
	LCD_vidWriteStr(", ");
	LCD_vidSendYearElement(year);
}

void ALARM_PRINTER()
{
	LCD_vidCursorXY(6,2);
	LCD_vidSendTimeElement(alarm_hour);
	LCD_vidSendChar(':');
	LCD_vidSendTimeElement(alarm_minute);
	LCD_vidWriteStr("  ");
	LCD_vidWriteStr(alarm_day_night);
	LCD_vidCursorXY(5,3);
	LCD_vidWriteStr(days_names[Day_Of_Week(alarm_day, alarm_month, year)]);
	LCD_vidWriteStr(", ");
	LCD_vidSendDayElement(alarm_day);
	LCD_vidSendChar(' ');
	LCD_vidWriteStr(months_names[alarm_month-1]);
}

u8 TIME_UPDATER()
{
	u8 ret = UPDATE_MINUTE;
	minute++;
	if(minute >= 60)
	{
		minute = 0;
		hour++;
		ret = UPDATE_HOUR;
		if(hour > 12)
			hour = 1;
		else if(hour >= 12)
		{
			ret = UPDATE_TIME;
			switch(day_night[1])
			{
				case 'P': day_night[1] = 'A'; DATE_UPDATER(); ret = UPDATE_DATE; break;
				case 'A': day_night[1] = 'P'; break;
			}
		}
	}
	if(alarm_hour == hour && alarm_minute == minute && alarm_day_night[1] == day_night[1] && alarm_day == day && alarm_month == month && alarm_set)
	{
		alarm_set = FALSE;
		ALARM_RESPONSE();
	}
	time_update = FALSE;
	return ret;
}

void DATE_UPDATER()
{
	day++;
	if(day > max_month_days[month - 1])
	{
		day = 1;
		month++;
		if(month > 12)
		{
			year++;
			leap_year = IS_LEAP_YEAR();
			if(leap_year)
				max_month_days[1] = 29;
			else
				max_month_days[1] = 28;
		}
	}
	name_of_day = Day_Of_Week(day,month,year);
	date_size = Size_Of_Date();
}

void SENSOR_UPDATER()
{
	if(auto_brightness)
	{
		TIMR1_vidSET_OCR1A(ADC_u16GetADCRead(ADC_CH7));
	}
	battery = ADC_u16GetADCRead(ADC_CH6);
	sensor_update = FALSE;
}

void DOTS_PRINTER()
{
	switch(hour_format)
	{
		case HOUR_12:
			LCD_vidCursorXY(7,2);
			LCD_vidSendChar(':');
			LCD_vidCursorXY(10,2);
			LCD_vidSendChar(':');
		break;
		case HOUR_24:
			LCD_vidCursorXY(9,2);
			LCD_vidSendChar(':');
			LCD_vidCursorXY(12,2);
			LCD_vidSendChar(':');
		break;
	}
}

void TIMER_UPDATER()
{
	timer_minute--;
	if(timer_minute == 0xFF)
	{
		timer_minute = 59;
		timer_hour--;
	}
	timer_update = FALSE;
}

void STATUS_BAR()
{
	u16 temperature,humidity;
	UART_vidTransmit(GET_TEMPERATURE);
	temperature = UART_u8Receive();
	temperature |= UART_u8Receive() << 8;
	UART_vidTransmit(GET_HUMIDITY);
	humidity = UART_u8Receive();
	humidity |= UART_u8Receive() << 8;
	LCD_vidCursorXY(1,4);
	LCD_vidSendDayElement(humidity/10);
	LCD_vidSendChar('.');
	LCD_vidSendDayElement(humidity%10);
	LCD_vidSendChar('%');
	LCD_vidSendChar(0x07);
	LCD_vidSendChar(' ');
	LCD_vidCursorXY(15,4);
	LCD_vidSendDayElement(temperature/10);
	LCD_vidSendChar('.');
	LCD_vidSendDayElement(temperature%10);
	LCD_vidSendChar(0x06);
	LCD_vidSendChar('C');
	LCD_vidCursorXY(8,4);

}

void NOTIFICATION_BAR()
{
	u8 old_timer_set,old_alarm_set;
	LCD_vidCursorXY(19,1);
	if(battery > 683)
		LCD_vidSendChar(0x03);
	else if(battery > 342)
		LCD_vidSendChar(0x04);
	else
		LCD_vidSendChar(0x05);
	if(timer_set != old_timer_set || old_alarm_set != alarm_set)
	{
		if(timer_set)
		{
			LCD_vidCursorXY(3,1);
			LCD_vidSendChar(0x01);
		}
		else
		{
			LCD_vidCursorXY(3,1);
			LCD_vidSendChar(' ');
		}
		if(alarm_set)
		{
			LCD_vidCursorXY(2,1);
			LCD_vidSendChar(0x00);
		}
		else
		{
			LCD_vidCursorXY(2,1);
			LCD_vidSendChar(' ');
		}
		old_timer_set = timer_set;
		old_alarm_set = alarm_set;
	}
}

u8 CHECKER()
{
	u8 ret = NOTHING;
	if(time_update)
	{
		ret = TIME_UPDATER();
	}
	if(sensor_update)
	{
		SENSOR_UPDATER();
		ret += UPDATE_SENSOR;
	}
	if(timer_update)
	{
		TIMER_UPDATER();
	}
	return ret;
}

#endif /* HELPER_FUNCTIONS_H_ */
