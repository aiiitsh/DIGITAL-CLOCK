/*
 * LCD_interface.h
 *
 *  Created on: Jan 23, 2021
 *      Author: DELL
 */

/****************************************************/
/******************Public functions******************/
/****************************************************/

void LCD_vidInit();

void LCD_vidSendCommand(u8 u8cmd);

void LCD_vidSendChar(u8 u8char);

void LCD_vidWriteStr(u8* pu8str);

void LCD_vidCustomChar(u8 u8location,u8* pattern);

void LCD_vidCursorXY(u8 u8x,u8 u8y);

void LCD_vidClrLine(u8 u8line);

void LCD_vidSendTimeElement( u8 u8number );

void LCD_vidSendDecimalLToR( u16 u8number );

void LCD_vidSendDayElement( u8 u8number );

void LCD_vidSendDecimalRToL( s32 s32number );

u8 LCD_u8ReadCounter();

void LCD_vidSendTimeElement( u8 u8number );

/****************************************************/
/********************Public Macros*******************/
/****************************************************/

#define LCD_CLR					0x01
#define LCD_HOME				0x02
#define LCD_ENTRYMODE_OFF		0x04
#define LCD_ENTRYMODE_ON		0x06
#define LCD_DISPOFF				0x08
#define LCD_DISPON_CURSON		0x0E
#define LCD_FUNCRESET			0x30
#define LCD_FUNCSET_8BIT		0x38
#define LCD_SETCURSOR			0x80
#define LCD_DISPON_CURSBLINK	0x0F
#define LCD_DISPON_CURSOFF		0x0C
#define LCD_LEFT_CURSOR_SHIFT	0x10
#define LCD_RIGHT_CURSOR_SHIFT	0x14
#define LCD_LEFT_SHIFT			0x18
#define LCD_RIGHT_SHIFT			0x1C

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_



#endif /* LCD_INTERFACE_H_ */
