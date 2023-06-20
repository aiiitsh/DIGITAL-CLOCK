/*
 * LCD_prog.c
 *
 *  Created on: Jan 23, 2021
 *      Author: DELL
 */
#define	F_CPU	8000000UL
#include	"LIB/TYPES.h"
#include	"LIB/Bit_Math.h"
#include	"util/delay.h"
#include	"Dio_interface.h"
#include 	"LCD_interface.h"
#include	"LCD_configure.h"
#include	"LCD_prv.h"

void LCD_vidInit()
{
	_delay_ms(30);
	LCD_vidSendCommand(LCD_FUNCSET_8BIT);
	_delay_ms(1);
	LCD_vidSendCommand(LCD_DISPON_CURSOFF);
	_delay_ms(1);
	LCD_vidSendCommand(LCD_HOME);
	_delay_ms(3);
	LCD_vidSendCommand(LCD_ENTRYMODE_ON);
	_delay_ms(2);
}

void LCD_vidSendCommand(u8 u8cmd)
{
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_RS_PIN,DIO_LOW);
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_RW_PIN,DIO_LOW);
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_E_PIN,DIO_HIGH);
	DIO_vidSetPortVal(LCD_DATA_PORT, u8cmd);
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);
	_delay_ms(5);
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
	_delay_ms(10);
}

void LCD_vidSendChar(u8 u8char)
{
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_RS_PIN,DIO_HIGH);
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_RW_PIN,DIO_LOW);
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_E_PIN,DIO_HIGH);
	DIO_vidSetPortVal(LCD_DATA_PORT, u8char);
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_LOW);
	_delay_ms(5);
	DIO_vidSetPinVal(LCD_CONTROL_PORT,LCD_E_PIN,DIO_HIGH);
	_delay_ms(10);
}

void LCD_vidWriteStr(u8* pu8str)
{
	u8 i =0;
	while(pu8str[i]!=0)
	{
		LCD_vidSendChar(pu8str[i++]);
	}
}

void LCD_vidCustomChar(u8 u8location,u8* pattern)
{
	LCD_vidSendCommand(0x40+(u8location*8));
	u8 i;
	for(i=0;i<8;i++)
	{
		LCD_vidSendChar(pattern[i]);
	}
}

void LCD_vidCursorXY(u8 u8x,u8 u8y)
{
	switch(u8y)
	{
		case 1: LCD_vidSendCommand(0x7F+u8x); break;
		case 2: LCD_vidSendCommand(0xBF+u8x); break;
		case 3: LCD_vidSendCommand(0x93+u8x); break;
		case 4: LCD_vidSendCommand(0xD3+u8x); break;
	}
}

void LCD_vidClrLine(u8 u8line)
{
	switch(u8line)
	{
		case 1: LCD_vidSendCommand(0x80); LCD_vidWriteStr("                    "); break;
		case 2: LCD_vidSendCommand(0xC0); LCD_vidWriteStr("                    "); break;
		case 3: LCD_vidSendCommand(0x94); LCD_vidWriteStr("                    "); break;
		case 4: LCD_vidSendCommand(0xD4); LCD_vidWriteStr("                    "); break;
	}
}

void LCD_vidSendDecimalLToR( u16 u16number )
{
	u32 i;
	u16 test=u16number;
	if(u16number < 10)
	{
		LCD_vidSendChar('0');
	}
	if(u16number != 0)
	{
		for(i=10;test!=0;i*=10)
		{
			test=u16number;
			test/=i;
		}
		test=u16number;
		i/=100;
		for(;i>0;i/=10)
		{
			test/=i;
			LCD_vidSendChar(test+48);
			test=u16number;
			test-=((test/i)*i);
		}
	}
	else if(u16number == 0)
	{
		LCD_vidSendChar('0');
	}
}

void LCD_vidSendTimeElement( u8 u8number )
{
	LCD_vidSendChar(u8number/10 + '0');
	LCD_vidSendChar(u8number%10 + '0');
}
void LCD_vidSendDayElement( u8 u8number )
{
	if(u8number > 9)
	{
		LCD_vidSendChar(u8number/10 + '0');
	}
	LCD_vidSendChar(u8number%10 + '0');
}

void LCD_vidSendYearElement( u16 u16number )
{
	LCD_vidSendChar(u16number/1000 + '0');
	LCD_vidSendChar((u16number/100)%10 + '0');
	LCD_vidSendChar((u16number/10)%10 + '0');
	LCD_vidSendChar(u16number%10 + '0');
}

void LCD_vidSendDecimalRToL( s32 s32number )
{
	if(s32number < 0)
	{
		LCD_vidSendChar('-');
		s32number=-s32number;
	}
	s32 test=s32number;
	if(s32number != 0)
	{
		while(s32number != 0)
		{
			test=s32number%10;
			s32number/=10;
			LCD_vidSendChar(test+48);
		}
	}
	else if(s32number == 0)
	{
		LCD_vidSendChar('0');
	}
}

u8 LCD_u8ReadCounter()
{
	u8 val;
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_RS_PIN,DIO_LOW);
	DIO_vidSetPinVal(LCD_CONTROL_PORT, LCD_RW_PIN,DIO_HIGH);
	DIO_vidSetPortDir(LCD_DATA_PORT,DIO_PORT_INPUT);
	val = DIO_u8GetPortVal(LCD_DATA_PORT);
	DIO_vidSetPortDir(LCD_DATA_PORT,DIO_PORT_OUTPUT);
	CLR_BIT(val,7);
	return val;
}
