/*
 * DIO_prog.c
 *
 *  Created on: Jan 22, 2021
 *      Author: DELL
 */
#include "LIB/TYPES.h"
#include "LIB/Bit_Math.h"
#include "DIO_INTERFACE.h"
#include "DIO_PRV.h"

void DIO_vidSetPinVal(u8 portid,u8 pinid,u8 pinval)
{
	if((portid <= DIO_PORTD) && (pinid <= DIO_PIN7))
	{
		if(pinval == DIO_HIGH)
		{
			switch(portid)
			{
				case DIO_PORTA: SET_BIT(PORTA_REG,pinid);break;
				case DIO_PORTB: SET_BIT(PORTB_REG,pinid);break;
				case DIO_PORTC: SET_BIT(PORTC_REG,pinid);break;
				case DIO_PORTD: SET_BIT(PORTD_REG,pinid);break;
			}
		}
		else if(pinval == DIO_LOW)
		{
			switch(portid)
			{
				case DIO_PORTA: CLR_BIT(PORTA_REG,pinid);break;
				case DIO_PORTB: CLR_BIT(PORTB_REG,pinid);break;
				case DIO_PORTC: CLR_BIT(PORTC_REG,pinid);break;
				case DIO_PORTD: CLR_BIT(PORTD_REG,pinid);break;
			}
		}
		else
		{
			/*report error*/
		}
	}
}

void DIO_vidTogglePinVal(u8 portid,u8 pinid)
{
	switch(portid)
	{
		case DIO_PORTA: TOG_BIT(PORTA_REG,pinid);break;
		case DIO_PORTB: TOG_BIT(PORTB_REG,pinid);break;
		case DIO_PORTC: TOG_BIT(PORTC_REG,pinid);break;
		case DIO_PORTD: TOG_BIT(PORTD_REG,pinid);break;
	}
}

void DIO_vidSetPinDir(u8 portid,u8 pinid,u8 pinval)
{
	if((portid <= DIO_PORTD) && (pinid <= DIO_PIN7))
	{
		if(pinval == DIO_OUTPUT)
		{
			switch(portid)
			{
				case DIO_PORTA: SET_BIT(DDRA_REG,pinid);break;
				case DIO_PORTB: SET_BIT(DDRB_REG,pinid);break;
				case DIO_PORTC: SET_BIT(DDRC_REG,pinid);break;
				case DIO_PORTD: SET_BIT(DDRD_REG,pinid);break;
			}
		}
		else if(pinval == DIO_INPUT)
		{
			switch(portid)
			{
				case DIO_PORTA: CLR_BIT(DDRA_REG,pinid);break;
				case DIO_PORTB: CLR_BIT(DDRB_REG,pinid);break;
				case DIO_PORTC: CLR_BIT(DDRC_REG,pinid);break;
				case DIO_PORTD: CLR_BIT(DDRD_REG,pinid);break;
			}
		}
		else
		{
			/*report error*/
		}
	}
}

void DIO_vidSetPortVal(u8 portid,u8 portval)
{
	if(portid <= DIO_PORTD)
	{
		switch(portid)
		{
			case DIO_PORTA: PORTA_REG = portval; break;
			case DIO_PORTB: PORTB_REG = portval; break;
			case DIO_PORTC: PORTC_REG = portval; break;
			case DIO_PORTD: PORTD_REG = portval; break;
		}
	}
	else
	{
		/*report error*/
	}
}

void DIO_vidSetPortDir(u8 portid,u8 portval)
{
	if(portid <= DIO_PORTD)
	{
		switch(portid)
		{
			case DIO_PORTA: DDRA_REG = portval; break;
			case DIO_PORTB: DDRB_REG = portval; break;
			case DIO_PORTC: DDRC_REG = portval; break;
			case DIO_PORTD: DDRD_REG = portval; break;
		}
	}
	else
	{
		/*report error*/
	}
}

u8 DIO_u8GetPinVal(u8 portid,u8 pinid)
{
	u8 result;
	if((portid <= DIO_PORTD) && (pinid <= DIO_PIN7))
		{
			switch(portid)
			{
				case DIO_PORTA: result = GET_BIT(PINA_REG,pinid) ; break;
				case DIO_PORTB: result = GET_BIT(PINB_REG,pinid) ; break;
				case DIO_PORTC: result = GET_BIT(PINC_REG,pinid) ; break;
				case DIO_PORTD: result = GET_BIT(PIND_REG,pinid) ; break;
			}
			return result;
		}
		else
		{
			/*report error*/
			result=0xFF;
			return result;
		}
}

u8 DIO_u8GetPortVal(u8 portid)
{
	u8 result;
	if(portid <= DIO_PORTD)
		{
			switch(portid)
			{
				case DIO_PORTA: result = PINA_REG	; break;
				case DIO_PORTB: result = PINB_REG	; break;
				case DIO_PORTC: result = PINC_REG	; break;
				case DIO_PORTD: result = PIND_REG	; break;
			}
			return result;
		}
		else
		{
			/*report error*/
		}
}

