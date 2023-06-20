/*
 * main.c
 *
 *  Created on: Jun 11, 2023
 *      Author: mahmo
 */
#define F_CPU 8000000UL
#include "LIB/TYPES.h"
#include "DIO_INTERFACE.h"
#include "TIMR0_INTERFACE.h"
#include "TIMR1_INTERFACE.h"
#include "TIMR2_INTERFACE.h"
#include "UART_interface.h"
#include "ADC_interface.h"
#include "GLOBINT_interface.h"
#include "LCD_interface.h"
#include "MACROS.h"
#include "VARIABLES.h"
#include "HELPER_FUNCTIONS.h"
#include <avr/interrupt.h>
#include <util/delay.h>

int main(){
	DIO_vidSetPortDir(DIO_PORTB, DIO_PORT_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTC, DIO_PIN2, DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTC, DIO_PIN3, DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTC, DIO_PIN4, DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTD, DIO_PIN4, DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);
	DIO_vidSetPinDir(DIO_PORTA, DIO_PIN0, DIO_INPUT);
	DIO_vidSetPinDir(DIO_PORTA, DIO_PIN1, DIO_INPUT);
	DIO_vidSetPinDir(DIO_PORTA, DIO_PIN2, DIO_INPUT);
	DIO_vidSetPinDir(DIO_PORTA, DIO_PIN3, DIO_INPUT);
	DIO_vidSetPinDir(DIO_PORTA, DIO_PIN4, DIO_INPUT);
	DIO_vidSetPinDir(DIO_PORTA, DIO_PIN6, DIO_INPUT);
	DIO_vidSetPinDir(DIO_PORTA, DIO_PIN7, DIO_INPUT);
	DIO_vidSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);
	DIO_vidSetPinVal(DIO_PORTA, DIO_PIN1, DIO_HIGH);
	DIO_vidSetPinVal(DIO_PORTA, DIO_PIN2, DIO_HIGH);
	DIO_vidSetPinVal(DIO_PORTA, DIO_PIN3, DIO_HIGH);
	DIO_vidSetPinVal(DIO_PORTA, DIO_PIN4, DIO_HIGH);
	LCD_vidInit();
	LCD_vidSendCommand(LCD_CLR);
	TIMR1_vidSET_OCR1B(768);
	TIMR1_vidSET_OCR1A(768);
	TIMR1_vidInit();
	TIMR2_vidSET_OCR2(125);
	TIMR2_vidInit();
	TIMR2_vidStart();
	UART_vidInit();
	ADC_vidInit();
	GLOBINT_vidEnable();
	name_of_day = Day_Of_Week(day, month, year);
	leap_year = IS_LEAP_YEAR();
	date_size = Size_Of_Date();
	if(leap_year)
		max_month_days[1] = 29;
	u8 choice = ALARM;
	u8 old_choice = TIMER;
	u8 x,y;
	u8 TEMP;
	bool loop = TRUE;
	u8 new_hour,new_minute,new_second,new_day,new_month,new_day_night[] = " PM";
	u8 custom_alarm[] = {0x04,0x0E,0x0E,0x0E,0x1F,0x00,0x04,0x00};
	u8 custom_timer[] = {0x04,0x0A,0x15,0x17,0x11,0x0A,0x04,0x00};
	u8 custom_back[] = {0x04,0x0E,0x15,0x04,0x04,0x04,0x04,0x04};
	u8 custom_fullcharged[] = {0x0E,0x1B,0x11,0x1F,0x1F,0x1F,0x1F,0x1F};
	u8 custom_60charged[] = {0x0E,0x1B,0x11,0x11,0x11,0x1F,0x1F,0x1F};
	u8 custom_30charged[] = {0x0E,0x1B,0x11,0x11,0x11,0x11,0x1F,0x1F};
	u8 custom_degree[] = {0x0E,0x0A,0x0E,0x00,0x00,0x00,0x00,0x00};
	u8 custom_drop[] = {0x04,0x0E,0x0E,0x1F,0x1F,0x1F,0x0E,0x00};
	LCD_vidCustomChar(0,custom_alarm);
	LCD_vidCustomChar(1,custom_timer);
	LCD_vidCustomChar(2,custom_back);
	LCD_vidCustomChar(3, custom_fullcharged);
	LCD_vidCustomChar(4, custom_60charged);
	LCD_vidCustomChar(5, custom_30charged);
	LCD_vidCustomChar(6, custom_degree);
	LCD_vidCustomChar(7, custom_drop);
	while(1)
	{
		switch(display)
		{
			case main_display:
				LCD_vidSendCommand(LCD_CLR);
				SECOND_PRINTER();
				MINUTE_PRINTER();
				HOUR_PRINTER();
				DOTS_PRINTER();
				DATE_PRINTER();
				NOTIFICATION_BAR();
				STATUS_BAR();
				while(display == main_display)
				{
					TEMP = CHECKER();
					if((u8)(TEMP-UPDATE_SENSOR) <= UPDATE_DATE || TEMP == 14)
					{
						TEMP-=UPDATE_SENSOR;
						STATUS_BAR();
					}
					switch(TEMP)
					{
						case UPDATE_DATE:DATE_PRINTER();
						case UPDATE_TIME:
						case UPDATE_HOUR:HOUR_PRINTER();
						case UPDATE_MINUTE:MINUTE_PRINTER();
						break;
					}
					NOTIFICATION_BAR();
					SECOND_PRINTER();
					while(!DIO_u8GetPinVal(DIO_PORTA, DIO_PIN4))
						if(alarm_ended || timer_ended)
							{DISABLE_RESPONSES();while(!DIO_u8GetPinVal(DIO_PORTA, DIO_PIN4));}
						else
							display = main_menu;
				}
			break;
			case ALARM:
				LCD_vidSendCommand(LCD_CLR);
				if(!alarm_set)
				{
					alarm_minute = minute;
					alarm_hour = hour;
					alarm_day = day;
					alarm_month = month;
					alarm_day_night[1] = day_night[1];
				}
				else
				{
					LCD_vidCursorXY(4,2);
					LCD_vidWriteStr("DISABLE  CHANGE");
					LCD_vidCursorXY(4,2);
					LCD_vidSendCommand(LCD_DISPON_CURSON);
					choice = 0;
					while(loop)
					{
						CHECKER();
						switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
						{
							case LEFT:
								LCD_vidCursorXY(4,2);
								choice = 0;
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == LEFT);
								break;
							case RIGHT:
								LCD_vidCursorXY(13,2);
								choice = 1;
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == RIGHT);
								break;
							case SELECT:
								loop = FALSE;
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
								break;
						}
					}
				}
				if(choice == 0)
				{
					alarm_set = FALSE;
					display = main_display;
					LCD_vidSendCommand(LCD_DISPON_CURSOFF);
					choice = ALARM;
					break;
				}
				LCD_vidSendCommand(LCD_DISPON_CURSON);
				choice = ALARM;
				loop = TRUE;
				LCD_vidSendCommand(LCD_CLR);
				ALARM_PRINTER();
				x = 7, y = 2;
				LCD_vidCursorXY(x,y);
				while(loop)
				{
					CHECKER();
					_delay_ms(10);
					switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
					{
						case LEFT:
									if(x == 10)
										x = 7;
									else if(x == 14)
										x = 10;
									else if(x == 5)
									{
										x = 14;
										y = 2;
									}
							LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == LEFT);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case RIGHT:
									if(x == 7)
										x = 10;
									else if(x == 10)
										x = 14;
									else if(x == 14)
									{
										x = 5;
										y = 3;
									}
							LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == RIGHT);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case UP:
									switch(x)
									{
										case 5: alarm_day++; if(alarm_day > max_month_days[alarm_month - 1]){alarm_day = 1; alarm_month++; if(alarm_month > 12){alarm_month = 1;}} LCD_vidCursorXY(5,3);LCD_vidWriteStr(days_names[Day_Of_Week(alarm_day, alarm_month, year)]);LCD_vidWriteStr(", ");LCD_vidSendDayElement(alarm_day);LCD_vidSendChar(' ');LCD_vidWriteStr(months_names[alarm_month-1]);LCD_vidWriteStr("    ");break;
										case 7: alarm_hour++; if(alarm_hour > 12) {alarm_hour = 1;} LCD_vidCursorXY(6,2);LCD_vidSendTimeElement(alarm_hour);break;
										case 10: alarm_minute++; if(alarm_minute > 59) alarm_minute = 0; LCD_vidCursorXY(9,2);LCD_vidSendTimeElement(alarm_minute);break;
										case 14: if(alarm_day_night[1] == 'P'){alarm_day_night[1] = 'A';}else{{alarm_day_night[1] = 'P';}} LCD_vidCursorXY(13,2);LCD_vidWriteStr(alarm_day_night);break;
									}
									LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == UP);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case DOWN:
									switch(x)
									{
										case 5: alarm_day--; if(alarm_day < 1){alarm_month--; if(alarm_month < 1){alarm_month = 1;}alarm_day = max_month_days[alarm_month - 1];} LCD_vidCursorXY(5,3);LCD_vidWriteStr(days_names[Day_Of_Week(alarm_day, alarm_month, year)]);LCD_vidWriteStr(", ");LCD_vidSendDayElement(alarm_day);LCD_vidSendChar(' ');LCD_vidWriteStr(months_names[alarm_month-1]);LCD_vidWriteStr("    ");break;
										case 7: alarm_hour--; if(alarm_hour < 1) {alarm_hour = 12;} LCD_vidCursorXY(6,2);LCD_vidSendTimeElement(alarm_hour);break;
										case 10: alarm_minute--; if(alarm_minute == 0xFF) alarm_minute = 59; LCD_vidCursorXY(9,2);LCD_vidSendTimeElement(alarm_minute);break;
										case 14: if(alarm_day_night[1] == 'P'){alarm_day_night[1] = 'A';}else{{alarm_day_night[1] = 'P';}} LCD_vidCursorXY(13,2);LCD_vidWriteStr(alarm_day_night);break;
									}
									LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == DOWN);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case SELECT:
							alarm_set = TRUE;
							loop = FALSE;
							display = main_display;
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
							LCD_vidSendCommand(LCD_DISPON_CURSOFF);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
					}
				}
				break;
			case TIMER:
				LCD_vidSendCommand(LCD_CLR);
				if(!timer_set)
				{
					LCD_vidCursorXY(7,2);
					LCD_vidSendTimeElement(timer_hour);
					LCD_vidSendChar(':');
					LCD_vidSendTimeElement(timer_minute);
					LCD_vidSendChar(':');
					LCD_vidSendTimeElement(timer_second);
					LCD_vidSendCommand(LCD_DISPON_CURSON);
					LCD_vidCursorXY(14,2);
					x = 14;
					loop = TRUE;
					while(loop)
					{
						CHECKER();
						_delay_ms(10);
						switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
						{
							case LEFT:
										if(x == 14)
											x = 11;
										else
											x = 8;
										LCD_vidCursorXY(x,2);
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == LEFT);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
							case RIGHT:
										if(x == 8)
											x = 11;
										else
											x = 14;
										LCD_vidCursorXY(x,2);
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == RIGHT);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
							case UP:
										switch(x)
										{
											case 8:
												timer_hour++; if(timer_hour > 99)timer_hour=0;LCD_vidCursorXY(7,2);LCD_vidSendTimeElement(timer_hour);if(timer_hour == 0 && timer_minute == 0 && timer_second == 0){timer_second = 1;LCD_vidCursorXY(13,2);LCD_vidSendTimeElement(timer_second);}
												break;
											case 11:
												timer_minute++; if(timer_minute > 99)timer_minute=0;LCD_vidCursorXY(10,2);LCD_vidSendTimeElement(timer_minute);if(timer_hour == 0 && timer_minute == 0 && timer_second == 0){timer_second = 1;LCD_vidCursorXY(13,2);LCD_vidSendTimeElement(timer_second);}
												break;
											case 14:
												timer_second++; if(timer_second > 99){if(timer_minute == 0 && timer_hour == 0)timer_second=1;else timer_second = 0;}LCD_vidCursorXY(13,2);LCD_vidSendTimeElement(timer_second);
												break;
										}
										LCD_vidCursorXY(x,2);
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == UP);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
							case DOWN:
										switch(x)
										{
											case 8:
												timer_hour--; if(timer_hour == 0xFF)timer_hour=99;LCD_vidCursorXY(7,2);LCD_vidSendTimeElement(timer_hour);if(timer_hour == 0 && timer_minute == 0 && timer_second == 0){timer_second = 1;LCD_vidCursorXY(13,2);LCD_vidSendTimeElement(timer_second);}
												break;
											case 11:
												timer_minute--; if(timer_minute == 0xFF)timer_minute=99;LCD_vidCursorXY(10,2);LCD_vidSendTimeElement(timer_minute);if(timer_hour == 0 && timer_minute == 0 && timer_second == 0){timer_second = 1;LCD_vidCursorXY(13,2);LCD_vidSendTimeElement(timer_second);}
												break;
											case 14:
												timer_second--; if(timer_second == 0xFF||(timer_minute == 0 && timer_hour == 0 && timer_second == 0))timer_second = 99;LCD_vidCursorXY(13,2);LCD_vidSendTimeElement(timer_second);
												break;
										}
										LCD_vidCursorXY(x,2);
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == DOWN);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
							case SELECT:
								timer_set = TRUE;
								loop = FALSE;
								display = main_display;
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
								LCD_vidSendCommand(LCD_DISPON_CURSOFF);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
						}
					}
				}
				else
				{
					LCD_vidCursorXY(6,2);
					LCD_vidWriteStr("DISABLE  VIEW");
					LCD_vidSendCommand(LCD_DISPON_CURSON);
					LCD_vidCursorXY(6,2);
					choice = 0;
					while(loop)
					{
						CHECKER();
						switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
						{
							case LEFT:
								LCD_vidCursorXY(6,2);
								choice = 0;
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == LEFT);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
							case RIGHT:
								LCD_vidCursorXY(15,2);
								choice = 1;
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == RIGHT);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
							case SELECT:
								loop = FALSE;
								while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
								if(alarm_ended || timer_ended)
									DISABLE_RESPONSES();
								break;
						}
					}
				}
				LCD_vidSendCommand(LCD_DISPON_CURSOFF);
				if(choice == 0)
				{
					timer_set = FALSE;
				}
				else
				{
					loop = TRUE;
					LCD_vidSendCommand(LCD_CLR);
					while(loop)
					{
						CHECKER();
						LCD_vidCursorXY(7,2);
						LCD_vidSendTimeElement(timer_hour);
						LCD_vidSendChar(':');
						LCD_vidSendTimeElement(timer_minute);
						LCD_vidSendChar(':');
						if(timer_set)
							LCD_vidSendTimeElement(timer_second);
						while(!DIO_u8GetPinVal(DIO_PORTA, DIO_PIN4))
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							else
								loop = FALSE;
					}
				}
				display = main_display;
				choice = ALARM;
				break;
			case CONTRAST:
						LCD_vidCursorXY(10,3); LCD_vidSendDecimalLToR(contrast);;
						loop = TRUE;
						while(loop)
						{
							CHECKER();
							_delay_ms(10);
							switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
							{
								case UP:
											if(contrast < 100) contrast+=5;
											LCD_vidCursorXY(9,3);
											LCD_vidSendChar(' ');
											if(contrast < 100)LCD_vidCursorXY(10,3);
											else LCD_vidCursorXY(9,3);
											LCD_vidSendDecimalLToR(contrast);
											TIMR1_vidSET_OCR1B((contrast*10)+((contrast*23)/100));
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == UP);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
								case DOWN:
											if(contrast > 0) contrast-=5;
											LCD_vidCursorXY(9,3);
											LCD_vidSendChar(' ');
											if(contrast < 100)LCD_vidCursorXY(10,3);
											else LCD_vidCursorXY(9,3);
											LCD_vidSendDecimalLToR(contrast);
											TIMR1_vidSET_OCR1B((contrast*10)+((contrast*23)/100));
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == DOWN);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
								case SELECT:
									display = main_display;
									loop = FALSE;
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
							}
						}
				break;
			case BRIGHTNESS:
						LCD_vidSendCommand(LCD_CLR);
						LCD_vidCursorXY(5,2);
						LCD_vidWriteStr("AUTO  MANUAL");
						LCD_vidCursorXY(5,2);
						LCD_vidSendCommand(LCD_DISPON_CURSON);
						x = 5;
						while(loop)
						{
							CHECKER();
							_delay_ms(10);
							switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
							{
								case RIGHT:
											x = 11;
											LCD_vidCursorXY(x,2);
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == UP);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
								case LEFT:
											x = 5;
											LCD_vidCursorXY(x,2);
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == DOWN);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
								case SELECT:
									display = main_display;
									loop = FALSE;
									LCD_vidSendCommand(LCD_DISPON_CURSOFF);
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
							}
						}
						if(x == 11)
						{
							loop = TRUE, auto_brightness = FALSE;
							LCD_vidCursorXY(5,2); LCD_vidWriteStr(" BRIGHTNESS ");
							LCD_vidCursorXY(10,3); LCD_vidSendDecimalLToR(brightness);
							TIMR1_vidSET_OCR1A((brightness*10)+((brightness*23)/100));

						}
						else
						{
							auto_brightness = TRUE;TIMR1_vidSET_OCR1A(ADC_u16GetADCRead(ADC_CH7));
						}
						while(loop)
						{
							CHECKER();
							_delay_ms(10);
							switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
							{
								case UP:
											if(brightness < 100) brightness+=5;
											LCD_vidCursorXY(9,3);
											LCD_vidSendChar(' ');
											if(brightness < 100)LCD_vidCursorXY(10,3);
											else LCD_vidCursorXY(9,3);
											LCD_vidSendDecimalLToR(brightness);
											TIMR1_vidSET_OCR1A((brightness*10)+((brightness*23)/100));
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == UP);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
								case DOWN:
											if(brightness > 0) brightness-=5;
											LCD_vidCursorXY(9,3);
											LCD_vidSendChar(' ');
											if(brightness < 100)LCD_vidCursorXY(10,3);
											else LCD_vidCursorXY(9,3);
											LCD_vidSendDecimalLToR(brightness);
											TIMR1_vidSET_OCR1A((brightness*10)+((brightness*23)/100));
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == DOWN);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
								case SELECT:
									display = main_display;
									loop = FALSE;
									while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
									if(alarm_ended || timer_ended)
										DISABLE_RESPONSES();
									break;
							}
						}
				break;
			case ADJUST:
				new_hour = hour;
				new_minute = minute;
				new_second = second;
				new_day_night[1] = day_night[1];
				new_day = day;
				new_month = month;
				LCD_vidSendCommand(LCD_CLR);
				LCD_vidCursorXY(5,2);
				LCD_vidSendTimeElement(new_hour);
				LCD_vidSendChar(':');
				LCD_vidSendTimeElement(new_minute);
				LCD_vidSendChar(':');
				LCD_vidSendTimeElement(new_second);
				LCD_vidSendChar(' ');
				LCD_vidWriteStr(new_day_night);
				LCD_vidCursorXY(6,3);
				LCD_vidSendTimeElement(new_day);
				LCD_vidSendChar('/');
				LCD_vidSendTimeElement(new_month);
				LCD_vidSendChar('/');
				LCD_vidSendYearElement(year);
				x=6,y=2;
				LCD_vidSendCommand(LCD_DISPON_CURSON);
				LCD_vidCursorXY(x,y);
				loop = TRUE;
				while(loop)
				{
					CHECKER();
					_delay_ms(10);
					switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
					{
						case LEFT:
									if(x == 15 && y == 3)
										x = 10;
									else if(x == 10)
										x = 7;
									else if(x == 7)
									{
										x = 15;
										y = 2;
									}
									else if(x == 15)
										x = 12;
									else if(x == 12)
										x = 9;
									else if(x == 9)
										x = 6;
							LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == LEFT);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case RIGHT:
									if(x == 6)
										x = 9;
									else if(x == 9)
										x = 12;
									else if(x == 12)
										x = 15;
									else if(x == 15 && y == 2)
									{
										x = 7;
										y = 3;
									}
									else if(x == 7)
										x = 10;
									else if(x == 10)
										x = 15;
							LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == RIGHT);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case UP:
									if(x == 6)
									{
										new_hour++;if(new_hour > 12) new_hour = 1;LCD_vidCursorXY(5,2);LCD_vidSendTimeElement(new_hour);
									}
									else if(x == 9)
									{
										new_minute++;if(new_minute > 59) new_minute = 0;LCD_vidCursorXY(8,2);LCD_vidSendTimeElement(new_minute);
									}
									else if(x == 12)
									{
										new_second++;if(new_second > 59) new_second = 0;LCD_vidCursorXY(11,2);LCD_vidSendTimeElement(new_second);
									}
									else if(x == 15 && y == 2)
									{
										if(new_day_night[1] == 'P')
											new_day_night[1] = 'A';
										else new_day_night[1] = 'P';
										LCD_vidCursorXY(14,2);LCD_vidWriteStr(new_day_night);
									}
									else if(x == 7)
									{
										new_day++;if(new_day > max_month_days[new_month - 1]) new_day = 1;LCD_vidCursorXY(6,3);LCD_vidSendTimeElement(new_day);
									}
									else if(x == 10)
									{
										new_month++;if(new_month > 12) new_month = 1;LCD_vidCursorXY(9,3);LCD_vidSendTimeElement(new_month);
									}
									else{  if(year < 2500) year++; LCD_vidCursorXY(12,3);LCD_vidSendYearElement(year);leap_year = IS_LEAP_YEAR();if(leap_year)max_month_days[1] = 29;else max_month_days[1] = 28;if(new_day > max_month_days[new_month - 1]){ new_day = max_month_days[new_month - 1];LCD_vidCursorXY(6,3);LCD_vidSendTimeElement(new_day);}}
									LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == UP);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case DOWN:
									if(x == 6)
									{
										new_hour--;if(new_hour < 1) new_hour = 12;LCD_vidCursorXY(5,2);LCD_vidSendTimeElement(new_hour);
									}
									else if(x == 9)
									{
										new_minute--;if(new_minute == 0xFF ) new_minute = 59;LCD_vidCursorXY(8,2);LCD_vidSendTimeElement(new_minute);
									}
									else if(x == 12)
									{
										new_second--;if(new_second == 0xFF) new_second = 59;LCD_vidCursorXY(11,2);LCD_vidSendTimeElement(new_second);
									}
									else if(x == 15 && y == 2)
									{
										if(new_day_night[1] == 'P')
											new_day_night[1] = 'A';
										else new_day_night[1] = 'P';
										LCD_vidCursorXY(14,2);LCD_vidWriteStr(new_day_night);
									}
									else if(x == 7)
									{
										new_day--;if(new_day < 1) new_day = max_month_days[new_month - 1];LCD_vidCursorXY(6,3);LCD_vidSendTimeElement(new_day);
									}
									else if(x == 10)
									{
										new_month--;if(new_month < 1) new_month = 12;LCD_vidCursorXY(9,3);LCD_vidSendTimeElement(new_month);
									}
									else{  if(year > 1970) year--; LCD_vidCursorXY(12,3);LCD_vidSendYearElement(year);leap_year = IS_LEAP_YEAR();if(leap_year)max_month_days[1] = 29;else max_month_days[1] = 28; if(new_day > max_month_days[new_month - 1]){ new_day = max_month_days[new_month - 1];LCD_vidCursorXY(6,3);LCD_vidSendTimeElement(new_day);}}
									LCD_vidCursorXY(x,y);
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == DOWN);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
						case SELECT:
							second = new_second;
							minute = new_minute;
							hour = new_hour;
							day_night[1] = new_day_night[1];
							day = new_day;
							month = new_month;
							loop = FALSE;
							display = main_display;
							name_of_day = Day_Of_Week(day,month,year);
							date_size = Size_Of_Date();
							while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);
							LCD_vidSendCommand(LCD_DISPON_CURSOFF);
							if(alarm_ended || timer_ended)
								DISABLE_RESPONSES();
							break;
					}
				}
				break;
		}
		while(display == main_menu)
		{
			if(old_choice != choice)
			{
				LCD_vidSendCommand(LCD_CLR);
				switch(choice)
				{
					case ALARM: LCD_vidCursorXY(8,2); LCD_vidWriteStr("ALARM"); break;
					case TIMER: LCD_vidCursorXY(8,2); LCD_vidWriteStr("TIMER"); break;
					case CONTRAST: LCD_vidCursorXY(7,2); LCD_vidWriteStr("CONTRAST"); break;
					case BRIGHTNESS: LCD_vidCursorXY(6,2); LCD_vidWriteStr("BRIGHTNESS"); break;
					case ADJUST: LCD_vidCursorXY(8,2); LCD_vidWriteStr("ADJUST"); LCD_vidCursorXY(5,3); LCD_vidWriteStr("DATE & TIME"); break;
					case CANCEL: LCD_vidCursorXY(8,2); LCD_vidWriteStr("CANCEL"); break;
				}
				old_choice = choice;
			}
			switch(DIO_u8GetPortVal(DIO_PORTA) & 0b00011111)
			{
				case LEFT: if(choice > ALARM){ choice--;} while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == LEFT);if(alarm_ended || timer_ended)DISABLE_RESPONSES();break;
				case RIGHT: if(choice < CANCEL){ choice++;} while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == RIGHT);if(alarm_ended || timer_ended)DISABLE_RESPONSES();break;
				case SELECT: if(choice == CANCEL) {display = main_display;} else{display = choice;} choice = ALARM; old_choice = TIMER; loop = TRUE;  while((DIO_u8GetPortVal(DIO_PORTA) & 0b00011111) == SELECT);if(alarm_ended || timer_ended)DISABLE_RESPONSES();break;
			}
			CHECKER();
		}
	}
}

ISR(TIMER2_COMP_vect)
{
	counter++;
	if(counter == 250)
	{
		counter = 0;
		second++;
		if(second == 60)
		{
			second = 0;
			time_update = TRUE;
		}
		else if(!(second % 5))
		{
			sensor_update = TRUE;
		}
		if(timer_set)
		{
			timer_second--;
			if(timer_second == 0xFF)
			{
				if(timer_minute == 0 && timer_hour == 0)
				{
					timer_second = 1;
					timer_set = FALSE;
					timer_ended = TRUE;
					UART_vidTransmit(FIRE_TIMER);
				}
				else
				{
					timer_update = TRUE;
					timer_second = 59;
				}
			}
		}
	}
}
